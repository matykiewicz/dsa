
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct sbst {
  int x;
  struct sbst *left;
  struct sbst *right;
} bst;

void add_bst ( bst **bsts, int x ) {
  bst *new_bst = NULL;
  if ( *bsts != NULL ) {
    if ( x < (*bsts)->x ) {
      add_bst(&((*bsts)->left),x);
    } else {
      add_bst(&((*bsts)->right),x);
    }
  } else {
   new_bst = (bst *) malloc(sizeof(bst));
   new_bst->x = x;
   new_bst->left = NULL;
   new_bst->right = NULL;
   *bsts = new_bst;
  }
}

bst **min_bst ( bst **bsts ) {
  if ( (*bsts)->left != NULL ) {
    return(min_bst(&((*bsts)->left)));
  } else {
    return(bsts);
  }
}

bst **find_bst ( bst **bsts, int x ) {
  if ( bsts != NULL ) {
    if ( (*bsts)->x == x ) {
      return(bsts);
    } else if ( x < (*bsts)->x ) {
      return(find_bst(&((*bsts)->left),x));
    } else {
      return(find_bst(&((*bsts)->right),x));
    }
  } else {
    return(NULL);
  }
}

void delete_bst ( bst **bsts, int x ) {
  if ( bsts != NULL ) {
    if ( x < (*bsts)->x ) {
      if ( (*bsts)->left != NULL ) {
	delete_bst(&((*bsts)->left),x);
      }
    } else if ( x > (*bsts)->x ) {
      if ( (*bsts)->right != NULL ) {
	delete_bst(&((*bsts)->right),x);
      }
    } else {
      if ( (*bsts)->left == NULL && (*bsts)->right == NULL ) {
	free(*bsts);
	*bsts = NULL;
      } else if ( (*bsts)->left == NULL && (*bsts)->right != NULL ) {
	bst *temp = (*bsts)->right;
	(*bsts)->right = NULL;
	free(*bsts);
	*bsts = temp;
      } else if ( (*bsts)->left != NULL && (*bsts)->right == NULL ) {
	bst *temp = (*bsts)->left;
	(*bsts)->left = NULL;
	free(*bsts);
	*bsts = temp;
      } else {
	bst **temp = min_bst(&((*bsts)->right));
	(*bsts)->x = (*temp)->x;
	delete_bst(temp,(*temp)->x);
      }
    }
  } else {
    printf("Not found!\n");
  }
}

void print_bst ( bst *bsts, int level ) {
  int i = 0; // pre-order traversal
  if ( bsts != NULL ) {
    for ( i = 0; i < level; i ++ ) {
      printf("   ");
    }
    printf("%03d (%u %u %u)\n",bsts->x,(int) bsts, (int) bsts->left,(int) bsts->right);
    if ( bsts->left != 0 ) {
      print_bst(bsts->left,level+1);
    }
    if ( bsts->right != 0 ) {
      print_bst(bsts->right,level+1);
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

void sort_bst ( bst *bsts, int **result, int *location ) {
  int added = 0;
  if ( bsts != NULL ) {
    if ( bsts->left != NULL ) {
      sort_bst(bsts->left,result,location);
    } else {
      (*result)[*location] = bsts->x;
      *result = (int *) realloc(*result,(*location+2)*sizeof(int));
      (*result)[*location+1] = -1;
      (*location)++;
      added = 1;
    } 
    if ( !added ) { 
      (*result)[*location] = bsts->x;
      *result = (int *) realloc(*result,(*location+2)*sizeof(int));
      (*result)[*location+1] = -1;
      (*location)++;
    }
    if ( bsts->right != NULL ) {
      sort_bst(bsts->right,result,location);
    }
  }
}

// ====================================
// == USE ALL DATA STRUCTURES
// ====================================

int main ( ) {  

  int i = 0;
  int r = 0;
  bst *bsts = NULL; 
  bst **this_bst = NULL;
  srand(time(NULL));
  // - - create
  // - - add
  for ( i = 0; i < 15; i++ ) {
    add_bst(&bsts,rand()%30);
  }
  add_bst(&bsts,1);
  add_bst(&bsts,0);
  // - - print
  printf("%d - ",bsts->left->x);
  printf("%d - ",bsts->x);
  printf("%d\n",bsts->right->x);
  print_bst(bsts,0);
  printf("\n");
  // - - find bst
  this_bst = find_bst(&bsts,1);
  if ( this_bst != NULL ) {
    print_bst(*this_bst,0);
  } else {
    printf("Not found\n");
  }
  printf("\n");
  // - - delete bst
  delete_bst(&bsts,1);
  print_bst(bsts,0);
  printf("\n");
  delete_bst(&bsts,0);
  print_bst(bsts,0);
  printf("\n");
  for ( i = 0; i < 15; i++ ) {
    r = rand()%30;
    printf("Delete %d\n",r);
    delete_bst(&bsts,r);
  }
  print_bst(bsts,0);
  printf("\n");
  // - - sorting
  int *result = (int *) malloc(5*sizeof(int));
  int location = 0;
  result[0] = -1;
  result[1] = -1;
  sort_bst(bsts,&result,&location);
  print_da(result);
  // - - pause
  getchar();

}

