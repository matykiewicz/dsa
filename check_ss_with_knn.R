

n <- 100;
x1 <- cbind(rnorm(n,1,1));
x2 <- cbind(rnorm(n,1.5,1));
cl <- c(rep('a',n),rep('b',n));
dis <- as.matrix(dist(rbind(x1,x2)));

knn <- t(apply(dis,1,function(x){cl[sort(x,ind=T,dec=F)$ix]}));
knn_ratio <- t(apply(knn,1,function(x){sapply(seq(x),function(y){max(table(x[1:y]))/y  })}));

