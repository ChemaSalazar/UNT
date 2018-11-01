#include <sys/wait.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <stdlib.h>

void main(void){ 
//get parent process //
printf("\nParent process PID is: %d\n\n", getpid()); 

//some variables
 
int i = 0; 
int parentVar = 10; 
int x = 2; 
int c;

//open file
FILE *fp;
fp  = fopen("project1.txt", "r");

//default value int
printf("1. VARIABLES: Parent variable default value:%d\n\n", parentVar); 

//grab a char by ascii value
c = fgetc (fp);
printf("2. FILE DESCRIPTORS:\nChar retrieved by parent from file: %c\n\n", c);

pid_t pids[2]; 
for(i = 0; i < 2; i++)
{  
//if not child then fork
	if((pids[i] = fork()) < 0) 
	{ 
		perror("fork"); 
		abort();
	} 
//if child then 
	else if(pids[i] ==0)
	{
		switch(i){ 
		//child 1
			case 0:
                //add value to parentVariable, then display to screen.
                parentVar +=100; printf("Child 1: add 100 to parentVar:%d\n", parentVar);
                
                //initialize child variable (for children variable sharing between same parent)
                int childVar =50; printf("Child 1: childVar:%d\n", childVar);
				break;
		//child 2 
			case 1:
                //display shared variable from child 1
                printf("Child 2: childvar:%d\n", childVar);
                
				//read from file
				c = fgetc(fp);
				printf("Child 2: read char from file: %c\n", c); 
				break;
		}
	exit(0);
	}// else if
}

int status; 
pid_t pid; 
//wait for children to exit
//part 3 EXIT/WAIT
while(x > 0)
{ 
	pid = wait(&status); 
	--x;
}
//problem 1
printf("\n1. VARIABLES: Parent variable after children have ended:%d \nQuestion 1: end\n", parentVar);
c = fgetc(fp);
//problem 2
printf("2. FILE DESCRIPTORS: \nChar from file after children have ended: %c \nQuestion 2 end.\n", c); 
}//main
