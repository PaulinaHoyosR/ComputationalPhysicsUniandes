#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_eigen.h>

int count_lines(char *filename);

int main (int argc, char** argv)
{

        //Abrir el archivo  
	FILE* file;
	file = fopen(argv[1], "r");

        //Dimensiones y medidas
	int dimensions;
	int measurements;
	
	measurements = 24;
	dimensions = count_lines(argv[1]);

	//Diferentes matrices que se necesitan
	gsl_matrix* data = gsl_matrix_calloc (measurements, dimensions);
	gsl_matrix* covariance_matrix = gsl_matrix_calloc (dimensions, dimensions);
	gsl_matrix* eigenvectors = gsl_matrix_calloc (dimensions, dimensions);
	gsl_vector* eigenvalues =  gsl_vector_calloc (dimensions);

	gsl_matrix_fscanf (file, data);
	get_covariance_matrix(data, dimensions, measurements, covariance_matrix);
	get_eigen (covariance_matrix, eigenvalues, eigenvectors, dimensions);

	//Imprimir los 3 archivos que se piden
	print_file_eigenvectors (eigenvectors,dimensions);
	print_file_eigenvalues (eigenvalues,dimensions);
	print_file_chisquare(data, eigenvectors, measurements, dimensions);
}


double average (gsl_vector* vector, int size)
{
	int k;
	double average;
	average = 0;
	for(k = 0 ; k < size ; k++)
	{
		
		average += gsl_vector_get(vector,k);
	}
	average /= (size);
	
	return average;
}


double get_covariance(gsl_matrix* data, int i, int j, int n, int m)
{
	gsl_vector* d_i = gsl_vector_calloc (m);
	gsl_vector* d_j = gsl_vector_calloc (m);
	gsl_matrix_get_col (d_i, data, i);
	gsl_matrix_get_col (d_j, data, j);
	
	int k;
	double covariance;
	covariance = 0;
	for (k = 0 ; k < m ; k++)
	{	
		double d_ik = gsl_vector_get (d_i,k);
		double d_jk = gsl_vector_get (d_j,k);
		
		
		covariance +=((d_ik-average(d_i,m))*(d_jk-average(d_j,m)));
	}
	
	covariance /= (m-1);
	
	return covariance;
	
}

int get_covariance_matrix(gsl_matrix* data, int n, int m, gsl_matrix* answer)
{
	int i;
	int j;
	
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n; j ++)
		{
		
			gsl_matrix_set(answer, i , j ,get_covariance(data, i, j, n, m));
		}
	}
}

int count_lines(char *filename)
{
	FILE *in;
	int n_lines;
	int c;
		if(!(in=fopen(filename, "r")))
		{
    			printf("problem opening file %s\n", filename);
    			exit(1);
  		}

	n_lines = 0;
	
	do
	{
   		c = fgetc(in);
    		if(c=='\n')
    		{
      			n_lines++;
    		}
  	}
  	while (c!=EOF);
  	return n_lines;
}

int get_eigen (gsl_matrix* m,gsl_vector* eval, gsl_matrix* evec, int n)
{
 	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (n);
  
 	gsl_eigen_symmv (m, eval, evec, w);
  
 	gsl_eigen_symmv_free (w);
  
 	gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_ABS_DESC);

	return 0;
}

int print_file_eigenvectors (gsl_matrix* input, int dimensions)
{
	FILE *export;
	export = fopen("PaulinaHoyos_eigenvectors.dat", "w");
	gsl_matrix_swap_columns (input, 0, 2);
	
	int i;
	for(i=0;i<dimensions;i++){
	  fprintf(export, "%f %f %f %f %f %f %f %f %f %f \n" ,gsl_matrix_get (input, 0,i), gsl_matrix_get (input, 1,i), gsl_matrix_get (input, 2,i),gsl_matrix_get (input, 3,i), gsl_matrix_get (input, 4,i), gsl_matrix_get (input, 5,i), gsl_matrix_get (input, 6,i), gsl_matrix_get (input, 7,i), gsl_matrix_get (input, 8,i), gsl_matrix_get (input, 9,i));
	}
	return 0;
}

