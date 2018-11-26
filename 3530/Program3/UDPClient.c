/* Compilation: gcc -o UDPclient UDPclient.c
   Execution  : ./UDPclient <port_number> [eg. port_number = 5000, where port_number is the UDP server port number]
*/

//Import
/*============================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>


//Definitions
/*============================================================================*/
#define SERVER "129.120.151.94" //IP address of server
#define BUFLEN 512  //Max length of buffer
#define TIMETOLIVE 3600 //Time to live

//Classes && Structs
/*============================================================================*/
typedef struct  {
  char *yiaddr;
  int tid;  //Transaction ID
  int ttl;  //Time to live
}DHCP_Request;

//Function Declarations && Implementations
/*============================================================================*/
void die(char *s)
{
    perror(s);
    exit(1);
}
//lets generate a random Transaction id!
int gen_tid()
{
  return rand()%101+100;
}



//Main Function
/*============================================================================*/
int main(int argc, char *argv[])
{
    //use current time as seed for random int generator
    srand(time(0));
    //initial values for for client's request structure
    DHCP_Request test;
    test.yiaddr="0.0.0.0";
    test.tid=gen_tid();
    test.ttl=TIMETOLIVE;


    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other), portno;
    char buf[BUFLEN];
    char message[BUFLEN];


    system("clear");
    printf("...This is UDP client...\n\n");

    //output initial values
    printf("Initialized Client Structure:\n");
    printf("[YIADDR]: %s\n",test.yiaddr);
    printf("[TID]: %d\n",test.tid);
    printf("[TTL]: %d\n",test.ttl);

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    portno = atoi(argv[1]); //The port on which to listen for incoming data
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(portno);
    si_other.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while(1)
    {
      // Sending the message to the server
      printf("Sending client's message : ");

      //convert transaction interger to c string.
      char c_tid[BUFLEN];
      char *c_tab = " ";
      //itoa(test.tid,c_tid,10);
      sprintf(c_tid,"%d", test.tid );

      //Assemble message to send to the server.
      strcpy(message, test.yiaddr);
      strcat(message, c_tab);
      strcat(message, c_tid);

      //gets(message);
      if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
      {
          die("sendto()");
      }

      //Receiving reply from server and printing it
      //clear the buffer by filling null, it might have previously received data
      bzero(buf, BUFLEN);
      if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
      {
         die("recvfrom()");
      }
      printf("Server has sent: %s\n", buf);
    }
    close(s);
    return 0;
}
