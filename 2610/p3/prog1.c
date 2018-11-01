/*
Jose Salazar 
 
Write a C program to find the sum, mean, and range of n numbers. The user inputs the 
value of n followed by n 64-bit unsorted values. Assume the value of n is always a non-
zero positive number. Comment your C code. 
 
*/


#include <stdio.h>

//int get_sum(int n){};
//int range(){};


void main(){
	
	//declare variables
	int input,n,mean,sum=0,i=1;
	int min=0, max=0;
	//display userful information to user regarding how the program will work.
	printf("!This program is guaranteed to work using ONLY integer values!\n");
	printf("The value you input will be used to find value sums, mean, and range\n");
	printf("Desired number 'n':");
	scanf("%d", &input);

	//fetch n number of values given by input.
	for (i=1; i <= input; i++)
	{
		//we will display useful information to the user (current nth value/n).
		printf("Enter a value for [%d/%d]:", i, input);
		
		//'n' is the temporary variable for the nth user value.
		scanf("%d", &n);
		
		//in the following conditional statements
		//we will assign max and min values for all n values.
		
		if (i==1){
			max = n;
			min = n;
		}
		
		else if (n > max){
			max = n;
		}
		
		else if (n < min){
			min = n;
		}
		
		//printf("Current Min = %d | Max =%d\n", min, max);
		
		//for debug show the step
		//printf("Currently adding %d + %d \n", sum, n);
		
		sum+=n;
		
		//for debug show the result
		//printf("Sum value now = %d\n", sum);
	}
	
	//Display final sum
	printf("Final sum = %d\n", sum);
	
	//since we already calculated the summation of all n values, we just divide by input.
	
	//printf("Currently performing mean: [%d divided by %d]\n", sum,input);
	
	mean=sum/input;
	printf("Mean is = %d\n", mean);
	
	printf("Minumum = %d\n",min);
	printf("Maximum = %d\n", max);

	
}
