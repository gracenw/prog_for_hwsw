/*    Color Matcher

This program finds the two closest colors in an array of packed RGB values,
based on the total component difference (computed as a sum of absolute
difference.) It prints the total component difference of the two closest colors.

Date: 02/01/2019
Your Name: Gracen Wallace
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /* you may change and add to these declarations and initializations */
  unsigned	Pixels[8];
  int	        NumPixels, MinDelta=-55;  // temporary initial value
  int Load_Mem(char *, unsigned *);

  if (argc != 2) {
    printf("usage: ./HW2-1 valuefile\n");
    exit(1);
  }
  NumPixels = Load_Mem(argv[1], Pixels);
  if (NumPixels != 8) {
    printf("valuefiles must contain 8 entries\n");
    exit(1);
  }

  int i;
  for(i=1;i<NumPixels;i++) {			//begin main loop 
    int B,G,R;					//delcare RGB variables
    B=Pixels[i] & 0xFF;				//initialize blue value 
    G=Pixels[i]>>8 & 0xFF;			//initialize green value
    R=Pixels[i]>>16 & 0xFF;			//initialize red value
    int j;
    for(j=0;j<i;j++) {				//begin loop to compare previous pixel values to the current
      int tempB,tempG,tempR;			//declare temp RGB variables
      tempB=Pixels[j] & 0xFF;			//initialize temp blue value
      tempG=Pixels[j]>>8 & 0xFF;		//initialize temp green value
      tempR=Pixels[j]>>16 & 0xFF;		//initialize temp red value
      int diffB,diffG,diffR,colorDiff;		//declare RGB difference variables and Color difference variable
      diffB=B-tempB;				//initialize blue difference value
      if(diffB<0) {				//if blue difference value is negative, multiply by -1 to find absolute value
	diffB*=(-1);  
      }
      diffG=G-tempG;				//initialize green difference value
      if(diffG<0) {				//if green difference value is negative, multiply by -1 to find absolute value
	diffG*=(-1);
      }
      diffR=R-tempR;				//initialize red difference value
      if(diffR<0) {				//if red difference value is negative,  multiply by -1 to find absolute value
	diffR*=(-1);
      }	
      colorDiff=diffB+diffG+diffR;		//initialize color difference value
      if(i==1 && j==0) {			//if this is the first comparison of colors, the temporary initial lowest difference is assigned to the current difference
	MinDelta=colorDiff;
      }
      else if(colorDiff<MinDelta) {		//if the current color difference is less than the previous lowest value, the lowest value is set to current color difference
	MinDelta=colorDiff;
      }
    }
  }
  
  printf("The two closest colors have a total component difference of %d\n", MinDelta);
  exit(0);
}

/* This routine loads in up to 8 newline delimited unsigned integers from
a named file in the local directory. The values are placed in the
passed unsigned integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, unsigned PixelArray[]) {
  int	N, Addr, NumVals;
  unsigned Value;
  FILE	*FP;
  
  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    for (N=0; N < 8; N++) {
      NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
      if (NumVals == 2)
	PixelArray[N] = Value;
      else
	break;
    }
    fclose(FP);
    return N;
  }
}

