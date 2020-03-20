/*
 * Some of the code written in here has been referenced from the following sources:
 * 1) W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
 * 2) Jim Frost's IP Sockets Tutorial
 */

#include "funct.h"


int seats=40;

int main(){
  char server_message[MAXSIZE],client_response[MAXSIZE];
  int server_socket,client_socket;
  struct sockaddr_in server_address;

  //Create a socket
  server_socket = Socket(AF_INET, SOCK_STREAM, 0);

  //creating the IP address block which will be later assigned to socket
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
  printf("EDM is running on localhost, listening on port %d\n", ntohs(server_address.sin_port));



  while (1) {
    //Accepting the incoming connections from Client
    client_socket=Accept(server_socket,(struct sockaddr *)NULL, NULL);
    memset(client_response,0,MAXSIZE*sizeof(char));
    memset(server_message,0,MAXSIZE*sizeof(char));

    //Receiving the message from Client
    Recv(client_socket, client_response);

    //Checking the message sent by Client
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

    //Encapsulating the message into a format (header)-(message)
    //here header is the length of message that follows
    format_string(server_message);

    //Send the messagei response to client
    if(send(client_socket, server_message, sizeof(server_message),0)<0){
      perror("Failed to send message to client");
    }

    //Closing the Client Socket
    close(client_socket);
  }
  //Close the Server Socket while exiting the program
  close(server_socket);
  return 0;
}
