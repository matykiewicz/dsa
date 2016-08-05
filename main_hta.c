#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

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
// -- http://www.partow.net/programming/hashfunctions/

// unsigned long hash_str ( unsigned char *str, int size ) {
//   double hash = 0.1234;
//   int c;
//   int j=1;
//   int index;
//   while ( (c = *str++) ) {
//     hash = (hash + ((double) (c-64))/26)/2;
//     for ( int i = 0; i < j; i++ ) { 
//       hash = 3.999999*hash*(1-hash);
//     }
//     j++;
//   }
//   //printf("%.5f\n",hash);
//   index = (int) (hash*size);
//   return(index);
// }

int hash_str ( unsigned char *str, int size ) {
  unsigned long hash = 0;
  unsigned long c;
  int index = 0;
  while ( (c = *str++) ) {
    hash += (hash<<5) + c;
  }
  index = (int) (hash&size);
  return(index);
}

//unsigned long hash_str ( unsigned char *str ) {
//  double hash = 0;
//  double hashhash = 1;
//  int c;
//  int j=2;
//  while ( (c = *str++) ) {
//    hash = ((double) c)/255;
//    for ( int i = 0; i < j; i++ ) { 
//      hash = 3.9*hash*(1-hash);
//    }
//    j++;
//    hashhash = 10*hashhash + 300*hash;
//  }
//  return((unsigned long) hashhash);
//}

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
  int i = hash_str((unsigned char *) key,this_hta->size);
  this_hta->inserts++;
  if ( this_hta->keys[i] == NULL ) {
    this_hta->keys[i] = key;
    this_hta->values[i] = value;
  } else if ( strcmp(key,this_hta->keys[i]) != 0 ) {
    this_hta->collisions++;
  }
}

int find_hta (hta *this_hta, void *key) {
  int i = hash_str((unsigned char *) key,this_hta->size);
  return(this_hta->values[i]);
}

int main ( ) {

  int i = 0;
  int j = 0;
  int r = 0;
  int size = ((int) 0xFFFFF); printf("size %d\n",size);
  char *key = NULL;
  srand(123456);
  // - - create
  hta *this_hta = create_hta(size);
  // - - add 
  for ( i = 0; i < (int) (10000); i++ ) {
    r = rand()%11+4;
    key = (char *) calloc((r+1),sizeof(char));
    for ( j = 0; j < r; j++ ) {
      key[j] = (char) 65+(rand()%24);
    }
    key[r] = '\0';
    add_hta(this_hta,key,r);
  }
  printf("%s %d\n",this_hta->keys[1],this_hta->values[1]);
  printf("Collisions %f %d\n",(double) (((double) this_hta->collisions)/((double) this_hta->inserts)),this_hta->inserts);
  // - - find
  srand(123456);
  int not_found = 0;
  for ( i = 0; i < (int) (10000); i++ ) {
    r = rand()%11+4;
    key = (char *) calloc((r+1),sizeof(char));
    for ( j = 0; j < r; j++ ) {
      key[j] = (char) 65+(rand()%24);
    }
    key[r] = '\0';
    int f = find_hta(this_hta,key);
    if ( f != r ) {
      not_found++;
      printf("%s %d %d\n",key,r,f);
    }
  }
  printf("Not found %f %d\n",(double) (((double) not_found)/((double) this_hta->inserts)),not_found);
  // - - destroy
  for ( i = 0; i < this_hta->size; i++ ) {
    free(this_hta->keys[i]);
  }
  free(this_hta->values);
  free(this_hta->keys);
  free(this_hta);
  // - - pause
  return(1);

}

