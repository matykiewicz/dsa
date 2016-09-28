## ======

## This is for debugging, R makes copies of objects for certain operation, it differs

address <- function ( x ) { sub('^(.+?) .+$','\\1',capture.output(.Internal(inspect(x,0)))[1]) }

## This is just to get references working - there no constrains to this data structure

Node <- function ( value ) { reference <- new.env(parent=emptyenv()); reference$value <- value; return(reference) };


