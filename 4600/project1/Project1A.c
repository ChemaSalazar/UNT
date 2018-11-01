/*
=================================================================
Author:             Jose Salazar
Description:        This program has a parent process create
                    2 child processes. Output calls indicate 
                    Which program and or segment of the pro-
                    gram it is at.
=================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    //create child A1, A2
	pid_t	A1, A2;
	
    
	printf("==========START OF PROGRAM A==========\n");
    
    //fork processes this will be for A1
	A1 = fork();
    
    //check for negative values
	if (A1 < 0) {
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
    
    //this is the first child segment
	else if (A1 == 0 ){
		printf("Inside [A1]\n");
	}
    
    //this will be the segment for child 2 and parent return.
	else{
		printf("PROGRAM A\n");
		
        //fork from parent to create child_2
        A2 = fork();
		
        //allow process to wait
        wait(NULL);
        
        //this is child 2's code segment
		if (A2==0)
		{
			printf("PROGRAM A\n");
			printf("Inside [A2]\n");
		}
			
		printf("PROGRAM A\n");
		
        //allow to wait until child is done
		wait(NULL);
        
        //we are at the parent again.
		printf("Child Complete [PROGRAM A]\n");
		printf("Inside of Parent [PROGRAM A]\n");
		printf("===========END OF PROGRAM A===========\n");
		exit(0);
	}

	return 0;

}
