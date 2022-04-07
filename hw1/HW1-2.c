/* ECE 2035 Homework 1-2

Your Name: Gracen Wallace
Date: 01/25/19

This is the only file that should be modified for the C implementation
of Homework 1.

This program computes and prints the union of two sets of 
ten integers, SetA and SetB.  It also prints the size of the union.
*/

#include <stdio.h>
#include <stdlib.h>

//DO NOT change the following declaration (you may change the initial value).
int SetA[] = {5, -19, 8, 26, 3, 6, -9, 17, 60, -63};
int SetB[] = {8, 11, -63, 18, 26, 17, 25, 12, -9, 60};
/*
For the grading scripts to run correctly, the above declarations
must be the first lines of code in this file (for this homework
assignment only).  Under penalty of grade point loss, do not change
these lines, except to replace the initial values while you are testing
your code.  

Also, do not include any additional libraries.
 */

int main() {
  int Size;
  Size=0; //initialize Size variable
  int i; //initiliaze main loop variable
  //begin main loop
  for(i=0;i<10;i++) {
	int checkA=0;
	int checkB=0;
	int j; //initialize SetA loop variable 
	for(j=0;j<=i;j++) {
		if(SetA[i]==SetB[j]) {
			checkA=1; //alter boolean if duplicate is found
		}
	}
	int k; //initialize SetB loop variable
	for(k=0;k<i;k++) {
		if(SetB[i]==SetA[k]) {
			checkB=1; //alter boolean if a duplicate is found
		}
	}
	if(checkA==0) {
		printf("%d: %d\n",Size,SetA[i]); //prints SetA element if no duplicates were found
		Size++; //increase Size
	}
	if(checkB==0) {
		printf("%d: %d\n",Size,SetB[i]); //prints SetB elemtn is no duplicares were found
		Size++; //increase Size
	}
  }
  printf("Union Set Size: %d\n", Size);
  return 0;
}
