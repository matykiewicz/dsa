## ====

# a[i] = a[a[i]];

a_in = c(2,3,1,0)+1; # 3,4,2,1
a_out = c(1,0,3,2)+1; # 2,1,4,3

# a[1] = a[3] = 2
# a[2] = a[4] = 1
# a[3] = a[2] = 4
# a[4] = a[1] = 3
# a[1] = 3 + 5*2

repl <- function ( a_in ) {
  for ( i in seq(a_in) ) {
    a_in[i] = a_in[i] + (a_in[a_in[i]]%%(length(a_in)+1))*(length(a_in)+1);
  }
  for ( i in seq(a_in) ) {
    a_in[i] = a_in[i] - a_in[i]%%(length(a_in)+1);
    a_in[i] = a_in[i]/(length(a_in)+1);
  }
  return(a_in);
}
print(a_in);
print(repl(a_in));

## ====

a_in = c(2,3,1,4);
a_out = c(12,8,24,6);

# 2*3*1*4 = 24

mult <- function ( a_in ) {
  mul <- 1;
  for ( i in seq(a_in) ) {
    mul <- mul*a_in[i];
  }
  for ( i in seq(a_in) ) {
    a_in[i] <- mul/a_in[i]
  }
  return(a_in);
}
print(a_in);
print(mult(a_in));

## ====

a_in = c(1,3,5,18);

# 8 -> 1, 1+3, 1+3+5, 3+5
# 9 -> 1, 1+3, 1+3+5
# 10 -> 1, 1+3, 1+3+5, 1+3+5+18, 3+5+18, 5+18, 18
# 23 -> 1, 1+3, 1+3+5, 1+3+5+18, 3+5+18, 5+18

IsThereSub <- function ( ar, target ) {
  left <- 1;
  right <- 1;
  Sum <- 0;
  len <- length(ar);
  if ( target < min(ar) ) {
    return(FALSE);
  }
  while ( right <= len || left < len ) {
    if ( Sum < target && right <= len ) {
      Sum <- Sum + ar[right];
      right <- right + 1;
    }
    if ( Sum > target && left <= len ) {
      Sum <- Sum - ar[left];
      left <- left + 1;
    }
    if ( Sum < target && right > len && left == 1 ) {
      return(FALSE);
      break;
    }
    if ( Sum == target ) {
      return(TRUE);
      break;
    }
  }
  return(FALSE);
}
print(a_in);
print(IsThereSub(a_in,8));
print(IsThereSub(a_in,9));
print(IsThereSub(a_in,10));
print(IsThereSub(a_in,40));
print(IsThereSub(a_in,18));
print(IsThereSub(a_in,18+5));
print(IsThereSub(a_in,18+5+3));
print(IsThereSub(a_in,0));

