#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include "funct.c"
/*
#define MAXLINE 4096
#define bzero(ptr,n) memset(ptr, 0, n)
*/
/* include Socket */
/*
int
Socket(int family, int type, int protocol)
{
  int n;
  if((n=socket(family, type, protocol)) < 0)
    err_sys("socket error");
  return(n);
}
*/
/* end Socket */
/*
void Bind(int fd, const struct sockaddr *sa, socklen_t salen){
  if (bind(fd, sa, salen) < 0)
    err_sys("bind error");
}
*/
/* include Listen */
/*
void
Listen(int fd, int backlog)
{
    char  *ptr;
    if((ptr=getenv("LISTENQ"))!=NULL)
      backlog=atoi(ptr);
    if(listen(fd, backlog)<0)
      err_sys("listen error");
}
*/
/* end Listen */
/*
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr){
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
    err_sys("accept error");
  }
  return(n);

}
*/

int main(int argc, char **argv){
  int listenfd, connfd,n;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];
  char recvline[MAXLINE + 1];
  struct message msg;
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(0);
  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);
  for(;;){
    connfd = Accept(listenfd, (SA *) NULL, NULL);
  }
}
