#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#ifndef _MAIN_SEARCH_C_
#define _MAIN_SEARCH_C_
#endif

void print_ar ( int *array, int size ) {
  int i = 0;
  for ( i = 0; i < size; i ++ ) {
    printf("%d ",array[i]);
  }
  printf("\n");
}

int linear_search ( int *array, int size, int x ) {
  int i = 0;
  for ( int i = 0; i < size; i++ ) {
    if ( array[i] == i ) {
      return(i);
    }
  }
  return(-1);
}

#ifndef _USE_IT_IN_R_

int main ( int argc, char **argv ) {
  int size = 30000;
  int nsearch = 100;
  int i = 0;
  int r = 0;
  clock_t start, end;
  int *array = calloc(size,sizeof(int));
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - search
  start = clock();
  for ( i = 0; i < nsearch; i++ ) {
    r = rand()%size;
    r = linear_search(array,size,r);
  }
  end = clock();
  printf("Search time: %lu\n",(end-start)/1000);
  // - - cleanup
  free(array);

}

#endif

