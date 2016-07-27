
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct nodes {
  int x;
  struct nodes *left;
  struct nodes *right;
} node;

void add_node ( node **nodes, int x ) {

  node *new_node = NULL;
  if ( *nodes == NULL ) {
   new_node = malloc(sizeof(node));
   new_node->x = x;
   new_node->left = NULL;
   new_node->right = NULL;
   *nodes = new_node;
  } else {
    if ( x < (*nodes)->x ) {
      add_node(&((*nodes)->left),x);
    } else {
      add_node(&((*nodes)->right),x);
    }
  }
}

void print_node ( node *nodes, char *pos ) {
  if ( nodes != NULL ) {
    printf("%s %d ",pos,nodes->x);
    if ( nodes->left != 0 ) {
      print_node(nodes->left,"l");
    }
    if ( nodes->right != 0 ) {
      print_node(nodes->right,"r");
    }
  }
}

// ====================================
// == USE ALL DATA STRUCTURES
// ====================================

int main ( ) {  

  int i = 0;
  node *nodes = NULL; 
  srand(time(NULL));
  // - - create
  // - - add
  for ( i = 0; i < 100; i++ ) {
    add_node(&nodes,rand()%100);
  }
  // - - print
  printf("%d - ",nodes->left->x);
  printf("%d - ",nodes->x);
  printf("%d\n",nodes->right->x);
  print_node(nodes,"h");
  // - - pause
  getchar();

}

