#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <strings.h>
#include <ctype.h>

/* from stack overfow
 * link : https://stackoverflow.com/questions/23618316/undefined-reference-to-strlwr
 */
char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;
  while (*p) {
    *p = tolower((unsigned char)*p);
    p++;
  }
  return str;
}

/*struct for the message
 */
struct message {
  int msg_header;
  char msg[20];
};

void	 err_sys(const char *, ...);
#define MAXLINE 4096
#define	SA	struct sockaddr
#define	LISTENQ		1024	/* 2nd argument to listen() */
/*
#define bzero(ptr,n) memset(ptr, 0, n)
*/

/* include Socket */
int Socket(int family, int type, int protocol)
{
  int n;
  if((n=socket(family, type, protocol)) < 0)
    err_sys("socket error");
  return(n);
}
/* end Socket */

void Bind(int fd, const struct sockaddr *sa, socklen_t salen){
  if (bind(fd, sa, salen) < 0)
    err_sys("bind error");
}

/* include Listen */
void Listen(int fd, int backlog)
{
    char  *ptr;
    if((ptr=getenv("LISTENQ"))!=NULL)
      backlog=atoi(ptr);
    if(listen(fd, backlog)<0)
      err_sys("listen error");
}
/* end Listen */

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
