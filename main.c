
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

node **min_node ( node **nodes ) {
  if ( (*nodes)->left != NULL ) {
    return(min_node(&((*nodes)->left)));
  } else {
    return(nodes);
  }
}

node **find_node ( node **nodes, int x ) {
  if ( nodes != NULL ) {
    if ( (*nodes)->x == x ) {
      return(nodes);
    } else if ( x < (*nodes)->x ) {
      return(find_node(&((*nodes)->left),x));
    } else {
      return(find_node(&((*nodes)->right),x));
    }
  } else {
    return(NULL);
  }
}

void delete_node ( node **nodes, int x ) {
  
  if ( nodes != NULL ) {
    if ( x < (*nodes)->x ) {
      if ( (*nodes)->left != NULL ) {
	delete_node(&((*nodes)->left),x);
      }
    } else if ( x > (*nodes)->x ) {
      if ( (*nodes)->right != NULL ) {
	delete_node(&((*nodes)->right),x);
      }
    } else {
      if ( (*nodes)->left == NULL && (*nodes)->right == NULL ) {
	free(*nodes);
	*nodes = NULL;
      } else if ( (*nodes)->left == NULL && (*nodes)->right != NULL ) {
	node *temp = (*nodes)->right;
	(*nodes)->right = NULL;
	free(*nodes);
	*nodes = temp;
      } else if ( (*nodes)->left != NULL && (*nodes)->right == NULL ) {
	node *temp = (*nodes)->left;
	(*nodes)->left = NULL;
	free(*nodes);
	*nodes = temp;
      } else {
	node **temp = min_node(&((*nodes)->right));
	(*nodes)->x = (*temp)->x;
	delete_node(temp,(*temp)->x);
      }
    }
  } else {
    printf("Not found!\n");
  }

}

void print_node ( node *nodes, int level ) {
  int i = 0;
  if ( nodes != NULL ) {
    for ( i = 0; i < level; i ++ ) {
      printf("   ");
    }
    printf("%03d (%u %u %u)\n",nodes->x,(int) nodes, (int) nodes->left,(int) nodes->right);
    if ( nodes->left != 0 ) {
      print_node(nodes->left,level+1);
    }
    if ( nodes->right != 0 ) {
      print_node(nodes->right,level+1);
    }
  }
}


void print_da ( int *array ) {
  int i = 0;
  while ( array[i] != -1 ) {
    printf("%d ",array[i]);
    i++;
  }
  printf("\n");
}



void sort_node ( node *nodes, int *result, int *location ) {

  int added = 0;
  if ( nodes != NULL ) {
    if ( nodes->left != NULL ) {
      sort_node(nodes->left,result,location);
    } else {
      result[*location] = nodes->x;
      result = (int *) realloc(result,(*location+5)*sizeof(int));
      result[*location+1] = -1;

      printf("here1\n");
      printf("%d %d %u\n",nodes->x,*location,nodes);
      print_da(result);
      getchar();
      

      (*location)++;
      added = 1;
    } 



    if ( !added ) { 
      result[*location] = nodes->x;
      result = (int *) realloc(result,(*location+5)*sizeof(int));
      result[*location+1] = -1;

      printf("here2\n");
      printf("%d %d %u\n",nodes->x,*location,nodes);
      print_da(result);
      getchar();

      (*location)++;
      added = 1;
    }


    if ( nodes->right != NULL ) {
      sort_node(nodes->right,result,location);
    }


  }
}

// ====================================
// == USE ALL DATA STRUCTURES
// ====================================

int main ( ) {  

  int i = 0;
  int r = 0;
  node *nodes = NULL; 
  node **this_node = NULL;
  srand(time(NULL));
  // - - create
  // - - add
  for ( i = 0; i < 15; i++ ) {
    add_node(&nodes,rand()%30);
  }
  add_node(&nodes,1);
  add_node(&nodes,0);
  // - - print
  printf("%d - ",nodes->left->x);
  printf("%d - ",nodes->x);
  printf("%d\n",nodes->right->x);
  print_node(nodes,0);
  printf("\n");
  // - - find node
  this_node = find_node(&nodes,1);
  if ( this_node != NULL ) {
    print_node(*this_node,0);
  } else {
    printf("Not found\n");
  }
  printf("\n");
  // - - delete node
  delete_node(&nodes,1);
  print_node(nodes,0);
  printf("\n");
  delete_node(&nodes,0);
  print_node(nodes,0);
  printf("\n");
  for ( i = 0; i < 15; i++ ) {
    r = rand()%30;
    printf("Delete %d\n",r);
    delete_node(&nodes,r);
  }
  print_node(nodes,0);
  printf("\n");
  // - - sorting
  int *result = (int *) malloc(5*sizeof(int));
  int location = 0;
  result[0] = -1;
  result[1] = -1;
  sort_node(nodes,result,&location);
  print_da(result);
  // - - pause
  getchar();

}

