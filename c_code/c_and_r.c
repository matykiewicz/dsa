
#include <R.h>
#include <Rdefines.h>
#include <stdio.h>
#include <stdlib.h>
#include "main_bst.c"

// https://github.com/b4winckler/reverse/blob/master/src/reverse.c
/* Take an int vector and reverse it. */

SEXP nothing(SEXP x)
{
  PROTECT(x = AS_INTEGER(x));
  int n = GET_LENGTH(x);
  if (n <= 0) {
    UNPROTECT(1);
    return R_NilValue;
  }

  const int *px = INTEGER_POINTER(x);

  UNPROTECT(2);
  return(x);
}

