#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

void main(void){
pid_t pid;
pid = fork();

if(pid == 0)
{
	char * compile = "gcc -std=c11 project1a.c";
	char * run = "./a.out";
	system(compile);
	system(run);
}
else
{
	printf("Child one finished executing");	
}
}
