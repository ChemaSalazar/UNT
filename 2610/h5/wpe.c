/*
  Jose Salazar

  Find Potential energy and weight given
  floating values of mass, height, and gravity.

*/

//libraries
#include <stdio.h>

//global constants
float gravity = 9.8; // m/s^2


void main()
{
  float mass, height;
  float potential_energy, weight;
  printf("\n\nPlease enter a mass (Kilograms):");
  scanf("%f", &mass);
  printf("\nPlease enter a height (meters):");
  scanf("%f",&height);

  //let's find weight.
  weight = mass*gravity;

  //now let's find Potential energy.
  potential_energy = weight * height;

  //finally we will display the results to the user.
  printf("\n ***RESULTS***\n\nweight = %f Kg*m/s^2\n\n", weight);
  printf("potential_energy = %f Joules\n\n", potential_energy );
}
