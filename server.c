#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>


int main(){
  char server_message[256]="You have connected to the server!";

  //create a socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  //specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = htons(INADDR_ANY);

  //Bind the socket to our specified IP and Port
  bind(server_socket, (struct sockaddr *) &server_address,sizeof(server_address));

  listen(server_socket, 4);

  int client_socket;
  client_socket=accept(server_socket,(struct sockaddr *)NULL, NULL);

  //receive the message after accepting the connection
  char client_response[20];
  recv(client_socket, &client_response, sizeof(client_response),0);
  printf("client sent : %s\n", client_response);

  //send the message
  send(client_socket, server_message, sizeof(server_message),0);

  //close the socket
  close(server_socket);
  return 0;
}
