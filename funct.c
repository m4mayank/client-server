#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>


int HEADER=5;
int MAXSIZE=256;

//Reference: https://stackoverflow.com/questions/23618316/undefined-reference-to-strlwr
char *strlwr(char *str)
{
 unsigned char *p = (unsigned char *)str;
 while (*p) {
   *p = tolower((unsigned char)*p);
   p++;
 }
 return str;
}


void Recv(int network_socket,char server_response[]){
  char header[HEADER];
  char response[MAXSIZE];
  memset(header,0,HEADER*sizeof(char));
  memset(response,0,MAXSIZE*sizeof(char));
  recv(network_socket, &header, sizeof(header),0);
  long len = strtol(header, NULL, 10);
  if (strlen(response)<len)
  recv(network_socket, &response,len*sizeof(char),0);
  strcpy(server_response,response);
}

void format_string(char sti[]){
  char formatted_string[MAXSIZE];
  memset(formatted_string,0,MAXSIZE*sizeof(char));
  char result[HEADER];
  memset(result,0,HEADER*sizeof(char));
  int len = strlen(sti);
  sprintf(result, "%d", len);
  strcat(formatted_string,result);
  int i;
  for(i=0;i<(HEADER - strlen(result));i++){
    strcat(formatted_string, " ");
  }
  strcat(formatted_string, sti);
  strcpy(sti,formatted_string);
}
