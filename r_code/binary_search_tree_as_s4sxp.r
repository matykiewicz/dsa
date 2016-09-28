
## ======

## This is for debugging, R makes copies of objects if there is write, unless it's the misterous S4SXP object

address <- function ( x ) { sub('^(.+?) .+$','\\1',capture.output(.Internal(inspect(x,0)))[1]) }

## This is kind of equivalent of STURCT in C but in fact it creates a special S4SXP object that is handled differntly than anything else in R

Node <- setRefClass('Node',fields=list(value="ANY",left='ANY',right='ANY'),methods=list(initialize=function(value){.self$left=NULL;.self$right=NULL;.self$value=value}));

## ======

create_bst_from_array <- function ( this_array ) {

  new_bst <- NULL;
## ---
  if ( length(this_array) ) {
    for ( element in this_array ) {
      if ( is.null(new_bst) ) {
	new_bst <- insert_element(new_bst,element); ## can be called only once because it makes a copy
      } else {
	insert_element(new_bst,element); ## now we operate on the same instance of BST
      }
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
   this_bst$left <- insert_element(this_bst$left,element); ## create & copy
 } else {
   this_bst$right <- insert_element(this_bst$right,element); ## create & copy
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
    left <- traverse_in_order(this_bst$left);
  }
  node <- this_bst$value;
  if ( !is.null(this_bst$right) ) {
    right <- traverse_in_order(this_bst$right);
  }
## ---
  return(c(left,node,right)); ## R will remove all NULLs

}

## ======

## TEST: source('binary_search_tree_as_s4sxp.R'); t <- proc.time(); bst <- create_bst_from_array(c(1,sample(1000))); arr <- traverse_in_order(bst); print(proc.time()-t);

## ======

