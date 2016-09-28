
## ======

## This is for debugging, R makes copies of objects for certain operation, it differs

address <- function ( x ) { sub('^(.+?) .+$','\\1',capture.output(.Internal(inspect(x,0)))[1]) }

## This is just to get references working - there no constrains to this data structure

Node <- function(value){reference <- new.env(parent=emptyenv()); reference$value <- value; return(reference) };

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
 } else if ( element <= this_bst$value ) {
   this_bst$left <- insert_element(this_bst$left,element); ## passing and returning reference
 } else {
   this_bst$right <- insert_element(this_bst$right,element); ## passing and returning reference
 }
## ---
  return(this_bst);

}

## ======

traverse_in_order <- function ( this_bst ) {

## ---
  left <- NULL;
  right <- NULL;
  if ( !is.null(this_bst$left) ) {
    left <- traverse_in_order(this_bst$left); ## collects all values
  }
  node <- this_bst$value;
  if ( !is.null(this_bst$right) ) {
    right <- traverse_in_order(this_bst$right); ## collects all values
  }
## ---
  return(c(left,node,right)); ## R will remove all NULLs

}

## ======

## TEST: source('binary_search_tree_as_env.R'); t <- proc.time(); bst <- create_bst_from_array(c(1,sample(1000))); arr <- traverse_in_order(bst); print(proc.time()-t);

## ======

