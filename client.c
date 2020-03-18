#include "funct.c"

void client_validations(struct hostent *hp, char new_msg[20],int argc, char *argv[]){
  // printf("%s\n", new_msg);
  memset(new_msg,0,20*sizeof(char));
  if(argc!=4){
    printf("\nMissing options. Please provide the inputs in following format: ./client [IP] [PORT] [status/reserve]\n");
    exit(-1);
  }

  *hp = *(struct hostent *)gethostbyname(argv[1]);
  if (hp == NULL){
    printf("Unable to resolve name. Please enter a proper IP address.");
    exit(1);
  }
  if (strcmp(strlwr(argv[3]),"status")==0){
    strcpy(new_msg,"status");
  }
  else if (strcmp(strlwr(argv[3]),"reserve")==0){
    strcpy(new_msg,"reserve");
  }
  else{
    printf("\nInvalid option. Please provide the inputs in following format: ./client [IP] [PORT] [status/reserve]\n");
    exit(1);
  }
}

int main(int argc, char *argv[]){
  char msg[20];
  memset(msg,0,20*sizeof(char));
  struct hostent *hp;
  long port = strtol(argv[2], NULL, 10);
  printf("%ld\n",port );
  // if(argc!=4){
  //   printf("\nPlease provide the Server IP address, Port number and the action");
  //   exit(-1);
  // }
  client_validations(hp,msg,argc,argv);
  // hp = gethostbyname(argv[1]);
  // if (hp == NULL){
  //   printf("Unable to resolve name. Please enter a proper IP address.");
  //   exit(-1);
  // }
  // struct sockaddr_in sock_addr;
  // char ip[16];

  // if (strcmp(strlwr(argv[3]),"status")==0){
  //   strcpy(msg,"status");
  // }
  // else if (strcmp(strlwr(argv[3]),"reserve")==0){
  //   strcpy(msg,"reserve");
  // }
  // else{
  //   printf("\nInvalid option. Please provide the inputs in following format: ./client [IP] [PORT] [status/reserve]\n");
  //   exit(1);
  // }
  //create a socket
  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  //specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr = *((struct in_addr*) hp->h_addr_list[0]);
  // printf("\nIP Address : %s\n", inet_ntoa(server_address.sin_addr));
	// inet_ntop(AF_INET, &sock_addr.sin_addr, ip, sizeof(ip));
  // server_address.sin_addr.s_addr = htons(IPbuffer);

  //check for error with connection
  if ((connect(network_socket, (struct sockaddr *) &server_address,sizeof(server_address))) < 0){
    perror("Error connecting to the remote socket");
    exit(1);
  }

  //sending the initial message to server
  // char msg[20] = "reserve";
  format_string(msg);

  if((send(network_socket, msg, sizeof(msg),0)) < 0)
  {
    printf("Error sending the message to server");
    exit(1);
  }

  //receive data from the socket
  char server_response[MAXSIZE];
  memset(server_response,0,MAXSIZE*sizeof(char));
  Recv(network_socket, server_response);
  printf("%s\n",server_response);
  //and then close the socket
  close(network_socket);
  return 0;
}
