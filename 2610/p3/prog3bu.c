/*
Jose Salazar
 
Write a C program to
compute y using recursion. Print the value of y on the console. The user inputs the
value of x and a. Assume these inputs are 64-bit, non-negative integers less than 9.
 
*/

#include <stdio.h>

//sum function that will be used to create the recursion strategy.
int square_sum(int n);

int main(){

    //declare variable
	int n;
    
    //prompt for user input then get user input
	printf("Enter a value:");
	scanf("%d", &n);
    
    //display the user input value along with the result of he recursion result.
	printf("The sum is : %d is =%d \n", n, square_sum(n));
}


//recursive call for sum of square.
int square_sum(int n){

	if (n == 0){
		return 0;
	}
	else{
		return ( square_sum(n-1)+(n*n));
	}
}
