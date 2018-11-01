
/*
 =================================================================
 Author:             Jose Salazar
 Description:        This program will create one child process
                     that will execute Project1A.c program within
                     child B1's code segment.
 =================================================================
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    //create child B1
	pid_t	B1;
    
	printf("==========START OF PROGRAM B==========\n");
	
    //fork process
    B1 = fork();
    
    //check for negative values
	if (B1 < 0) {
	
		fprintf(stderr, "Fork Failed");
		exit(-1);	

	}
    
    //this is child B1's code segment; which will execute Project1A.c program
	else if (B1 == 0 ){
	
		printf("Inside [B1]\n");
		printf("Execute Program here\n");
		printf("PROGRAM B\n");
        
        //execute external program
		system("gcc Project1A.c");		
		system("./a.out");
		printf("PROGRAM B\n");

	}
    
    //when heading to parent process
	else{

		printf("PROGRAM B\n");
        
        //allow to wait for process to finish
		wait(NULL);
        
        //at this point we are back as the parent process
		printf("Child Complete [PROGRAM B]\n");
		printf("Inside Parent [PROGRAM B]\n");
		printf("===========END OF PROGRAM B===========\n");		
		exit(0);
	}

	return 0;

}

