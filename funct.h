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

#define HEADER 5
#define MAXSIZE 256

char *strlwr(char *str);
void Recv(int network_socket,char server_response[]);
void format_string(char sti[]);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
int Socket(int family, int type, int protocol);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
