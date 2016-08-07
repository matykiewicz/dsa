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
  int skips;
  int inserts;
  char **keys;
  int *values;
} hta;

hta *create_hta ( int size ) {
  int i = 0;
  hta *h = calloc(1,sizeof(hta));
  h->keys = calloc(size+1,sizeof(void *));
  for ( i = 0; i < (size+1); i++ ) {
    h->keys[i] = NULL;
  }
  h->values = calloc(size+1,sizeof(int));
  h->size = size;
  h->collisions = 0;
  h->inserts = 0;
  h->skips = 0;
  return(h);
}

// -- http://burtleburtle.net/bob/hash/doobs.html
// -- http://www.cse.yorku.ca/~oz/hash.html
// -- http://www.partow.net/programming/hashfunctions/

int hash_str ( unsigned char *str, int size ) {
  unsigned long hash = 255;
  unsigned long c;
  int index = 1;
  while ( (c = *str++) ) {
    hash += (hash<<5) - c;
  }
  index = (int) (hash&size);
  return(index);
}

void add_hta ( hta *this_hta, char *key, int value ) {
  int i = hash_str((unsigned char *) key,this_hta->size);
  this_hta->inserts++;
  if ( this_hta->keys[i] == NULL ) {
    this_hta->keys[i] = key;
    this_hta->values[i] = value;
  } else if ( strcmp(key,this_hta->keys[i]) != 0 ) {
    this_hta->collisions++;
    i++;
    while ( this_hta->keys[i] != NULL ) {
      i++;
      if ( i > this_hta->size ) {
	i = 1;
      }
      this_hta->skips++;
    }
    this_hta->keys[i] = key;
    this_hta->values[i] = value;
  }
}

int find_hta (hta *this_hta, char *key) {
  int i = hash_str((unsigned char *) key,this_hta->size);
  while ( strcmp(key,this_hta->keys[i]) != 0 ) {
    i++;
    if ( i > this_hta->size ) {
      i = 1;
    }
  }
  return(this_hta->values[i]);
}

int main ( ) {

  int i = 0;
  int j = 0;
  int r = 0;
  int size = ((int) 0xFFFFF); printf("size %d\n",size);
  char *key = NULL;
  srand(1234567);
  // - - create
  hta *this_hta = create_hta(size);
  // - - add 
  for ( i = 0; i < (int) (size/2); i++ ) {
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
  printf("Skips %f %d\n",(double) (((double) this_hta->skips)/((double) this_hta->inserts)),this_hta->inserts);
  // - - find
  srand(1234567);
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
    free(key);
  }
  printf("Not found %f %d\n",(double) (((double) not_found)/((double) this_hta->inserts)),not_found);
  // - - destroy
  for ( i = 0; i < (this_hta->size+1); i++ ) {
    free(this_hta->keys[i]);
  }
  free(this_hta->values);
  free(this_hta->keys);
  free(this_hta);
  // - - pause
  return(1);

}

