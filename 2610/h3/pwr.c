/*
================================================================================
Name:		Jose Salazar
Program:	pwr.c
Class:		CSCE2610
Description:	Prototype function program that computers x^y without using
		any pre-defined functions. This is part of Homework # 3 (part1)
		the part 2 section is provided in the PDF file (problem 3).

Recent Changes:	Completed basic power arithmetic and logic.
Program State:	WORKING-Needs integer checking.
Notes:		If user inputs a negative integer value, the sign will be
		ignored and will be used as if it were postive integer value.
		This will not affect the end result, only the output segments.
================================================================================
*/

//Library includes

#include <stdio.h>

//Prototype Program

unsigned long long int pwr (unsigned long long int x,unsigned long long int y);

unsigned long long int pwr (unsigned long long int x, unsigned long long int y)
{
	int i;

	unsigned long long int temp=x;
	for (i=1; i < y; i++)
	{
		
		temp*=x;
		//printf("x's current value= %llu\n", temp);
	}
	//printf ("test: %llu\n", x);	
	x = temp;
	return x;
	
}

int main ()
{
	unsigned long long int x,y;
	int z=0;
	printf("Please enter a value for your base number 'x': ");
	scanf ("%llu", &x);
//	printf ("Test x= %llu\n", x);
	printf("Please enter a value for your power number 'y': ");
	scanf ("%llu", &y);
//	printf ("Test y= %llu\n", y);

	z=pwr(x,y);
	
	printf("result of %llu^%llu is = %d\n", x,y,z);
	
return 0;
}

