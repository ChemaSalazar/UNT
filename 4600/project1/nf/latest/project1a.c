#include <sys/wait.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <stdlib.h>

void main(void){ 
//get parent process //
printf("parent process my PID is:%d\n", getpid()); 

//two childern printf("question 1:\n");
 
int i = 0; 
int pVar = 10; 
int n = 2; 
int c;

FILE *fp;
fp  = fopen("project1.txt", "r");
c = fgetc (fp);
printf("PARENT FILE DESCRIPTOR:\n Char retrieved by parent from file: %c\n\n", c);

printf("pVar in parent default value:%d\n\n", pVar); 
pid_t pids[2]; 
for(i = 0; i < 2; i++)
{ 
	if((pids[i] = fork()) < 0) 
	{ 
		perror("fork"); 
		abort();
	} 
	else if(pids[i] ==0)
	{
		switch(i){ 
			case 0: pVar +=100; printf("child 1: add 100 to pvar:%d\n", pVar);
				int cVar = 50; printf("child 1: cvar:%d\n",cVar); 
				break; 
			case 1: printf("child 2: cvar:%d\n",cVar);
				printf("CHILD FILE DESCRIPTOR: \n");
				c = fgetc(fp);
				printf("Child 2 read char from file: %c\n\n", c); 
				break;
		}
	exit(0);
	}// else if
}
int status; 
pid_t pid; 
while(n > 0)
{ 
	pid = wait(&status); 
	--n;
}
printf("pVar in parent after children have ended:%d\nquestion 1: end\n", pVar);
c = fgetc(fp);
printf("PARENT FILE DESCRIPTOR: \nChar from file after children have ended: %c\n Question 2 end.\n", c); 
}//main
