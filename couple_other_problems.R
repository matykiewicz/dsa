## ==

# a[i] = a[a[i]];

a_in = c(2,3,1,0)+1; # 3,4,2,1
a_out = c(1,0,3,2)+1; # 2,1,4,3

# a[1] = a[3] = 2
# a[2] = a[4] = 1
# a[3] = a[2] = 4
# a[4] = a[1] = 3
# a[1] = 3 + 5*2

rep <- function ( a_in ) {
  for ( i in seq(a_in) ) {
    a_in[i] = a_in[i] + (a_in[a_in[i]]%%(length(a_in)+1))*(length(a_in)+1);
  }
  for ( i in seq(a_in) ) {
    a_in[i] = a_in[i] - a_in[i]%%(length(a_in)+1);
    a_in[i] = a_in[i]/(length(a_in)+1);
  }
  return(a_in);
}



