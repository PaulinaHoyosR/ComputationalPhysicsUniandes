#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_blas.h>
#include <math.h>

int count_lines(char *filename);
int write_g (gsl_vector* time, gsl_matrix* answer, int size);
int invert_matrix (gsl_matrix * m, gsl_matrix * inverse, int n);


int main (int argc, char** argv)
{	

        //Archivo con los puntos x_i, f_i
	FILE *file;
	file = fopen(argv[1], "r");

	//Numero de filas y columnas
	int n_rows, n_columns;

	n_rows = count_lines(argv[1]);
	n_columns = 2;

	//Grado del polinomio
	int pol_grad;

	pol_grad = atoi(argv[2]);

	//Matrices y vectores que se necesitan

	//Matriz con los datos del archivo
  	gsl_matrix *data = gsl_matrix_calloc (n_rows, n_columns);
  
  	//Matriz G
  	gsl_matrix *g = gsl_matrix_calloc (n_rows, pol_grad);
  	
  	//Matriz G^T 
  	gsl_matrix *g_trans = gsl_matrix_calloc (pol_grad,n_rows);
  	
  	//Matriz (G^T) * G Matrix
  	gsl_matrix *g_trans_times_g = gsl_matrix_calloc (pol_grad,pol_grad);
  	
  	//Matriz [(G^T) * G]^(-1) 
  	gsl_matrix *inverse = gsl_matrix_calloc (pol_grad,pol_grad);
  	
  	//Vector X_i 
  	gsl_vector *x_i = gsl_vector_calloc (n_rows);
  	
  	//Vector f_i
  	gsl_vector *f_i = gsl_vector_calloc (n_rows);
  	
  	// (G^T) * f_i  Vector
  	gsl_vector *g_trans_times_f_i = gsl_vector_calloc (pol_grad);
  	
  	//Vector m de parámetros óptimos
  	gsl_vector *m = gsl_vector_calloc (pol_grad);
  	
  	//Datos se cargan en la matriz de datos
  	gsl_matrix_fscanf (file, data);
  	
  	//Datos se dividen en los vectores x_i y f_i
  	gsl_matrix_get_col (x_i, data, 0);
  	gsl_matrix_get_col (f_i, data, 1);
  		
	//Se escribe la matriz G
	write_g (x_i, g, n_rows);
  	
  	//Se calcula la matriz (G^T) * G
  	gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1.0, g, g, 0.0, g_trans_times_g);
  
  	//Se invierte la matriz (G^T) * G y se salva en la matriz [(G^T) * G]^(-1)
  	invert_matrix (g_trans_times_g, inverse, pol_grad);
  	
	//Se calcula el vector (G^T) * d 
  	gsl_blas_dgemv (CblasTrans, 1.0, g, f_i, 0.0, g_trans_times_f_i);
  	
  	//Se calcula el vector m 
  	gsl_blas_dgemv (CblasNoTrans, 1.0, inverse, g_trans_times_f_i, 0.0, m);
  	
  	//Imprime los resultados en la pantalla
	int i;
	for(i=0;i<pol_grad;i++){ 
	  printf("a_ %d %f\n",i,gsl_vector_get (m, i));
	}

	//chi^2
	chi2(pol_grad,n_rows,f_i,x_i,m);
 
	return 0;
}


int write_g (gsl_vector* x_i, gsl_matrix* answer, int size)
{
	gsl_vector* one = gsl_vector_calloc( size );
	gsl_vector* x_i_squared = gsl_vector_calloc( size );

	gsl_vector_set_all (one, 1.0);
	gsl_vector_add (x_i_squared, x_i);
	gsl_vector_mul (x_i_squared, x_i);
  	gsl_vector_scale (x_i_squared, 0.5);

	gsl_matrix_set_col (answer, 0, one);
  	gsl_matrix_set_col (answer, 1, x_i);
  	gsl_matrix_set_col (answer, 2, x_i_squared);	
  	
  	return 0;
}

int invert_matrix (gsl_matrix * m, gsl_matrix * inverse, int n)
{

	int s;

	gsl_permutation * perm = gsl_permutation_alloc (n);

	gsl_linalg_LU_decomp (m, perm, &s);
	gsl_linalg_LU_invert (m, perm, inverse);

	return 0;
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

int chi2(int pol_grad, int N, gsl_vector* f_i, gsl_vector* x_i, gsl_vector* m){
 
  float acum;
  int i;

  acum=0;
 
  for(i=0;i<N;i++){
   acum= acum + (pow((gsl_vector_get(f_i,i))-fx_i(pol_grad,x_i,m),2));
  }

  printf("chi2 %f\n", acum/N);
  
}


int fx_i(int pol_grad, gsl_vector* x_i, gsl_vector* m){
  long double acum=0;
  int i;
  for(i=0;i<pol_grad;i++){
    acum= acum + (gsl_vector_get(m,i))*(pow((gsl_vector_get(x_i,i)),i));
  }
  return acum;
}
