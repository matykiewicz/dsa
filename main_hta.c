#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct {
  int size;
  int collisions;
  int inserts;
  void **keys;
  int *values;
} hta;

hta *create_hta ( int size ) {
  int i = 0;
  hta *h = calloc(1,sizeof(hta));
  h->keys = calloc(size,sizeof(void *));
  for ( i = 0; i < size; i++ ) {
    h->keys[i] = NULL;
  }
  h->values = calloc(size,sizeof(int));
  h->size = size;
  h->collisions = 0;
  h->inserts = 0;
  return(h);
}

// -- http://burtleburtle.net/bob/hash/doobs.html
// -- http://www.cse.yorku.ca/~oz/hash.html

unsigned long hash_str ( unsigned char *str ) {
  unsigned long hash = 0;
  int c;
  while ( (c = *str++) ) {
    hash = (((hash<<5) + hash)) + c;
  }
  return(hash);
}



// unsigned long hash_str ( unsigned char *str ) {
//   unsigned long hash = 0;
//   int c;
//   while ( (c = *str++) ) {
//     hash += c;
//     hash += (hash << 10);
//     hash ^= (hash >> 6);
//   }
//   hash += (hash << 3);
//   hash ^= (hash >> 11);
//   hash += (hash << 15);
//   return(hash);
// }

//unsigned long hash_str ( unsigned char *str ) {
//  unsigned long hash = 5381;
//  int c;
//  while ( (c = *str++) ) {
//    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
//  }
//  return(hash);
//}

//unsigned long hash_str ( unsigned char *str ) {
//  unsigned long hash = 0;
//  int c;
//  while ( (c = *str++) ) {
//    hash = c + (hash << 6) + (hash << 16) - hash;
//  }
//  return(hash);
//}

void add_hta ( hta *this_hta, void *key, int value ) {
  unsigned long i = hash_str((unsigned char *) key);
  int j = (int) (i & this_hta->size);
  this_hta->inserts++;
  if ( this_hta->keys[j] == NULL ) {
    this_hta->keys[j] = key;
    this_hta->values[j] = value;
  } else {
    this_hta->collisions++;
  }
}

int find_hta (hta *this_hta, void *key) {
  unsigned long i = hash_str((unsigned char *) key);
  int j = (int) (i & this_hta->size);
  return(this_hta->values[i]);
}

int main ( ) {

  int i = 0;
  int j = 0;
  int r = 0;
  int size = ((int) 0xFFFFF); printf("size %d\n",size);
  char *key = NULL;
  srand(time(NULL));
  // - - create
  hta *this_hta = create_hta(size);
  // - - add 
  for ( i = 0; i < (int) (size/2); i++ ) {
    r = rand()%10+4;
    key = (char *) calloc((r+1),sizeof(char));
    for ( j = 0; j < r; j++ ) {
      key[j] = (char) 65+(rand()%24);
    }
    key[r] = '\0';
    add_hta(this_hta,key,r);
  }
  printf("%s %d\n",this_hta->keys[1],this_hta->values[1]);
  printf("Collisions %f %d",(double) (((float) this_hta->collisions)/((float) this_hta->inserts)),this_hta->inserts);

  // - - destroy
  for ( i = 0; i < this_hta->size; i++ ) {
    free(this_hta->keys[i]);
  }
  free(this_hta->values);
  free(this_hta->keys);
  free(this_hta);
  // - - pause
  getchar();
  return(1);

}

