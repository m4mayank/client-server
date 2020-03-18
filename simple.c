#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
int HEADER=5;
int MAXSIZE=20;

//#include "funct.c""

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
//
/*struct for the message
 */
struct message {
  int msg_header;
  char msg[20];

};
//
int main(int argc, char *argv[]){
  struct hostent *hp;
  char status[6] = "status";
  char reserve[7] = "reserve";
  if(argc!=4){
    printf("\nPlease provide the Server IP address, Port number and the action");
    exit(-1);
  }
//
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

void format_string(char sti[]){
  char formatted_string[MAXSIZE+1];
  memset(formatted_string,0,strlen(formatted_string));
  char result[HEADER];
  memset(result,0,strlen(result));
  int len = strlen(sti);
  sprintf(result, "%d", len);
  strcat(formatted_string,result);
  for(int i=0;i<(HEADER - strlen(result));i++){
    strcat(formatted_string, " ");
  }
  strcat(formatted_string, sti);
  strcpy(sti,formatted_string);
}


int main(){
  char msg[MAXSIZE+1];
  memset(msg,0,strlen(msg));
  printf("\nEnter the string: ");
  // scanf("%s", msg);
  fgets(msg, MAXSIZE, stdin);
  int len = strlen(msg);
  if( msg[len-1] == '\n' ){
    msg[len-1] = 0;
  }
  printf("%s\n", msg);
  format_string(msg);
  printf("%s\n",msg);
  char message[256];
  sprintf(message, )
}
