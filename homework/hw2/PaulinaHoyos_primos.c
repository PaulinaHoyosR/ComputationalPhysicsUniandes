#include <stdio.h>
#include <stdlib.h>

void calculate(int num);



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


void calculate(int num){
  printf("hola mundo\n");
  }
