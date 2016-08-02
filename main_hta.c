#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct {
  int size;
  void **keys;
  void **values;
} hta;

hta *create_hta ( int size ) {
  hta *h = calloc(1,sizeof(hta));
  h->keys = calloc(size,sizeof(void *));
  h->values = calloc(size,sizeof(void *));
  h->size = size;
  return(h);
}

int main ( ) {

  // - - create
  hta *this_hta = create_hta(100);
  // - - destroy
  free(this_hta->values);
  free(this_hta->keys);
  free(this_hta);
  return(1);

}

