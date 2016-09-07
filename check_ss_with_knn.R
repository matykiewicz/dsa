## ----

create_2d_data <<- function ( n_small = 20, n_big = 10, d_small = 0.15, d_big = 0.45 ) {
  m_big   <- matrix(round(rnorm(n_big*n_big,d_big,0.05)),n_big,n_big);
  m_final <- NULL;
  class_lab <- NULL;
  for ( i in 1:nrow(m_big) ) {
    for ( j in 1:ncol(m_big) ) {
      if ( m_big[i,j] ) {
	m_final <- rbind(m_final,cbind(rnorm(n_small,i*1,d_small),rnorm(n_small,j*1,d_small)));
	class_lab <- c(class_lab,rep(c('A','B')[round(rnorm(1,d_big+0.05,0.15))+1],n_small));
      }
    }
  }
  print(paste('Dim',nrow(m_final),ncol(m_final)));
  m_final <- cbind(as.data.frame(m_final),CLASS=class_lab);
  return(m_final);
}

check_ratio <- function ( data_matrix ) {
  cl <- data_matrix[,3];
  dis <- as.matrix(dist(data_matrix[,1:2]));
  knn <- t(apply(dis,1,function(x){cl[sort(x,ind=T,dec=F)$ix]}));
  knn_ratio <- t(apply(knn,1,function(x){sapply(seq(x),function(y){max(table(x[1:y]))/y  })}));
  return(knn_ratio);
}
