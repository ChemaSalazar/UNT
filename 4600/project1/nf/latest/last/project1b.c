#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

//here, we never wait for the child to stop executing, so parent closes without child wait, and all is well
//solves problem 4. TERMINATOR

//Code for Problem 5. Not implemented, but possible to use. This would need to be present in project1a.c as well
void signal_handler(int signum, siginfo_t *info, void *ptr)
{
    printf("SIGTERM received.\n");
}
void catch_signal()
{
    static struct sigaction signal;

    memset(&signal, 0, sizeof(signal));
  	signal.sa_sigaction = signal_handler;
    signal.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &signal, NULL);
}


//main
void main(void){
pid_t pid;

//fork process
pid = fork();

if(pid == 0)
{
	//compile project1a
	char * compile = "gcc -std=c11 project1a.c -o project1a";
	//run project1a as a child.
	char * run = "./project1a";
	system(compile);
	system(run);
}
//parent stuff
else
{
	printf("Child B1 finished executing\n");	
}
printf("Parent B exiting...\n\n");
}
