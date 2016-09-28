
## ======

## This is for debugging, R makes copies of objects for certain operation, it differs

address <- function ( x ) { sub('^(.+?) .+$','\\1',capture.output(.Internal(inspect(x,0)))[1]) }

## This is just to get references working - there no constrains to this data structure

Node <- function ( value ) { reference <- new.env(parent=emptyenv()); reference$value <- value; return(reference) };

## ======

create_bst_from_array <- function ( this_array ) {

  new_bst <- NULL;
## ---
  if ( length(this_array) ) {
    for ( element in this_array ) {
      new_bst <- insert_element(new_bst,element); ## passing and returning reference 
    }
  }
## ---
  return(new_bst);

}

## ======

insert_element <- function ( this_bst, element ) {

## ---
  if ( is.null(this_bst) ) {
    this_bst <- Node(element); ## create
  } else if ( class(this_bst) == 'environment' && element <= this_bst$value ) {
    this_bst$left <- insert_element(this_bst$left,element); ## passing and returning reference
  } else if ( class(this_bst) == 'environment' ) {
    this_bst$right <- insert_element(this_bst$right,element); ## passing and returning reference
  }
## ---
  return(this_bst);

}

## ======

traverse_in_order <- function ( this_bst ) {

  left <- NULL;
  right <- NULL;
  node <- NULL;
## ---
  if ( class(this_bst) == 'environment' ) {
    if ( !is.null(this_bst$left) ) {
      left <- traverse_in_order(this_bst$left); ## collects all values
    }
    node <- this_bst$value;
    if ( !is.null(this_bst$right) ) {
      right <- traverse_in_order(this_bst$right); ## collects all values
    }
  }
## ---
  return(c(left,node,right)); ## R will remove all NULLs

}

## ======

min_element <- function ( this_bst ) {

## ---
  if ( !is.null(this_bst$left) ) {
    min_element(this_bst$left);
  } else {
    return(this_bst$value);
  }
## ---

}

## ======

remove_element <- function ( this_bst, element, root ) {

## ---
  if ( !is.null(this_bst) && class(this_bst) == 'environment' ) {
    if ( element < this_bst$value ) {
      remove_element(this_bst$left,element,this_bst);
    } else if ( element > this_bst$value ) {
      remove_element(this_bst$right,element,this_bst);
    } else {
      if ( is.null(this_bst$left) && !is.null(this_bst$right) ) {
	tmp <- this_bst$right;
	this_bst$value <- tmp$value;
	this_bst$left <- tmp$left;
	this_bst$right <- tmp$right;
	tmp <- NULL;
      } else if ( is.null(this_bst$right) && !is.null(this_bst$left) ) {
	tmp <- this_bst$left;
	this_bst$value <- tmp$value;
	this_bst$left <- tmp$left;
	this_bst$right <- tmp$right;
	tmp <- NULL;
      } else if ( is.null(this_bst$left) && is.null(this_bst$right) ) {
	if ( identical(root$right,this_bst) ) {
	  root$right <- NULL;
	} else if ( identical(root$left,this_bst) ) {
	  root$left <- NULL;
	}
	this_bst <- NULL;
      } else {
	min_value <- min_element(this_bst$right);
	remove_element(this_bst$right,min_value,this_bst);
	this_bst$value <- min_value;
      }
    }
  }
## ---

}

## ======

cut_out_of_range_bst <- function ( this_bst, min_val, max_val, root ) {

## ---
  if ( !is.null(this_bst) && class(this_bst) == 'environment' && is.numeric(min_val) && is.numeric(max_val) && min_val <= max_val ) {
## -- post order
    if ( !is.null(this_bst$left) ) {
      cut_range_in_bst(this_bst$left,min_val,max_val,this_bst);
    }
    if ( !is.null(this_bst$right) ) {
      cut_range_in_bst(this_bst$right,min_val,max_val,this_bst);
    }
    if ( this_bst$value < min_val || this_bst$value > max_val ) {
## -- leaf node out of range
      if ( is.null(this_bst$left) && is.null(this_bst$right) ) {
	if ( identical(root$right,this_bst) ) {
	  root$right <- NULL;
	} else if ( identical(root$left,this_bst) ) {
	  root$left <- NULL;
	}
	this_bst <- NULL;
      } else {
## -- node in between two nodes out of range
	if ( !is.null(this_bst$left) && is.null(this_bst$right) ) {
	  tmp <- this_bst$left;
	  this_bst$value <- tmp$value;
	  this_bst$left <- tmp$left;
	  this_bst$right <- tmp$right;
	  tmp <- NULL;
	} else if ( !is.null(this_bst$right) && is.null(this_bst$left) ) {
	  tmp <- this_bst$right;
	  this_bst$value <- tmp$value;
	  this_bst$left <- tmp$left;
	  this_bst$right <- tmp$right;
	  tmp <- NULL;
	} else {
## -- this does not happen because of post order delete
	}
      }
    }
  }
## ---

}


## ======

## TEST: source('binary_search_tree_as_env.R'); t <- proc.time(); bst <- create_bst_from_array(c(1,sample(1000))); arr <- traverse_in_order(bst); print(proc.time()-t);

## ======

