


// Jose Salazar
// This program will compare given input and will find the max and min.
// number of compares will be done 'n' number of times.
// Created Feb 7 2017
// Part of Program 1


/* Program State
 =====================================================
 Working. Last modification: added condition to handle
 the value zero with error message.
 =====================================================
 */


#include <stdio.h>



int main ()
{
	//initialize all variables.	
	int n=0;	// this is the element count. Or number of compares.
	int max=0, min=0;// these values will be assigned to the current max or min 'n'.
	int i;
	int currentElement=0;
    
	//prompt user to input 'n' value, then read in the value.
	printf("Please enter the number of values to compare: ");
	scanf("%i", &n);
	
    //initialize the loop to compare values.
	for (i=1; i <= n; i++)
	{
		printf("enter value for [%i/%i]: ", i,n);
		scanf("%i", &currentElement);
		
		//the following conditions will assign the min or max values.
		//IF condition should initialize max and min as the first value of 'n'.
        //ELSE IF condition(s) compare the current element with the current max or min
        // depending on the compare results, a new max or min will be assigned.
	    if((i==1) || (currentElement < 1))
	    {
            	//if it happens that input value is valid, then set min and max
            	if(currentElement > 0)
            	{
                	max = currentElement;
                	min = currentElement;
            	}
            
            //otherwise don't store the value and we will decrement i value
            //to allow user to enter another value.
            else
            {
            	printf("Value must be a positive non-zero integer, scrapping value.\n");
            	i--;
            }
		
	    }
	    else if (currentElement > max)
	    {
		max = currentElement;
	    }	
	    else if (currentElement < min)
	    {
		min = currentElement;
	    }
        
        //added to handle negative and zero value(s); decrement is added
        //to allow user to try another input value.
            else if (currentElement < 1)
            {
          	 printf("Value must be a positive non-zero integer, scrapping value.\n");
            	 i--;
            }

	 }
	
	//Output the results
	printf("MAX value= %i\n", max);	
	printf("MIN value= %i\n", min);


	return 0;
}
