#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


void print_bha ( int *bhas ) {
  int size = bhas[0];
  int i = 0;
  for ( i = 1; i <= size; i++ ) {
    printf("%d ",bhas[i]);
  }
  printf("\n");
}

void siftup ( int **bhas, int child ) {
  int parent = floor((child-1)/2)+1;
  int temp = 0;
  if ( (*bhas)[parent] > (*bhas)[child] ) {
    temp = (*bhas)[child];
    (*bhas)[child] = (*bhas)[parent];
    (*bhas)[parent] = temp;
    if ( parent > 1 ) {
      siftup(bhas,parent);
    }
  }
}

void add_bha ( int **bhas, int x ) {
  int location = (*bhas)[0];
  printf("%d \n",location);
  *bhas = (int *) realloc(*bhas,(location+2)*sizeof(int));
  location++;
  (*bhas)[0] = location;
  (*bhas)[location] = x;
  if ( location > 1 ) {
    siftup(bhas,location);
  }
}

void siftdown ( int **bhas, int *position ) {

}


void delete_bha ( int **bhas, int x ) {
}


int main ( ) {  

  int i = 0;
  int r = 0;
  int *bhas = (int *) malloc(1*sizeof(int)); 
  bhas[0] = 0;
  srand(time(NULL));
  // - - create
  // - - add
  for ( i = 0; i < 15; i++ ) {
    add_bha(&bhas,rand()%30);

  print_bha(bhas);
  getchar();

  }
  // - - print
  print_bha(bhas);
  // - - pause
  getchar();
 
}
