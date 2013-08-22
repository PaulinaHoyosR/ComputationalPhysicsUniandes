#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int  count_lines(char* file);


main(int argc, char * argv []){

  int n_lines = count_lines(argv[1]);

  /*arrays for the group of points in the three corrdinates*/
  float X[n_lines];
  float Y[n_lines];
  float Z[n_lines];

  /*give values to each Xi Yi Zi*/
  FILE *im = fopen(argv[1], "r");
  int i;
  for(i=0; i<n_lines; ++i){
    fscanf(im, "%f %f %f", &X[i], &Y[i], &Z[i]);
  }
  fclose(im);



 
 printf("%d\n" , n_lines);

  return 0;
}


/*counts the number of lines in the input file*/
int  count_lines(char* file){
  
  int n_lines = 0;

  FILE *in = fopen(file, "r");

  float a,b,c;
  while(fscanf(in, "%f %f %f", &a, &b, &c)==3)++n_lines;

  fclose(in);

  return n_lines;
}
