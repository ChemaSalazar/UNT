/*
Jose Salazar
CSCE 3530 Program 3
*/



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
using namespace std;

/*Global Arrays <-- cuz im being lazy*/
std::string IP_List[5]= {
  "192.168.10.0",
  "192.168.10.1",
  "192.168.10.2",
  "192.168.10.3",
  "192.168.10.4"
};

std::string Active_Clients[10][10]={" "};

/*GLobal variables <-- cuz im being MEGA lazy*/
std::string code; //responce code from header


class DHCP_Responce{
  string yiaddr;
  string tid;
  int ttl;
};


//Server side
int main(int argc, char *argv[])
{
    //for the server, we only need to specify a port number
    if(argc != 2)
    {
        cerr << "[INFO]: Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);
    //buffer to send and receive messages with
    char msg[1500];

    //string to contain the server -> client message.
    std::string data;


    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "[WARNING]: Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "[WARNING]: Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "[CONSOLE]: Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to
    //handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "[WARNING]: Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "[CONSOLE]: Connected with client!" << endl;
    //lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    //also keep track of the amount of data sent as well
    int bytesRead, bytesWritten = 0;
    int CLI_count = 0;
    DHCP_Responce This_RES[10];
    while(1)
    {
        //receive a message from the client (listen)
        cout << "[CONSOLE]: Awaiting client request..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);


        if((!strcmp(msg, "exit"))|| (!strcmp(msg, "quit")))
        {
            cout << "[CONSOLE]: Client has quit the session" << endl;
            break;
        }

        std::string temp;
        temp = msg;

        //NEW CLIENT
        if (temp.find("0.0.0.0") != std::string::npos)
        {
            cout << "[CONSOLE]: found '0.0.0.0' => {DISCOVER PHASE}!" << '\n';
            data = IP_List[0];
            cout << "[CONSOLE]: sending offer: " << IP_List[CLI_count] << endl;
            This_RES[CLI_count].yiaddr = IP_List[CLI_count];
            This_RES[CLI_count].tid = temp.substr(8,temp.length());
            This_RES[CLI_count].ttl = 3600;
            CLI_count++;
        }

        //CLIENT THAT ACCEPTED PREVIOUS UP OFFER
        if (temp.find(IP_List[CLI_count-1]) != std::string::npos)
        {
          //update this client on the array list
          /*This_RES[CLI_count-1].yiaddr = temp.substr(0,12);
          This_RES[CLI_count-1].tid = temp.substr(13, temp.length());
          This_RES[CLI_count-1].ttl = 3600;
          */
          cout << "[CONSOLE]: CLIENT ACCEPTED OFFER : " << IP_List[CLI_count-1] << endl;
        }

        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        //send the message to client
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);

        //clear the temp string buffer
        temp.clear();
    }
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
        << " secs" << endl;
    cout << "[CONSOLE]: Connection closed..." << endl;
    return 0;
}
