/*
===============================================================================
Name:		Jose Salazar
Program:	memcpy for homework 3
Class:		2610.001
Description:	recreate memcpy without using predefined functions or special
		libraries. This program imitates the pre-existing function by
		casting two arrays and passing a source array size to run a 
		copy from source to destination procedure controlled by a 
		for loop (utilizing the source array size).


Program state:	WORKING


===============================================================================
*/

//library includes
#include <stdio.h>



//create the memcpy_function prototype function.

void memcpy_function(void *Destination, void *Source, size_t x)
{
   // cast the source and destination array  addresses to type char *
   char *copySource = (char *)Source;
   char *copyDestination = (char *)Destination;
   int i; 
   // Copy from source to destination
   for ( i=0; i<x; i++)
       copyDestination[i] = copySource[i];
}


int main()
{
  //initialize arrays for testing
  char copyDestination[50];
  char copySource[]="abcdefg012345";
  
  //arr_size will contain the size of the source array
  size_t arr_size = *(&copySource+1) - copySource;  

  //call the memcpy_function
  memcpy_function(copyDestination, copySource, arr_size);
  //print results.
  printf("Copied c string value is now: %s\n ", copyDestination); 
  return 0;

}
