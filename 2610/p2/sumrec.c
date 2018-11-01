/*
===============================================================================
/	NAME: Jose Salazar
/	PROGRAM: sumrec.c
/	DESC: Sums up n natural numbers by using simple recursion.
/	LAST EDIT: 03/5/17
/	PROGRAM STATE: WORKING.
===============================================================================
*/




#include<stdio.h>


//summation function declaration
int dosum(int);

int main()
{
	//variables to hold user input and result
	int n, sum;
	
	//get user input
	printf("Enter an integer number:");
	scanf("%d", &n);
	//call the sum function
	sum=dosum(n);
	printf("Sum = %d\n", sum);


return 0;
}

int dosum(int n)
{
	//sum all positive values until n.
	if (n != 0)
	{
		return n + dosum(n-1);
	}
	//return value if n is zero.
	else
	{
		return n;
	}
	
}
