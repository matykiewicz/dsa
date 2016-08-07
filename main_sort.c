#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void print_ar ( int *array, int size ) {
  int i = 0;
  for ( i = 0; i < size; i ++ ) {
    printf("%d ",array[i]);
  }
  printf("\n");
}

void insert_sort ( int *array, int size ) {
  int i = 0;
  int j = 0;
  int t = 0;
  for ( i = 1; i < size; i++ ) {
    j = i-1;
    t = array[i];
    while ( j >= 0 && array[j] > t ) {
      array[j+1] = array[j];
      j--;
    }
    array[j+1] = t;
  }
}

int main ( int argc, char **argv ) {

  int size = 10000;
  int i = 0;
  clock_t start, end;
  int *array = calloc(size,sizeof(int));
  srand(time(NULL));
  // - - randomize
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,20);
  // - - sort
  start = clock();
  insert_sort(array,size);
  end = clock();
  print_ar(array,20);
  printf("time: %lu\n",(end-start)/1000);
  free(array);

}

