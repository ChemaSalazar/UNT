


// Jose Salazar
// This program will receive a user input value of 'n' and then compute
// the "factorial" result of that value; This program will implement
// a for-loop strategy not recursion.
// Created Feb 6 2017

/* Program State
 =====================================================
 Working.
 =====================================================
 */


#include <stdio.h>


int main()
{
	//initialize all variables.
	int n;
	int factorial=1;
	int i;

	//prompt user for value to compute, then read in value.
	printf("Compute factorial of: ");
	scanf("%i", &n);
    
    // First we check if the input is negative
	if(n < 0)
	{
		printf("Sorry, negative numbers do not have factorials!\n");
		return 0;
	}
    
	factorial=1;
	//start the for loop. decrementing until we reach value of 1 since that is just value*1
	for(i=1; i <= n; i++)
	{
		factorial*=i;
	}
	
    // Output result to the user.
	printf("Result = %i\n", factorial);

    return 0;
}
