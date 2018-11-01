/*
  Jose Salazar
  2610 Programming Assignment #4 - Cosine function.
*/

//libraries
#include <stdio.h>

//global constants
float PI = 3.141592;


//functions
void main()
{
  int i;
  float a;
  float b=1;
  float x;
  float result=1;

  printf("The calculation is done by Cos(X) = Summation from" );
  printf(" b=1 until b = b of (-1)^x * ((i^2i)/(2i-1)!)\n" );
  printf("Please enter value for a (between 0 and 16) \n" );
  scanf("%f",&x);
  //convert degree into radian.
  x=x*(PI/180.0);
  printf("Great!, now enter a value x (between -5 and 5)\n" );
  scanf("%f", &a );

  for (i=1; i <= a; i++)
  {
    b=b*(-1)*x*x/(2*i*(2*i-1));
    result+=b;
  }

  //display results
  printf("COS = %f\n",result);

}
