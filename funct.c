/*
 * Some of the code written in here has been referenced from the following sources:
 * 1) W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
 * 2) Jim Frost's IP Sockets Tutorial
 */

#include "funct.h"


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

//Function to Receive the formatted message and extract message from it
void Recv(int network_socket,char server_response[]){
  char header[HEADER];
  char response[MAXSIZE];
  memset(header,0,HEADER*sizeof(char));
  memset(response,0,MAXSIZE*sizeof(char));
  while(strlen(header)<HEADER){
  recv(network_socket, &header, HEADER*sizeof(char),0);
  }
  long len = strtol(header, NULL, 10);
  while(strlen(response)<len){
  recv(network_socket, &response,len*sizeof(char),0);
  }
  strcpy(server_response,response);
}

//Formatting the message
//message format : (header)-(message)
//here header is the length of message and message is the actual message
//for example : the message "hey" will be sent as "3    hey"
//the spacing between the length and message is decided by the length of message
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

//Wrapper function for bind()
//Referred from W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0){
          perror("Bind error");
          close(fd);
          exit(1);
    }
}

//Wrapper function for socket()
//Referred from W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
int Socket(int family, int type, int protocol)
{
    int n;
    if ((n = socket(family, type, protocol)) < 0){
            perror("Socket error");
            exit(1);
    }
    return(n);
}

//Wrapper function for accept()
//Referred from W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
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

//Wrapper function for connect()
//Referred from W.R. Stevens, B. Fenner, and A.M. Rudoff. UNIX Network Programming, Volume 1
void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0){
    perror("Error connecting to the Server");
    close(fd);
    exit(1);
  }
}
