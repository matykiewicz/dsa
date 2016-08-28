#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int get_numb ( char *this_str, int pos ) {

  int i = 0;
  for ( i = 0; i < 3; i++ ) {
  }

}


int main ( ) {  

  int i = 0;
  int r = 0;
  int R = 0;
  int a[6];
  char str[100];
  srand(time(NULL));
  r = rand()%991+1;
  R = rand()%4+1;
  for ( i = 0; i < 6; i++ ) {
    if ( i != R ) {
      a[i] = r;
    } else {
      a[i] = 0;
    }
    r++;
  }
  r = 0;
  for ( i = 0; i < 6; i++ ) {
    printf("%d ",a[i]);
    if ( a[i] > 100 ) {
      sprintf(&(str[r]),"%d",a[i]);
      r += 3;
    } else if ( a[i] > 10 ) {
      sprintf(&(str[r]),"%d",a[i]);
      r += 2;
    } else if ( a[i] > 0 ) {
      sprintf(&(str[r]),"%d",a[i]);
      r += 1;
    }
  }
  printf("\n%s\n",str);
  r = get_numb(str,0);

}
