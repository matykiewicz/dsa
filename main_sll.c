
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct ssll {
  int x;
  struct ssll *next;
} sll;

sll *create_sll ( int x ) {
  sll *this_sll = NULL;
  this_sll = malloc(sizeof(sll));
  this_sll->x = x;
  this_sll->next = NULL;
  return(this_sll);
}

void add_sll ( sll **this_sll, int x ) {
  sll *new_sll = NULL;
  new_sll = malloc(sizeof(sll));
  new_sll->x = x;
  if ( *this_sll != NULL ) {
    new_sll->next = *this_sll;
    *this_sll = new_sll;
  } else {
    new_sll->next = NULL;
    *this_sll = new_sll;
  }
}

void push_sll ( sll **this_sll, int x ) {
  sll *new_sll = NULL;
  new_sll = malloc(sizeof(sll));
  new_sll->x = x;
  new_sll->next = NULL;
  if ( *this_sll != NULL ) {
    sll *current = *this_sll;
    while ( current->next != NULL ) {
      current = current->next;
    }
    current->next = new_sll;
  } else {
    *this_sll = new_sll;
  }
}

int pop_sll ( sll **this_sll ) {
  int result = -1;
  sll *next_sll = NULL;
  if ( *this_sll == NULL ) {
    return(result);
  } else {
    result = (*this_sll)->x;
    next_sll = (*this_sll)->next;
    free(*this_sll);
    *this_sll = next_sll;
    return(result);
  }
}

void add_sll_at ( sll **this_sll, int x, int at ) {
  int i = 1;
  sll *new_sll = NULL;
  sll *current = NULL;
  if ( at == 0 || *this_sll == NULL ) {
    add_sll(this_sll,x);
  } else {
    current = *this_sll;
    while ( current->next != NULL && i < at ) {
      i++;
      current = current->next;
    }
    new_sll = malloc(sizeof(sll));
    new_sll->x = x;
    if ( current->next == NULL ) {
      new_sll->next = NULL;
      current->next = new_sll;
    } else {
      new_sll->next = current->next;
      current->next = new_sll;
    }
  }
}

int remove_sll_at ( sll **this_sll, int at ) {
  int i = 1;
  int result = -1;
  sll *current = NULL;
  sll *temp = NULL;
  if ( at == 0 || *this_sll == NULL ) {
    result = pop_sll(this_sll);
  } else {
    current = *this_sll;
    while ( current->next->next != NULL && i < at ) {
      i++;
      current = current->next;
    }
    if ( current->next->next == NULL ) {
      result = current->next->x;
      free(current->next);
      current->next = NULL;
    } else {
      temp = current->next;
      result = current->next->x;
      current->next = temp->next;
      temp->next = NULL;
      free(temp);
    }
  }
  return(result);
}

sll *find_sll ( sll *this_sll, int x ) {
  sll *current = this_sll;
  while ( current != NULL ) {
    if ( current->x == x ) {
      return(current);
    }
    current = current->next;
  }
  return(current);
}

void print_sll ( sll *this_sll ) {
  printf("sll: ");
  sll *current = this_sll;
  while ( current != NULL ) {
    printf("%02d ",current->x);
    current = current->next;
  }
  printf("\n");
}

int find_sll_at ( sll *this_sll, int x ) {
  int result = -1;
  sll *current = this_sll;
  while ( current != NULL ) {
    result++;
    if ( current->x == x ) {
      return(result);
    }
    current = current->next;
  }
  result = -1;
  return(result);
}

void bubble_sort ( sll **this_sll ) {
  int changed = 1;
  sll **current = NULL;
  sll *prev = NULL;
  sll *next = NULL;
  while ( changed == 1 ) {
    changed = 0;
    current = this_sll;
    while ( (*current)->next != NULL ) {
      if ( (*current)->x > (*current)->next->x ) {
	next = *current;
	prev = (*current)->next;
	next->next = (*current)->next->next;
	prev->next = next;
	*current = prev;
	changed = 1;
      } 
      current = &((*current)->next);
    }
  }
}

// ====================================
// == USE ALL DATA STRUCTURES
// ====================================

int main ( ) {  

  int r = 0;
  int i = 0;
  // - - create
  sll *this_sll = create_sll(0);
  srand(time(NULL));
  // - - add
  for ( i = 0; i < 100; i++ ) {
    add_sll(&this_sll,rand()%100);
  }
  // - - print
  print_sll(this_sll);
  // - - find
  for ( i = 0; i < 50; i++ ) {
    r = rand()%100;
    printf("Found %d at %d\n",r,find_sll_at(this_sll,r));
  }
  // - - sort
  bubble_sort(&this_sll);
  print_sll(this_sll);
  // - - find
  print_sll(find_sll(this_sll,0));
  // - - push
  push_sll(&this_sll,1);
  push_sll(&this_sll,1);
  // - - pop
  r = 0;
  printf("pop: ");
  while ( r != -1 ) {
    r = pop_sll(&this_sll);
    if ( r != -1 ) {
      printf("%02d ",r);
    }
  }
  printf("\n");
  // - - add at
  add_sll_at(&this_sll,1,0);
  add_sll_at(&this_sll,2,0);
  add_sll_at(&this_sll,3,0);
  add_sll_at(&this_sll,4,1);
  add_sll_at(&this_sll,5,1);
  add_sll_at(&this_sll,6,9);
  add_sll_at(&this_sll,7,9);
  print_sll(this_sll);
  // - - remove at
  printf("del : %02d\n",remove_sll_at(&this_sll,0));
  printf("del : %02d\n",remove_sll_at(&this_sll,9));
  printf("del : %02d\n",remove_sll_at(&this_sll,9));
  printf("del : %02d\n",remove_sll_at(&this_sll,2));
  printf("del : %02d\n",remove_sll_at(&this_sll,1));
  print_sll(this_sll);
  // - - pause
  getchar();

}

