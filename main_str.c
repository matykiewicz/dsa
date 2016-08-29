#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

int GetVal ( char *this_str, int pos, int len ) {

  int val = 0;
  int i = 0;
  int c = 0;
  for ( i = 0; i < len; i++ ) {
    c = this_str[pos+i]-'0';
    if (c < 0 || c > 9) return -1;
    val = val * 10 + c;
  }
  return val;

}

int FindMissingNumber(char *str, int len) {
  // note: it's easy to get rid of the logs but the code is just 
  // not understandable with all those counters
  for (int m = 1; m <= 6; ++m) {
    int n = GetVal(str, 0, m);
    if (n == -1) break;
    int missingNo = -1;
    int fail = 0;
    for (int i = m; i != len; i += 1 + log10l(n)) {
      if ((missingNo == -1) && (GetVal(str, i, 1 + log10l(n + 2)) == n + 2))
      {
	missingNo = n + 1;
	n+=2;
      }
      else if (GetVal(str, i, 1 + log10l(n + 1)) == n + 1)
      {
	n++;
      }
      else 
      {
	fail = 1;
	break;
      }
    }
    if (!fail) return missingNo; 
  }
  return -1; // not found or no missing number
}



int main ( ) {  

  int i = 0;
  int r = 0;
  int R = 0;
  int dig = 7;
  int a[dig];
  char str[100];
  srand(time(NULL));
  r = rand()%9999+1;
  r = 2345;
  R = rand()%(dig-2)+1;
  for ( i = 0; i < dig; i++ ) {
    if ( i != R ) {
      a[i] = r;
    } else {
      a[i] = 0;
    }
    r++;
  }
  r = 0;
  for ( i = 0; i < dig; i++ ) {
    printf("%d ",a[i]);
    if ( a[i] > 1000 ) {
      sprintf(&(str[r]),"%d",a[i]);
      r += 4;
    } else if ( a[i] > 100 ) {
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
  R = FindMissingNumber(str,r);
  printf("\n%d len %d\n",R,r);

}
