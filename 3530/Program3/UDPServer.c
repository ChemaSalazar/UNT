/* Compilation: gcc -o UDPserver UDPserver.c
   Execution  : ./UDPserver <port_number> [eg. port_number = 5000, where port_number is the UDP server port number]
*/

//Import
/*============================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//Definitions
/*============================================================================*/
#define BUFLEN 512  //Max length of buffer
#define MAXCLIENT 10 //Max number of supported clients
#define TIMETOLIVE 3600 //Time to live

//Classes && Structs
/*============================================================================*/

typedef struct {
  char * yiaddr;
  int tid; //Transaction ID
  int ttl; //Time to live
}DHCP_Responce;

//Function Declarations && Implementations
/*============================================================================*/

void die(char *s)
{
    perror(s);
    exit(1);
}

void m(int x){

  //more messages to be added as program develops.
  switch(x)
  {
    case 0 :
      printf("[STATUS]: Success\n");
      break;
    case 1 :
      printf("[STATUS]: Fail\n");
      break;
    case 2 :
      printf("[TASK]: DHCP Discovered\n");
      printf("[EVENT]: Client Is Requesting An IP Address\n");
      break;
    case 3 :
      printf("[TASK]: DHCP IP Address Offer Sent\n");
      break;
    case 4 :
      printf("[TASK]: DHCP Request Received\n");
      break;
    case 5 :
      printf("[TASK]: DHCP Acknowledgement Sent\n");
      break;
  }
}


void set_IP(int client)
{
  if(client >= MAXCLIENT)
  {
    m(1);
  }
  else
  {
    //TODO:
    //open file for IP address
    //check for available address
    //set address to current clients
    //update list of available addresses
    //close file
  }
  return;
}


//Main Function
/*============================================================================*/
int main(int argc, char *argv[])
{
    struct sockaddr_in si_me, si_other;

    int s, i, slen = sizeof(si_other) , recv_len, portno;
    char buf[BUFLEN], message[1024];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    portno = atoi(argv[1]); //The port on which to listen for incoming data

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    si_other.sin_addr.s_addr = inet_addr("0.0.0.0");

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

    system("clear");
    printf("...This is UDP server...\n\n");

    //keep listening for data
    while(1)
    {
        printf("Waiting for client's message...\n\n");
        fflush(stdout);

        //Receiving data from client
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");

        }
        m(2);
        //print details of the client/peer and the data received
        printf("Received packet from %s, port number:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Client has sent: %s\n", buf);

        //Sending reply to the client
	bzero(message, 1024);
	printf("Enter server's message:");
	gets(message);
        if (sendto(s, message, strlen(message), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");

        }
            m(3);
    }
    close(s);

    return 0;
}
