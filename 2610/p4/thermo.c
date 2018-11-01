/*
Jose Salazar
Programming Assignment #4

Write a C program that converts temperature in Celsius to Fahrenheit and Kelvin.
Create a function that converts Celsius to Fahrenheit temperature. Create another
function that converts Celsius to Kelvin temperature. Use these functions in your
program and print the temperature in Fahrenheit and in Kelvin on the terminal console.
The input and output values are single precision floating-point values.

*/

//libraries
#include <stdio.h>

//function declariations
void CtoF (float a);  //Celsius to Fahrenheit
void CtoK (float a);  //Celsius to Kelvin

//main function
void main()
{
  //main variables
  float a;

  //prompt user for Celsius value and read input.
  printf("\n\nThis program is designed to convert Celsius temperature to Fahrenheit and Kelvin values.\n");
  printf("Please enter a temperature value in Celsius format: ");
  scanf("%f", &a);
  printf("Input temperature %fC\n", a);
  //run the conversion functions.
  CtoF(a);
  CtoK(a);

}

void CtoF(float a)
{
  a = (a*1.8+32);
  printf("%fF\n",a);


  //display new temperature in Fahrenheit format.
}

void CtoK(float a)
{
  a = (a+273.15);
  printf("%fK\n", a);


  //display new temperature in Kelvin format.
}
