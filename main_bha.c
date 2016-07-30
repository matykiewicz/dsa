#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct sbht {
  int x;
  struct sbht *left;
  struct sbht *right;
} bht;

void add_bht ( bht **bhts, int x ) {
  bht *new_bht = NULL;
  if ( *bhts != NULL ) {
   if ( x < (*bhts)->x ) {
      add_bht(&((*bhts)->left),x);
    } else {
      add_bht(&((*bhts)->right),x);
    }

  } else {
   new_bht = malloc(sizeof(bht));
   new_bht->x = x;
   new_bht->left = NULL;
   new_bht->right = NULL;
   *bhts = new_bht;
  }
}

void upheap ( bht **bhts, int x ) {
}

void print_bht ( bht *bhts, int level ) {
  int i = 0; // pre-order traversal
  if ( bhts != NULL ) {
    for ( i = 0; i < level; i ++ ) {
      printf("   ");
    }
    printf("%03d (%u %u %u)\n",bhts->x,(int) bhts, (int) bhts->left,(int) bhts->right);
    if ( bhts->left != 0 ) {
      print_bht(bhts->left,level+1);
    }
    if ( bhts->right != 0 ) {
      print_bht(bhts->right,level+1);
    }
  }
}

int main ( ) {  

  int i = 0;
  int r = 0;
  bht *bhts = NULL; 
  bht **this_bht = NULL;
  srand(time(NULL));
  // - - create
  // - - add
  for ( i = 0; i < 15; i++ ) {
    add_bht(&bhts,rand()%30);
  }
  // - - print
  print_bht(bhts,0);
 
}
