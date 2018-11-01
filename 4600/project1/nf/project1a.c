#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

void main(void){
//get parent process
//printf("parent process my PID is:%d\n", getpid());
//two childern


printf("question 1:\n");
int i = 0;
int pVar = 10;
char c, fp;
int n = 2;
printf("pVar in parent default value:%d\n", pVar);
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

switch(i)
{

	case 0:
	pVar +=100;
	printf("child 1: add 100 to pvar:%d\n", pVar);
	break;
	case 1:
	printf("child2 file descriptor\n");
	
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
	printf("pVar in parent after childern have ended:%d\nquestion 1: end\n", pVar);

}//main
