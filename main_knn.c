#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int main ( int argc, char **argv ) {

  for ( int i = 0; i < argc; i ++ ) {
    printf("Arg %d: %s\n",i,argv[i]);
  }
  if ( argc <= 1 ) {
    printf("Number of samples needed\n");
    return 1;
  }
  if ( argc <= 2 ) {
    printf("Overlap\n");
    return 1;
  }
  srand(1234567);
  return 0;

}
