
new_ll <- function ( ) {
  return(new.env(parent=emptyenv(),size=56L));
}

add_el <- function ( env, data ) {

  node <- new.env(parent=emptyenv(),size=NA);
  node$data <- data;
  if ( exists('right',envir=env) ) {
    node$right <- env$right;
    env$right <- node;
  } else {
    env$right <- node;
  }
  return(NULL);

}

add_el_at <- function ( env, data, n ) {

  node <- new.env(parent=emptyenv(),size=NA);
  node$data <- data;
  this_node <- env$right;
  i <- 0;
  if ( n == 1 ) {
    add_el(env,data);
  } else {
    while ( !is.null(this_node) && exists('data',envir=this_node) ) {
      i <- i + 1;
      if ( i == (n-1) ) {
	print(i);
	node$right <- this_node$right;
	this_node$right <- node;
	return(NULL);
      }
      this_node <- this_node$right;
    }
  }
  return(NULL);

}


print_el <- function ( env ) {

  this_node <- env$right;
  while ( !is.null(this_node) && exists('data',envir=this_node) ) {
    print(this_node$data);
    this_node <- this_node$right;
  }
  return(NULL);

}

