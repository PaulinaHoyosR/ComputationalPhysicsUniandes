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
  int* primos=malloc(1000*sizeof(int));
  int num_primos=0;

  int i;
  for(i=2; i<100; ++i){

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
  


    int p;
    for (p=0; p<10; p++){
      printf("%d\n", primos[p]);
    }

 
  
  return 0;
}