int print_file_eigenvalues(gsl_vector* input, int dimensions){
  
  	FILE *export;
	export = fopen("PaulinaHoyos_eigenvalues.dat", "w");
	
	int i;
	for(i=0;i<dimensions;i++){
	  fprintf(export,"%f \n", gsl_vector_get(input,i));
	}

	return 0;
}

int print_file_chisquare(gsl_matrix* data, gsl_matrix* eigenvec, int measurements, int dimensions){

  FILE *export;
  export = fopen("PaulinaHoyos_pca_chisquare.dat", "w");

  int i;
  for(i=0;i<measurements;i++){

    float a0;
    float a1;
    float a2;
    float a3;
    float a4;
    float a5;
    float a6;
    float a7;
    float a8;
    float a9;
    
    int j0;
    for(j0=0;j0<dimensions;j0++){
      a0 = a0 + gsl_matrix_get (data, i,j0)* gsl_matrix_get(eigenvec, 0,j0);
    }

    int j1;
    for(j1=0;j1<dimensions;j1++){
      a1 = a1 + gsl_matrix_get (data, i,j1)* gsl_matrix_get(eigenvec, 1,j1);
    }
 
    int j2;
    for(j2=0;j2<dimensions;j2++){
      a2 = a2 + gsl_matrix_get (data, i,j2)* gsl_matrix_get(eigenvec, 2,j2);
    }

    int j3;
    for(j3=0;j3<dimensions;j3++){
      a3 = a3 + gsl_matrix_get (data, i,j3)* gsl_matrix_get(eigenvec, 3,j3);
    }

    int j4;
    for(j4=0;j4<dimensions;j4++){
      a4 = a4 + gsl_matrix_get (data, i,j4)* gsl_matrix_get(eigenvec, 4,j4);
    }

    int j5;
    for(j5=0;j5<dimensions;j5++){
      a5 = a5 + gsl_matrix_get (data, i,j5)* gsl_matrix_get(eigenvec, 5,j5);
    }

    int j6;
    for(j6=6;j6<dimensions;j6++){
      a6 = a6 + gsl_matrix_get (data, i,j6)* gsl_matrix_get(eigenvec, 6,j6);
    }

    int j7;
    for(j7=7;j7<dimensions;j7++){
      a7 = a7 + gsl_matrix_get (data, i,j7)* gsl_matrix_get(eigenvec, 7,j7);
    }

    int j8;
    for(j8=0;j8<dimensions;j8++){
      a8 = a8 + gsl_matrix_get (data, i,j8)* gsl_matrix_get(eigenvec, 8,j8);
    }

    int j9;
    for(j9=0;j9<dimensions;j9++){
      a9 = a9 + gsl_matrix_get (data, i,j9)* gsl_matrix_get(eigenvec, 9,j9);
    }

    int k;
    float chi2;
    for(k=0;k<dimensions;k++){
      chi2 = chi2 + pow(gsl_matrix_get(data, i,k)- (a0*gsl_matrix_get(eigenvec, 0,k) + a1*gsl_matrix_get(eigenvec, 1,k) +  a2*gsl_matrix_get(eigenvec, 2,k) +a3*gsl_matrix_get(eigenvec, 3,k) + a4*gsl_matrix_get(eigenvec, 4,k) + a5*gsl_matrix_get(eigenvec, 5,k) +  a6*gsl_matrix_get(eigenvec, 6,k) + a7*gsl_matrix_get(eigenvec, 7,k) + a8*gsl_matrix_get(eigenvec, 8,k) + a9*gsl_matrix_get(eigenvec, 9,k)),2);
    }


   fprintf(export,"%f \n", chi2/dimensions);
 }
  
}

