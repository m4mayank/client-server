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

void
Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0){
    perror("Error connecting to the Server");
    close(fd);
    exit(1);
  }
}
