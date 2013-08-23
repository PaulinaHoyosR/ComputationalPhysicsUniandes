#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculate(int num);

int main(int argc, char * argv[]){

  int n = sizeof(argv[1])/(2*sizeof(char));
  int  num = atoi(argv[1]);

 if(argv[1][0] == '-'){printf("El número es negativo\n"); }
 else if(num>1000000){ printf("El número es de un orden mayor a 10e6\n");}
 else {
    calculate(num);
 }

return 0;
}


int calculate(int num){

  /*lista con numeros primos*/
  int* primos=malloc(100000*sizeof(int));
  int num_primos=0;

  int i;
  for(i=2; i<100000; ++i){

    int esprimo=1;
    int k;
    for(k=2; (k*k)<=i && esprimo==1; ++k){
     
      if((i%k) == 0){
	  esprimo = 0;
        }
      }

    if (esprimo == 1){
	++num_primos;
	primos[num_primos-1]=i;
      }
  }


  
    /*ver si el numero de entrada da*/
    int m;
    int func =1;
    for(m=0; m<num_primos && func==1; m++){
      int g = primos[m];
      int h = num % g;
      if(h == 0){
	int r = num/g;
        int esprimod=1;
        int k;
        for(k=2; (k*k)<=i && esprimod==1; ++k){
     
            if((r%k) == 0){
	    esprimod = 0;
            }
         }

        if (esprimod == 1){
	  func=2;	 
          printf ("%d %d\n", g, r);
      }
	else { printf("El número no se puede descomponer como factor de dos primos\n");}

     
      func=2;
      }


    }



 
  
  return 0;
}
