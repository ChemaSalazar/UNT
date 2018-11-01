


// Jose Salazar
// Find the Sum and average of the first 'n' natural numbers. 
// User will input value for 'n'
// Created Feb 5 2017
// Part of Program 1

/* Program State
=====================================================
 Working. Last modification: added handling of non
 natural numbers.
=====================================================
*/

#include<stdio.h>


int main()
{
    // declaring all variables being used on program. 'n' is the total number of elements.
	int sum,n;
	double avg;

	
	//prompt user to input value of n
	printf("Enter a positive integer value for N: ");
	scanf("%d", &n);
    
    //this condition will execute with valid positive value for n.
    if (n > -1)
    {
    
        // This while loop will keep calling the sum function
        // until the counter is greater than the value of 'n'.
        sum = (n*(n+1))/2;
        avg = (double)sum/2;

        // Output results for sum and average.
        printf("Sum = %i\n", sum);
        printf("Avg = %f\n", avg);
        
    }
    
    //this condition handles negative values.
    else
    {
        printf("Sorry, your value must be a positive integer.\n");
    }
    
	return 0;
}



