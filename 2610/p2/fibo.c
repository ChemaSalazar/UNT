/*
===================================================================================================
/	NAME: Jose Salazar
/	PROGRAM: fibo.c
/	DESC:Calculates fibbonacci sum using recursion of the fib function.
/	LAST EDIT: 02/23/17
/	PROGRAM STATE: WORKING.
===================================================================================================
*/






#include <stdio.h>

//function we will be using recursively
int fib(int);

int main()
{
	//n will be the variable being worked on, sum will store results after recursion
	int n, sum;
	

	//prompt user for value, then scan
	printf("Enter a value N to compute the fibonacci series:");
	scanf("%d", &n);
	

	//check if input is valid
	if (n < 0)
	{
		printf("Fibonacci of negative number is not possible, enter a positive int value\n");
	
	}
	//if valid run recusion and print result
	else
	{
		sum = fib(n);
		printf("series addition: (%d + %d)\n", fib(n-1), fib(n-2) );
		printf("The %d number in the Fib series is: %d\n", n, sum);
	
	}

	return 0;

}


//function receives data n then prints out or calls itself to get appropriate result.
int fib(int n)
{
	if (n == 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}
	//recursive calls adds previous 2 function values together
	else
	{
		return(fib(n-1)+fib(n-2));
	}

}
