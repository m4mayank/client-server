#include "funct.c"


int seats=5;

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0){
          perror("Bind");
          close(fd);
          exit(1);
    }
}

int Socket(int family, int type, int protocol)
{
    int n;
    if ((n = socket(family, type, protocol)) < 0){
            perror("Socket");
            exit(1);
    }
    return(n);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;

again:
      if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef  EPROTO
            if (errno == EPROTO || errno == ECONNABORTED)
#else
            if (errno == ECONNABORTED)
#endif
              goto again;
            else
              perror("Accept error");
      }
      return(n);
}

int main(){
  char server_message[MAXSIZE],client_response[MAXSIZE];
  int server_socket,client_socket;
  struct sockaddr_in server_address;

  //Create a socket
  server_socket = Socket(AF_INET, SOCK_STREAM, 0);

  //Specify an address for the socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(0);
  server_address.sin_addr.s_addr = htons(INADDR_ANY);

  //Bind the socket to our specified IP and Port
  Bind(server_socket, (struct sockaddr *) &server_address,sizeof(server_address));

  //Starting the socket for listening
  listen(server_socket, 4);

  socklen_t len = sizeof(server_address);
  if (getsockname(server_socket, (struct sockaddr *)&server_address, &len) < 0)
  perror("getsockname");
  else
  printf("EDM is running on local host, listening on port %d\n", ntohs(server_address.sin_port));



  while (1) {
    client_socket=accept(server_socket,(struct sockaddr *)NULL, NULL);
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
