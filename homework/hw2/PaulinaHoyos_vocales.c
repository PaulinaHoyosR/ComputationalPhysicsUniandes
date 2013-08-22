#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){

  FILE *in = fopen(argv[1], "r");

  char c;
  int n_a=0;
  int n_e=0;
  int n_i=0;
  int n_o=0;
  int n_u=0;

  while(fscanf(in, "%c", &c)==1){
    if((c=='a' || c=='A'){++n_a;}
    else if (c=='e'  || c=='E' ){++n_e}
    else if (c=='i'  || c=='I' ){++n_i}
    else if (c=='o'  || c=='O' ){++n_o}
    else if (c=='u'  || c=='U' ){++n_u}
  }

  return 0;
}
