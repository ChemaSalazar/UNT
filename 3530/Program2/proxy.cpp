/*
Jose Salazar
CSCE 3530 Program 2
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


//Function used to initialize the cache list.
void init_CacheList();
//Function used to modify cache list.
void mod_CacheList(int a, std::string msg);
//Function to check for appropriate URL or msg.
bool is_URL(std::string msg);
//Fuction that makes system call on behalf of client.
void telnetCall(std::string msg);

bool checkHeader(std::string msg);

void cleanUp(std::string msg);

/*Global Arrays*/
std::string cachedHistory[5];

/*GLobal variables*/
std::string code; //responce code from header









using namespace std;
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

    //prototype list of cached webpages. & a boolean to flag a hit of a cache or not.

    init_CacheList();
    bool hit = false;
    bool key;


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


        int copies, index, cnt = 0;
        bool wasEmpty = false;
        cout << "[CONSOLE]: Client Request: " << msg << endl;



        for(int x=cnt; x < 5; x++)
        {

          //msg matches x index on the list array.
          if(!strcmp(msg, cachedHistory[x].c_str()))
          {
            cout << "[CONSOLE]: Webpage: "  << msg << "=>" << cachedHistory[x] << " is already on the cache list!" << endl;
            hit = true; //hit toggle
            //copies++;
            cnt++;
            break;
          }

          //x index in array is empty AND there are more than one hit counts.
          else if(cachedHistory[x].empty())
          {
            wasEmpty = true;
            index = x;
          }
        }

        //reset hit counter
        cnt = 0;
        //write a new entry on the cachedHistory list if there was no hit. AND header 200 OK
        if (hit == false) //changed from && key ==true;
        {

          //if the array has content and no empty slots.
          if(wasEmpty==false)
          {
            telnetCall(msg);//run telnet
            key = checkHeader(msg);
            if (key == true)
            {
              mod_CacheList(0, msg);//modify the first entry on the array.
              cout << "[CONSOLE]: " << msg << " has been successully added to the 1st slot in the cache array!" << endl;
              data =  code;
            }
            else
            {
              cout << "[DEBUG]: " << msg << " has NOT been added to the cache array!" << endl;
              data =  code;
            }
            //cachedHistory[0] = msg; //LEGACY
          }

          //if array has content and an empty slot.
          else if(wasEmpty==true)
          {
            telnetCall(msg); //run telnet
            key = checkHeader(msg);
            if (key == true) //key is used to indicate a pass/fail on the 200 OK from checkHeader.
            {
              mod_CacheList(index, msg);//modify the nth entry on the array.
              cout << "[DEBUG]: " << msg << " has been added to slot: " << index + 1 << " of the cache array!" << endl;
              data =  code; //what the client will get
            }
            else
            {
              cout << "[DEBUG]: " << msg << " has NOT been added to the cache array!" << endl;
              data =  code; //what the client will receive.
            }
          }

        }

        if (hit == true)
        {
          data = "webpage is already in cache!";
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


        //reset hit and string for the next cycle.
        hit = false;
        key = false;
        wasEmpty = false;
        index = 0;
        data.clear();
        code.clear();

        //print the current cache list.
        cout << "\n ===== Current Cached List =====" << endl;
        for(int x=0; x < 5; x++)
        {
          cout << x+1 << " = " << cachedHistory[x] << endl;
        }
        cout << "\n ===============================" << endl;
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




void init_CacheList()
{
 //initialize empty. THIS WILL NOT BE DEFAULT.
 for (int a=0; a < 5; a++)
 {
   cachedHistory[a]="";
 }

 //The idea is to open the text file and loop its list to the cachedHistory array.
 if (std::ifstream("list.txt"))
 {
   //file exists
   cout << "[CONSOLE]: File 'list.txt' exists and has the following content:" << endl;

   //check if the file is empty.

   //ISSUE: RESOLVED
   /*
    I found that the following code reads in the text file and stores the content in
    the cachedHistory array, however the file is empty after termination of this
    program
    =======
    Turns out the section under this code 'DISABLED FOR TESTING' was the issue.
   */
   int index = 0;
   std::string content;
   std::ifstream file("list.txt");
   while(file >> content)
   {
     cout << content << endl;
     cachedHistory[index] = content; //saved into the cachedHistory array successfully
     index++;
   }

 }


 else
 {
   cout << "[CONSOLE]: list.txt does not exist, creating it now." << endl;
 }

 return ;
}

void mod_CacheList(int a, std::string msg)
{
  //First we will open or create the list.txt file, then we will modify the contents.
    std::string oldsite;
    oldsite = cachedHistory[a] + ".html";
    if ( ( !oldsite.empty() )|| ( !cachedHistory[a].empty() ) )
    {
      cleanUp(oldsite);
    }
    cachedHistory[a] = msg;

    std::string temp;
    std::ofstream outfile;
    outfile.open("list.txt");
    for(int a=0; a < 5; a++)
    {
      outfile << cachedHistory[a] << "\n";
    }
    outfile.close();

    //NOTES: UPDATED
    /*
      the int a value should be used as the "line" of the list.
      e.g.:
        if a = 0, then write to first entry.
        if a = 1, then write to second entry.
        ================
      10-16:
      checking will not be needed for the scope of this assignment.
      We will only modify the first entry in our file.

      Later versions of this program may include extended support for
      line-by-line modifications.

      For loop implementation works, however it may not be needed.
    */
  return ;
}

bool is_URL(std::string msg)
{
  //IMPLEMENTATION:
  /*
    if msg has www., then check that it also has .com,.edu,etc...

    if msg doesn't have .com,.edu, etc..
      bypass writing and clear buffer. Then notify the client.

    if msg is "quit"
      bypass writing and clear buffer, Signal to the client, then close
      connection.
  */

}

void telnetCall(std::string msg)
{
  //TODO:
  /*
    1. [COMPLETE] Make system call to execute the real telnet program.
    2. [COMPLETE] Send user msg to telnet (after being accepter by is_URL function).
    3. [COMPLETE] Take the output and write it to a new file, which will be <sitename>.<domain>.html.cache.
    4. We will check the header to see if the responce is 200 OK, else we remove the file.
    5. A message will be sent to the client to indicate whether pass or fail.
    6. If pass, continue to update the cachedHistory, if fail, we do not update the array.
  */

  //ISSUE: [RESOLVED]
  /*
    Right now this method of using system() below does not work the way i thought it would.
    For the first system(CMD.c_str()) the command works as expected, however
    the interface for telnet doesn't read or execute my other commands where i want
    telnet to take the GET request and Host: requests.

    Looking more into this, but i think this will require socket() for the program
    to work correctly.

    The html string output shows nothing, which means that nothing was really added to the
    variable after the last "\n" system().
  */

  //SOLUTION:
  /*
    I created a shell script that will automate telnet commands using the client's
    message as an argument.

    At the moment this works for all responces, a file is saved with .html extension.

    my idea is to open and read the saved file and parse through to find the responce
    code, and if it is NOT 200, then run a system ("rm <webpage.com.html>") to clean up.

  */

  std::string CMD;
  CMD = "sh get-cmd.sh " + msg + " | telnet > " + msg +".html";
  system(CMD.c_str());

  cout << "[FINISHED PROCESS]:" << endl;
  return ;
}

bool checkHeader(std::string msg)
{
  //TODO:
  /*
    1. Open the new created file
    2. Parse through for "HTTP/1.1 200 OK"  should be 5th Line
    3. Return TRUE for 200 OK
    4. Else return FALSE
    => use cleanUP(msg) to edit file or remove.
  */

  std::string line;
  std::string RES200;
  std::string url;
  bool ISOK = false;
  RES200 = "HTTP/1.1 200 OK";
  url = msg + ".html";
  std::ifstream unparsed(url.c_str());
  if(unparsed.is_open())
  {
    while(unparsed.good())
    {
      getline(unparsed,line);
      if(line == RES200)
      {
        cout << "200 OK" << endl;
        code = line;
        return true;
      }
      else if((line=="HTTP/1.1 301 MOVED PERMANENTLY")||(line =="HTTP/1.1 301 Moved Permanently")||(line == "HTTP/1.1 404 NOT FOUND") || (line =="HTTP/1.1 400 Bad Request") || (line == "HTTP/1.1 403 Forbidden") || (line == "HTTP/1.1 404 Not Found") || (line =="HTTP/1.1 302 Found") || (line =="HTTP/1.1 302 Object moved"))
      {

        code = line;
        cout << "***[RESPONCE]:" << code << endl;
        cleanUp(url);
        return false;
      }
      else if (line=="telnet> ?Invalid command")
      {
        code = line;
        cleanUp(url);
        return false;
      }
      //we can implement something to check for new permanent location.
      else
      {
        //cout << "NOT 200" << endl;
        cout << "[DISK]: " << line << endl;
        //IS_OK
      }
    }
    unparsed.close();

  }
  else
  {
    cout << "cannot open " << url << endl;
  }
  code = "Please try again, there was an error with your requested website.";
  return false;
}

void cleanUp(std::string msg)
{
  std::string del_cache;
  del_cache = "rm " + msg;
  system(del_cache.c_str());
  cout << "[SYSTEM]: Removed " << msg << endl;
 return ;
}
