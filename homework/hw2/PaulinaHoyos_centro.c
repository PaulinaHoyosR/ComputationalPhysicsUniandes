#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int  count_lines(char* file);
float calculate_phi(float *x, float *y, float *z, int size, int i );


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

  /*calculate phi*/



 
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


float calculate_phi(float *X, float *Y, float *Z, int size, int i ){

  float phi=0;

  int j;
  for(j=0; j<size; ++j){
    if (i != j){

      float a = X[i]-X[j];
      float b = Y[i]-Y[j];
      float c = Z[i]-Y[j];
      float d = powf (a,2.0);
      float e = powf(b,2.0);
      float f = powf(c,2.0);
      float g = sqrt(d+e+f);
      float h = 1.0/g;

      phi = phi+h;
    }
  } 

return phi


}
