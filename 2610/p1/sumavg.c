//Jose Salazar
// Find the Sum and average of the first 'n' natural numbers. 
// User will input value for 'n'
// Created Feb 5 2017
// Part of Program 1

/* Program State
=====================================================
 Working. 
=====================================================
*/

#include<stdio.h>
//using namespace std;


int sumavg(int total, int counter);

int main()
{
	int counter=1;;
	int sum,total,n;
	double avg;
	sum = total = n = 0;
	
	//prompt user to input value of n
	printf("Enter an integer value of N: ");
	scanf("%d", &n);

	// This while loop will keep calling the sum function
	// until the counter is greater than the value of 'n'. 		
	while(n)
	{
		total=sumavg(total,counter); //assign current sum to total.
		avg=(double)total/n; // assign average from total by diving by 'n'.
		counter++; // counter serves as current working number.
		if (counter == n+1) // n+1 is the sential value to quit the loop.
		{
			//print results
			printf("Total sum = %d\n", total);
			printf("Sum average = %f\n", avg);
			break;
		}
	}

	return 0;
}


/* sumavg function
=====================================================
 This simple function will add the current total with
 the current counter value to create the current sum.
=====================================================
*/

int sumavg(int total, int counter)
{
	total+=counter;
	return total;
}
