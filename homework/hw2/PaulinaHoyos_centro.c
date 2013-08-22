#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int  count_lines(char* file);
double  calculate_phi(double *X, double *Y, double *Z, int size, int i );


main(int argc, char* argv[]){

  int n_lines = count_lines(argv[1]);
 

  /*arrays for the group of points in the three coordinates*/
  double X[n_lines];
  double Y[n_lines];
  double Z[n_lines];


  /*give values to each Xi Yi Zi*/
  FILE *im = fopen(argv[1], "r");
  int k;
  for(k=0; k<n_lines; ++k){
    fscanf(im, "%lf %lf %lf\n", &(X[k]), &(Y[k]), &(Z[k]));
  }
  fclose(im);

  /*calculate minumun phi*/
  double min_phi = calculate_phi(X,Y,Z, n_lines, 0);
  int p_min_phi = 0;
  int i;
  for(i=1; i<n_lines; ++i){
    double ac_phi= calculate_phi(X,Y,Z, n_lines,i);
    if (ac_phi < min_phi){
      min_phi = ac_phi;
      p_min_phi = i;
    }
  }

  /*print the expected values*/
  printf("%lf %lf %lf\n", X[p_min_phi], Y[p_min_phi], Z[p_min_phi]);

  return 0;
}


/*counts the number of lines in the input file*/
int  count_lines(char* file){
  
  int n_lines = 0;

  FILE *in = fopen(file, "r");

  double a,b,c;
  while(fscanf(in, "%lf %lf %lf", &a, &b, &c)==3)++n_lines;

  fclose(in);

  return n_lines;
}


double calculate_phi(double X[], double Y[], double Z[], int size, int i ){

  double phi=0;

  int j;
  for(j=0; j<size; ++j){
    if (i != j){

      double a = X[i]-X[j];
      double b = Y[i]-Y[j];
      double c = Z[i]-Z[j];
      double d = a*a;
      double e = b*b;
      double f = c*c;
      double g = d+e+f;
      double h = sqrt(g);
      double w = (1.0/h);

      phi=-(phi+w);
    }
  } 

  return phi;
}
