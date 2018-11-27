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

/*Global Arrays*/
std::string IP_List[10]= {
  "192.168.10.0",
  "192.168.10.1",
  "192.168.10.2",
  "192.168.10.3",
  "192.168.10.4",
  "192.168.10.5",
  "192.168.10.6",
  "192.168.10.7",
  "192.168.10.8",
  "192.168.10.9"
};


std::string Active_Clients[10][10]={" "};

/*GLobal variables */
std::string code; //responce code from header
bool noMoreIP = false;

typedef struct{
  string yiaddr;
  string tid;
  int ttl;
}DHCP_Responce;

void init_File();

void mod_File(int CLI_count);


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
    system("clear");
    init_File();
    cout << "[SERVER]: Generated IPaddress.txt" << endl;
    cout << "[SERVER]: Listening for a client to connect.." << endl;
    while(1)
    {


/*
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

*/


        //receive a message from the client (listen)
        //cout << "[CONSOLE]: Awaiting client request..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);


        if((!strcmp(msg, "exit"))|| (!strcmp(msg, "quit")))
        {
            cout << "[CONSOLE]: Client has quit the session" << endl;
            cout << "****************" << endl;

            //ALL IP ADDRESSES HAVE BEEN USED!
            if(CLI_count > 9)
            {
              cout << "[CONSOLE]: All available IP addresses have been exhausted!" << endl;
              noMoreIP = true;
            }
            close(newSd);
            cout << "[SERVER]: Listening for a client to connect.." << endl;
            newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
            if(newSd < 0)
            {
                cerr << "[WARNING]: Error accepting request from client!" << endl;
                exit(1);
            }
            cout << "[CONSOLE]: New client has connected!" << endl;

            //break;
        }

        std::string temp;
        temp = msg;

        if (noMoreIP == true)
        {
          data ="ERROR";
          memset(&msg, 0, sizeof(msg));//clear the buffer
          strcpy(msg, data.c_str());
          bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
          cout << "[CONSOLE]: Terminating server program" << endl;
          cout << "[SYSTEM]: Cleaning up and Removing IPaddress.txt" << endl;
          system("rm IPaddress.txt");
          break;

        }

        //NEW CLIENT
        if ((temp.find("0.0.0.0") != std::string::npos) && (noMoreIP == false))
        {
            cout << "[DHCP DISCOVER]: client with yiaddr '0.0.0.0' has been discovered!" << '\n';
            data = IP_List[CLI_count];

            This_RES[CLI_count].yiaddr = IP_List[CLI_count];
            This_RES[CLI_count].tid = temp.substr(8,temp.length());
            This_RES[CLI_count].ttl = 3600;
            cout << "[DHCP DISCOVER]: This client has transaction id = " << This_RES[CLI_count].tid << endl;
            cout << "[DHCP OFFER]: sending offer: " << IP_List[CLI_count] << " to client #" << CLI_count << endl;
            mod_File(CLI_count);
            CLI_count++;
            memset(&msg, 0, sizeof(msg));//clear the buffer
            strcpy(msg, data.c_str());
            bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
        }

        //CLIENT THAT ACCEPTED PREVIOUS UP OFFER
        if ((temp.find(IP_List[CLI_count-1]) != std::string::npos)&&(noMoreIP == false))
        {
          //update this client on the array list
          /*This_RES[CLI_count-1].yiaddr = temp.substr(0,12);
          This_RES[CLI_count-1].tid = temp.substr(13, temp.length());
          This_RES[CLI_count-1].ttl = 3600;
          */
          cout << "[DHCP REQUEST]: CLIENT ACCEPTED OFFER = " << IP_List[CLI_count-1] << endl;
          cout << "[DHCP REQUEST]: transaction ID  = " << This_RES[CLI_count-1].tid << endl;
          cout << "[DHCP REQUEST]: Lifetime = " << This_RES[CLI_count-1].ttl << " secs" << endl;
          data = "DHCP ACK";
          cout << "[DHCP ACK]: ACK SENT to CLIENT" << endl;
          memset(&msg, 0, sizeof(msg));//clear the buffer
          strcpy(msg, data.c_str());
          bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
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
        //bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);

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


void init_File(){

  std::ofstream outfile;
  outfile.open("IPaddress.txt");
  for(int a=0; a < 10; a++)
  {
    outfile << IP_List[a] << "\n";
  }
  outfile.close();

  return;
}

void mod_File(int CLI_count){

  //IP_List[CLI_count] = "";
  std::string ToErase = IP_List[CLI_count];
  std::string line;
  std::ifstream infile;
  std::ofstream outfile;
  outfile.open("IPaddressNew.txt");
  infile.open("IPaddress.txt");
  while(getline(infile, line))
  {
    if (line == ToErase )
    {
      //do nothing
    }
    else
    {
      outfile << line << "\n";
    }
  }
  infile.close();
  outfile.close();
  system("rm IPaddress.txt");
  system("mv IPaddressNew.txt IPaddress.txt");

  return;
}
