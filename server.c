#include "funct.c"


int seats=5;


int main(){
  char server_message[MAXSIZE],client_response[MAXSIZE];
  int server_socket,client_socket;
  struct sockaddr_in server_address;
  //create a socket

  if((server_socket = socket(AF_INET, SOCK_STREAM, 0))<0){
    perror("socket");
    exit(1);
  }

  //specify an address for the socket

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(0);
  server_address.sin_addr.s_addr = htons(INADDR_ANY);

  //Bind the socket to our specified IP and Port
  if((bind(server_socket, (struct sockaddr *) &server_address,sizeof(server_address)))<0){
    perror("bind");
    close(server_socket);
    exit(1);
  }

  socklen_t len = sizeof(server_address);
  if (getsockname(server_socket, (struct sockaddr *)&server_address, &len) < 0)
  perror("getsockname");
  else
  printf("EDM is running on local host, listening on port %d\n", ntohs(server_address.sin_port));

  listen(server_socket, 4);


  while (1) {
    // client_socket=accept(server_socket,(struct sockaddr *)NULL, NULL);
    if ((client_socket=accept(server_socket,(struct sockaddr *)NULL, NULL)) < 0) {
      if (errno == EINTR){
        continue;
      }
      perror("accept");
      exit(1);
    }
    //receive the message after accepting the connection
    // char client_response[MAXSIZE];
    memset(client_response,0,MAXSIZE*sizeof(char));
    memset(server_message,0,MAXSIZE*sizeof(char));
    Recv(client_socket, client_response);
    printf("%s\n",client_response);
    if(strcmp(client_response,"reserve")==0){
      sprintf (server_message, "Failed Reservation.");
      if(seats > 0){
        --seats;
        sprintf (server_message,"Space Reserved. Shuttle bus now has %d spaces available.",seats);
      }
    }
    else{
      sprintf (server_message, "Shuttle bus has %d spaces available.",seats);
      if(seats < 0){
        sprintf (server_message, "Shuttle bus has 0 spaces available.");
      }
    }
    //send the message
    format_string(server_message);
    send(client_socket, server_message, sizeof(server_message),0);
    close(client_socket);
  }
  //close the socket
  close(server_socket);
  return 0;
}
