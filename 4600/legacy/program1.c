//Jose Salazar
//Homework 2
//Problem #4




#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>


/*
	This program will create child processes: 1 parent that forks
	2 children processes that will print out it's process ID and
	the parent's process ID. We will use some flags for one child
	process and other flags that will be run by the second child
	those two processes will then output the result to 2 text
	files P2_file.txt and P3_file.txt respectively. 

*/





void main(void) {

printf("Created parent process..\n\n");
printf("\nParent process, PID is : %d\n\n",getpid());

pid_t child_1, child_2; //initialize two child processes with data type pid_t


printf("Forking child process from parent..\n\n");
child_1 = fork();	//fork from parent to create child_1

if (child_1==0) //if child 1 equal zero, display ID and write result to text file.
{
	printf("\nChild#1 ID : %d  parent process ID: %d\n\n", getpid(), getppid());
	printf("Executing commands, and writing results to file: P2_file.txt\n\n");
	execl("/bin/sh", "sh", "-c", "ps -ael >> P2_file.txt", (char*)NULL);

}
else
{	
	printf("Forking second child from parent...\n\n");
	child_2 = fork();//fork from parent to create child_2
	printf("Waiting for parent process...\n\n");
	wait(NULL); //wait until we get the original process ID from the parent.
	if (child_2==0)// if child 2 equal zero, display ID and write result to text file
	{
		printf("\nChild#2 ID: %d   parent process ID: %d \n\n", getpid(), getppid());
		printf("Executing commands, and writing results to file: P3_file.txt\n\n");
		execl("/bin/sh", "sh", "-c", "ls >> P3_file.txt", (char*)NULL);

	}
}

printf("Program is finished.\n\n");
 //end of program
}
