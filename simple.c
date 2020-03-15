#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
#include "funct.c""

/* from stack overfow
 * link : https://stackoverflow.com/questions/23618316/undefined-reference-to-strlwr
char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;
  while (*p) {
    *p = tolower((unsigned char)*p);
    p++;
  }
  return str;
}
*/

/*struct for the message

struct message {
  int msg_header;
  char msg[20];

};
*/

int main(int argc, char *argv[]){
  struct hostent *hp;
  char status[6] = "status";
  char reserve[7] = "reserve";
  if(argc!=4){
    printf("\nPlease provide the Server IP address, Port number and the action");
    exit(-1);
  }

  hp = gethostbyname(argv[1]);
  if (hp == NULL){
    printf("Unable to resolve name. Please enter a proper IP address.");
    exit(-1);
  }

  if (strcmp(strlwr(argv[3]),status)==0){
    printf("Asking for status");
  }
  else if (strcmp(strlwr(argv[3]),reserve)==0){
    printf("Asking for reservation");
  }
  else{
    printf("Provide a Correct action");
    exit(-1);
  }
  struct message first;
  printf("\nEnter the message:");
  fgets(first.msg, sizeof(first.msg), stdin);
  first.msg_header = strlen(first.msg)-1;
  printf("\nThe msg is : %s and the length is %d",first.msg, first.msg_header);
}
