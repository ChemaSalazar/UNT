/* Compilation: gcc -o server server.c
   Execution  : ./server 5000
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    	int sockfd, newsockfd, portno, clilen, n;
   	struct sockaddr_in serv_addr, cli_addr;
    	char buffer[256];

	if(argc < 2)
	{

		printf("\nPort number is missing...\n");
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error(EXIT_FAILURE, 0, "ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		error(EXIT_FAILURE, 0, "ERROR binding");

	printf("\nServer Started and listening to the port %d\n", portno);
    	listen(sockfd, 5);

	while(1)
	{
		//Connecting with the client
    int vowels=0;
		clilen=sizeof(cli_addr);
		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
				error(EXIT_FAILURE, 0, "ERROR on accept");
		printf("\nClient is connected...\n");

    while(1){
		//Receiving the message from the client
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
	   	if(n < 0)
			error(EXIT_FAILURE, 0, "ERROR reading from socket");
	   	else
	   	{
        if (&buffer[0] == "quit")
        {
          printf("\nClient has disconnected.");
          close(newsockfd);

        }

          printf("\n Vowel function runs here.");
          for(int a=0; a < n; a++)
          {
            if (&buffer[a]=="a" || &buffer[a] == "e" || &buffer[a]=="i" || &buffer[a]== "o" || &buffer[a] == "u")
            {
              vowels++;
              printf("\nClient has sent: %s\n", &buffer[a]);
            }

          }
          printf("\n Counted %d vowels", vowels);
      }

      //if(buffer =="quit")
			//Sending the message to the client
			bzero(buffer,256);
		   	printf("\n Send vowels to client: ");
        //buffer[0] = vowels;
			scanf("%s", buffer);
      //puts(vowels);
        //snprintf(buffer, 10,"%d", vowels);
		   	n = write(newsockfd, buffer, strlen(buffer));
    }
			//Closing the connection
			close(newsockfd);

		}

		/*
		This section to contain the vowel counting function. We must make
		sure that the connection is kept open for the server to communicate
		back with the client.

		Once this is executed, we will listen for the client to send us a
		terminating command "Bye". This will let the server know when to
		close and terminate the communication between the programs.
		*/


		//TO DO: letsCountVowels(message)


	return 0;
}
