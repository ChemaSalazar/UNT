/*
  Jose Salazar
  2610 Programming Assignment #4 - Cosine function.
*/

//libraries
#include <stdio.h>

void cosine(int a, double x);
int fact(int n);
//functions
void main()
{
  int a;
  double x;

  printf("The calculation is done by Cos(X) = Summation from" );
  printf(" n=0 until n = a of (-1)^n * ((x^2n)/(2n)!)\n" );
  printf("Please enter value for a (between 0 and 16) \n" );
  scanf("%d",&a);
  printf("Great!, now enter a value x (between -5 and 5)\n" );
  scanf("%lf", &x );

  cosine(a,x);

}

void cosine(int a,double x)
{
  int n;
  double prev = x;
  for (n=0; n <= a; n ++)
  {
    x= (((double)x*(2*n/(fact(n))))*-1);
  }
  printf("COS(%lf) = %lf\n",prev,x);
}

int fact(int n)
{
    if(n==0)
    {
      return 1;
    }
    else
    {
      return(n * fact(n-1));
    }
}
