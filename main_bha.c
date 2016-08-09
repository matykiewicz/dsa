#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#ifndef _MAIN_BHA_C_
#define _MAIN_BHA_C_
#endif

void print_bha ( int *bhas ) {
  int size = bhas[0];
  int i = 0;
  for ( i = 1; i <= size; i++ ) {
    printf("%d ",bhas[i]);
  }
  printf("\n");
}

void siftup ( int **bhas, int child ) {
  int parent = floor(child/2);
  int temp = 0;
  if ( (*bhas)[parent] < (*bhas)[child] ) {
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
  *bhas = (int *) realloc(*bhas,(location+2)*sizeof(int));
  location++;
  (*bhas)[0] = location;
  (*bhas)[location] = x;
  if ( location > 1 ) {
    siftup(bhas,location);
  }
}

void siftdown ( int **bhas, int parent ) {
  int child_l = parent*2;
  int child_r = parent*2+1;
  int location = (*bhas)[0];
  int temp = 0;
  if ( ( child_l <= location && (*bhas)[parent] < (*bhas)[child_l] ) || ( child_r <= location && (*bhas)[parent] < (*bhas)[child_r] ) ) {
    if ( ( child_r <= location && (*bhas)[child_l] > (*bhas)[child_r] ) ) {
      temp = (*bhas)[parent];
      (*bhas)[parent] = (*bhas)[child_l];
      (*bhas)[child_l] = temp;
      if ( child_l < location ) {
	siftdown(bhas,child_l);
      }
    } else if ( child_r <= location ) {
      temp = (*bhas)[parent];
      (*bhas)[parent] = (*bhas)[child_r];
      (*bhas)[child_r] = temp;
      if ( child_r < location ) {
	siftdown(bhas,child_r);
      }
    } else if ( child_l <= location ) {
      temp = (*bhas)[parent];
      (*bhas)[parent] = (*bhas)[child_l];
      (*bhas)[child_l] = temp;
    }
  }
}

void delete_bha ( int **bhas, int x ) {
  int i = 1;
  int found = 0;
  int location = (*bhas)[0];
  while ( i <= location && found == 0 ) {
    if ( (*bhas)[i] == x && i != location ) {
      found = 1;
      (*bhas)[i] = (*bhas)[location];
      (*bhas)[location] = -1;
      location --;
      (*bhas)[0] = location;
      siftdown(bhas,i);
    } else if ( (*bhas)[i] == x && i == location ) {
      found = 1;
      (*bhas)[location] = -1;
      location--;
      (*bhas)[0] = location;
    }
    i++;
  }
}

int delete_first_bha ( int **bhas ) {
  int i = 1;
  int found = 0;
  int location = (*bhas)[0];
  int result = -1;
  if ( location > 0 ) {
    result = (*bhas)[1];
    (*bhas)[1] = (*bhas)[location];
    (*bhas)[location] = -1;
    location --;
    (*bhas)[0] = location;
    siftdown(bhas,1);
  }
  return(result);
}

void print_da ( int *array ) {
  int i = 0;
  while ( array[i] != -1 ) {
    printf("%d ",array[i]);
    i++;
  }
  printf("\n");
}

void sort_bha ( int **bhas, int **result ) {
  int i = 1;
  int location = (*bhas)[0];
  for ( i = 1; i <= location; i++ ) {
    (*result)[i-1] = delete_first_bha(bhas);
  }
}

#ifndef _USE_DSA_IN_R_
#ifndef _USE_BHA_IN_SEARCH_

int main ( ) {  

  int i = 0;
  int r = 0;
  // - - create
  int *bhas = (int *) malloc(1*sizeof(int)); 
  bhas[0] = 0;
  srand(time(NULL));
  // - - add
  for ( i = 0; i < 15; i++ ) {
    add_bha(&bhas,rand()%30);
  }
  // - - print
  print_bha(bhas);
  // - - delete
  for ( i = 0; i < 30; i ++ ) {
    delete_bha(&bhas,i);
  }
  print_bha(bhas);
  while ( bhas[0] > 0 ) {
    r = delete_first_bha(&bhas);
  }
  // - - print
  print_bha(bhas);
  // -- WIKI 6, 5, 3, 1, 8, 7, 2, 4 
  int array[8] = {6,5,3,1,8,7,2,4};
  for ( i = 0; i < 8; i++ ) {
    add_bha(&bhas,array[i]);
  }
  // - - print
  print_bha(bhas);
  // - - sort
  int *result = (int *) malloc((bhas[0]+1)*sizeof(int));
  result[bhas[0]] = -1;
  sort_bha(&bhas,&result);
  print_da(result);
  free(result);

  return(1);
 
}

#endif
#endif

