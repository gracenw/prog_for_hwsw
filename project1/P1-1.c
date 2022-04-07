/*    Match Puzzle

This program finds the reference pattern in the candidates which might be
rotated or flipped.

Your name: Gracen Wallace
Date: 02/15/2019
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int  Reference;
  int  Candidates[8];
  int  NumCandidates;
  int  Position = 0; //temporary initial value
  int  Load_Reference(char *);
  int  Load_Mem(char *, int *);
  int  check_ar(int candi[],int refi[]); // initialize my function

  if (argc != 2) {
    printf("usage: ./P1-1 testfile\n");
    exit(1);
  }
  Reference = Load_Reference(argv[1]);
  if (Reference == 0) {
    printf("Invalid Reference pattern.\n");
    exit(1);
   }
  NumCandidates = Load_Mem(argv[1], Candidates);
   if (NumCandidates != 8) {
      printf("testfiles must contain 8 candidates\n");
      exit(1);
   }
  
/* BEGIN MY CODE */
   // load reference into array
   int ref[8]={ (Reference&0x0003),(Reference&0x000C)>>2,(Reference&0x0030)>>4,(Reference&0x00C0)>>6,(Reference&0x0300)>>8,(Reference&0x0C00)>>10,(Reference&0x3000)>>12,(Reference&0xC000)>>14 };
   // create all possible unique permutations of reference
   int H[8]={ref[6],ref[5],ref[4],ref[3],ref[2],ref[1],ref[0],ref[7]};		// flipped horizontally
   int V[8]={ref[2],ref[1],ref[0],ref[7],ref[6],ref[5],ref[4],ref[3]};		// flipped vertically
   int R90[8]={ref[6],ref[7],ref[0],ref[1],ref[2],ref[3],ref[4],ref[5]};	// rotated 90 degrees
   int R180[8]={ref[4],ref[5],ref[6],ref[7],ref[0],ref[1],ref[2],ref[3]};	// rotated 180 degrees
   int R270[8]={ref[2],ref[3],ref[4],ref[5],ref[6],ref[7],ref[0],ref[1]};	// rotated 270 degrees
   int HR90[8]={ref[0],ref[7],ref[6],ref[5],ref[4],ref[3],ref[2],ref[1]};	// flipped horizontally, rotated 90 degrees
   int VR90[8]={ref[4],ref[3],ref[2],ref[1],ref[0],ref[7],ref[6],ref[5]};	// flipped vertically, rotated 90 degrees
   // begin matching check
   for(int i=0;i<8;i++) {
	// load candidate into array
	int cand[8]={ (Candidates[i]&0x0003),(Candidates[i]&0x000C)>>2,(Candidates[i]&0x0030)>>4,
		      (Candidates[i]&0x00C0)>>6,(Candidates[i]&0x0300)>>8,(Candidates[i]&0x0C00)>>10,
		      (Candidates[i]&0x3000)>>12,(Candidates[i]&0xC000)>>14 };
	// check candidate array against all possible reference arrays
	if(check_ar(cand,ref) || check_ar(cand,H) || check_ar(cand,V) || check_ar(cand,R90) || check_ar(cand,R180) || check_ar(cand,R270) || check_ar(cand,HR90) || check_ar(cand,VR90) ) {
		Position=i;
		break;
	}
   }
/* END MY CODE */
  
  printf("The matching pattern is at position [0-7] %d\n", Position);
  exit(0);
}

/* BEGIN MY FUNCTION: checks arrays against each other, returns 1 if the arrays are the same, 0 otherwise */
int check_ar(int candi[],int refi[]) {
	int match=1;
	for(int h=0;h<8;h++) {
		if(candi[h]!=refi[h])
			match=0;
	}
	return match;
}
/* END MY FUNCTION */


/* This routine reads in one integer value from the first line of a named file in the local directory (each line of the file is in the form Addr: integer). The integer is returned. */

int Load_Reference(char *InputFileName) {
  int	Reference, NumVals, Addr, Value;
  FILE	*FP;

  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
    if (NumVals == 2)
      Reference = Value;
    else {
      printf("test file must contain Addr: Value pairs on each line.\n");
      Reference = 0;
    }
    fclose(FP);
    return Reference;
   }
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     fscanf(FP, "%d: %d", &Addr, &Value); // ignore first line
     for (N=0; N < 8; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 IntArray[N] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}
