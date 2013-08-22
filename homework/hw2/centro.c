#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int  count_lines(char* file);
float calculate_phi(float *X, float *Y, float *Z, int size, int i );


main(int argc, char** argv){

  int i,j,k,n_lines;
  float* x;
  float* y;
  float* z;
  float min_phi;
  float ac_phi;

  n_lines = count_lines(argv[1]);
 
  x = malloc(n_lines*sizeof(float));
  y = malloc(n_lines*sizeof(float));
  z = malloc(n_lines*sizeof(float));

  /*give values to each Xi Yi Zi*/
  FILE *im = fopen(argv[1], "r");
  int k;
  for(k=0; k<n_lines; ++k){
    fscanf(im, "%f %f %f\n", &(X[k]), &(Y[k]), &(Z[k]));
  }
  fclose(im);

  /*calculate minumun phi starting at first point*/
 for (j=1; j<n_lines; ++j){
      if (0 != j){

      float a = X[0]-X[j];
      float b = Y[0]-Y[j];
      float c = Z[0]-Y[j];
      float d = a*a;
      float e = b*b;
      float f = c*c;
      float g = d+e+f;
      float h = sqrt(g);
      float i = (1.0/g);

      min_phi = (phi+i);
      }
    }
 
  for(i=1; i<n_lines; ++i){
    for (k=1; k<n_lines; ++k){
      if (i != j){

      float a = X[i]-X[k];
      float b = Y[i]-Y[k];
      float c = Z[i]-Y[k];
      float d = a*a;
      float e = b*b;
      float f = c*c;
      float g = d+e+f;
      float h = sqrt(g);
      float i = (1.0/g);

      phi = (phi+i);
      }
    }
    float ac_phi = calculate_phi(X,Y,Z, n_lines,i);
    if (ac_phi >= min_phi){
      min_phi = ac_phi;
      p_min_phi = i;
    }
  }

  /*print the expected values*/
  printf("%f %f %f\n", X[p_min_phi], Y[p_min_phi], Z[p_min_phi]);

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


float calculate_phi(float X[], float Y[], float Z[], int size, int i ){

  float phi=0;

  int j;
  for(j=0; j<size; ++j){
    if (i != j){

      float a = X[i]-X[j];
      float b = Y[i]-Y[j];
      float c = Z[i]-Y[j];
      float d = a*a;
      float e = b*b;
      float f = c*c;
      float g = d+e+f;
      float h = sqrt(g);
      float i = (1.0/g);

      ++phi
    }
  } 

  return phi;
}
