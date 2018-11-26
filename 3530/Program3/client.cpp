#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

#define SERVER "129.120.151.94" //IP address of server
#define TIMETOLIVE 3600 //time to live

typedef struct {
  string yiaddr;
  int tid;
  int ttl;
}DHCP_Request;

int gen_tid()
{
  return rand()%101+100;
}



//Client side
int main(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc != 3)
    {
        cerr << "Usage: something missing" << endl; exit(0);
    } //grab the IP address and port number
    char *serverIp = argv[1]; int port = atoi(argv[2]);
    //create a message buffer
    char msg[1500];
    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; //break;
    }
    cout << "Connected to the server!" << endl;

    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    //create a phase counter
    int phase = 1;
    //initialize client yiaddr value and transaction ID.
    DHCP_Request this_CLI;

    this_CLI.yiaddr = "0.0.0.0";
    this_CLI.tid = gen_tid();

    //loop communications
    while(1)
    {

        string data = this_CLI.yiaddr + " " + atoi(this_CLI.tid);
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;


        //clear the buffer
        memset(&msg, 0, sizeof(msg));
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        phase++;
        std::string temp;
        temp = msg;

        if((!strcmp(msg, "exit")) ||(!strcmp(msg, "quit")))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        //SERVER OFFER
        if(phase == 2)
        {
          cout << "[SERVER OFFER]: " << msg << endl;
          this_CLI.yiaddr = msg;
          cout << "[OFFER ACCEPTED]: this client's yiaddr is now : " << this_CLI.yiaddr << endl;
        }
        cout << "[Server msg]: " << msg << endl;

    }
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten <<
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec)
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;
}
