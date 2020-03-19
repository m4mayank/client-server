/*
 * Some of the code written in here has been referenced from the following sources:
 * 1) W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
 * 2) Jim Frost's IP Sockets Tutorial
 */

#include "funct.h"


int main(int argc, char *argv[]){
  char msg[20];
  int network_socket;
  struct sockaddr_in server_address;
  char server_response[MAXSIZE];
  struct hostent *hp;
  long port = strtol(argv[2], NULL, 10); //Converting port from string to long int

  memset(msg,0,20*sizeof(char));

  //Checking if all the Arguments are supplied.
  if(argc!=4){
    printf("\nPlease provide the Server IP address, Port number and the action");
    exit(-1);
  }

  //Validating the IP address entered by the user
  hp = gethostbyname(argv[1]);
  if (hp == NULL){
    printf("Unable to resolve name. Please enter a proper IP address.");
    exit(-1);
  }

  //Checking if user has asked the status or requested to reserve the seat
  if (strcmp(strlwr(argv[3]),"status")==0){
    strcpy(msg,"status");
  }
  else if (strcmp(strlwr(argv[3]),"reserve")==0){
    strcpy(msg,"reserve");
  }
  else{
    printf("\nInvalid option. Please provide the inputs in following format: ./client [IP] [PORT] [status/reserve]\n");
    exit(1);
  }
  //Create a Socket
  network_socket = Socket(AF_INET, SOCK_STREAM, 0);

  //Using the resolved address
  memset(&server_address,0,sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr = *((struct in_addr*) hp->h_addr);

  //Connecting using the socket and address block created earlier
  Connect(network_socket, (struct sockaddr *) &server_address,sizeof(server_address));

  //Formatting the message. Format used (header)-(message)
  //here the header is the length of message that follows
  format_string(msg);

  //Sending the initial formatted message to server
  if((send(network_socket, msg, sizeof(msg),0)) < 0)
  {
    printf("Error sending the message to server");
    exit(1);
  }

  //receive data from the socket
  memset(server_response,0,MAXSIZE*sizeof(char));
  Recv(network_socket, server_response);
  printf("%s\n",server_response);

  //Closing the socket
  close(network_socket);
  return 0;
}
