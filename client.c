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
  //create a socket
  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  //specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = htons(INADDR_ANY);

  int connection_status = connect(network_socket, (struct sockaddr *) &server_address,sizeof(server_address));
  //check for error with connection
  if (connection_status < 0){
    printf("Error connecting to the remote socket");
  }

  //sending the initial message to server
  char msg[20] = "Hello Server";
  send(network_socket, msg, sizeof(msg),0);

  //receive data from the socket
  char server_response[256];
  recv(network_socket, &server_response, sizeof(server_response),0);

  //print out the server's response
  printf("The server sent the data : %s\n", server_response);

  //and then close the socket
  close(network_socket);
  return 0;
}
