READ ME
===============================================
JOSE SALAZAR
PROGRAM ASSIGNMENT 1
===============================================

CONTENTS:
	
	*JOSESALAZAR.ZIP //Contains 4 files.
	  
	  -CSCE2610_LEGv8.pdf
	  -factorial.c
	  -findsmallest.c
	  -sum.c
	
*PDF file contains program code for questions 4 and 5.
*C program files are exectued with the basic compiler method:

===============================================
	INSTRUCTIONS
===============================================


	COMPILING

commandline:	gcc factorial.c
commandline:	gcc sum.c
commandline:	gcc findsmallest.c

===============================================


	EXECUTING

commandline:	./a.out



	SAMPLE TEST CODE

===============================================
>For factorial.c:

jms0787@cse02:~/2610/p1$ gcc factorial.c 
jms0787@cse02:~/2610/p1$ ./a.out
Compute factorial of: 0
Result = 1
jms0787@cse02:~/2610/p1$ ./a.out
Compute factorial of: 5
Result = 120
jms0787@cse02:~/2610/p1$ ./a.out
Compute factorial of: 10
Result = 3628800
jms0787@cse02:~/2610/p1$ ./a.out
Compute factorial of: -5
Sorry, negative numbers do not have factorials!
===============================================
	
>For findsmallest.c:

jms0787@cse02:~/2610/p1$ gcc findsmallest.c 
jms0787@cse02:~/2610/p1$ ./a.out
Please enter the number of values to compare: 5
enter value for [1/5]: 0
Value must be a positive non-zero integer, scrapping value.
enter value for [1/5]: 3
enter value for [2/5]: -7
Value must be a positive non-zero integer, scrapping value.
enter value for [2/5]: 7
enter value for [3/5]: 0
Value must be a positive non-zero integer, scrapping value.
enter value for [3/5]: 10
enter value for [4/5]: 1
enter value for [5/5]: 8
MAX value= 10
MIN value= 1				
===============================================

>For sum.c:

jms0787@cse02:~/2610/p1$ gcc sum.c
jms0787@cse02:~/2610/p1$ ./a.out
Enter a positive integer value for N: -3
Sorry, your value must be a positive integer.
jms0787@cse02:~/2610/p1$ ./a.out
Enter a positive integer value for N: 0
Sum = 0
Avg = 0.000000
jms0787@cse02:~/2610/p1$ ./a.out
Enter a positive integer value for N: 12
Sum = 78
Avg = 39.000000
===============================================

	END OF READ ME.
