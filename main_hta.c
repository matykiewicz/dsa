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

// -- http://burtleburtle.net/bob/hash/doobs.html
// -- http://www.cse.yorku.ca/~oz/hash.html

unsigned long hash ( unsigned char *str ) {
  unsigned long hash = 5381;
  int c;
  while ( c = *str++ ) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}

void add_hta ( hta *this_hta, void *key, void *value ) {
}

//int hash_index (hash_t *h, void *key) {
//  int i = (int) key % h->size;
//  while ( h->keys[i] && h->keys[i] != key ) {
//    i = (i + 1) % h->size;
//  }
//  return i;
//}
//
//void hash_insert (hash_t *h, void *key, void *value) {
//  int i = hash_index(h, key);
//  h->keys[i] = key;
//  h->values[i] = value;
//}
//
//void *hash_lookup (hash_t *h, void *key) {
//  int i = hash_index(h, key);
//  return h->values[i];
//}

int main ( ) {

  // - - create
  hta *this_hta = create_hta(100);
  // - - destroy
  free(this_hta->values);
  free(this_hta->keys);
  free(this_hta);
  return(1);

}

