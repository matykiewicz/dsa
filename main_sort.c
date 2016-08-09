#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#ifndef _MAIN_SEARCH_C_
#define _MAIN_SEARCH_C_
#endif

// - - http://stackoverflow.com/questions/1933759/when-is-each-sorting-algorithm-used

void print_ar ( int *array, int size ) {
  int i = 0;
  for ( i = 0; i < size; i ++ ) {
    printf("%d ",array[i]);
  }
  printf("\n");
}

// - - INSERT SORT

void insert_sort ( int *array, int size ) {
  int i = 0;
  int j = 0;
  int t = 0;
  for ( i = 1; i < size; i++ ) {
    j = i-1;
    t = array[i];
    while ( j >= 0 && array[j] > t ) {
      array[j+1] = array[j];
      j--;
    }
    array[j+1] = t;
  }
}

// - - SELECTION SORT

void selection_sort ( int *array, int size ) {
  int i = 0;
  int j = 0;
  int imin = 0;
  int t = 0;
  for ( i = 0; i < size; i++ ) {
    imin = i;
    for ( j = i+1; j < size; j++ ) {
      if ( array[imin] > array[j] ) {
	imin = j;
      }
    }
    t = array[i];
    array[i] = array[imin];
    array[imin] = t;
  }
}

// - - BUBBLE SORT

void bubble_sort ( int *array, int size ) {

 int i = 0;
 int t = 0;
 int n = size;
 char changed = 1;
  while ( changed ) {
    changed = 0;
    for ( i = 0; i < (n-1); i++ ) {
      if ( array[i] > array[i+1] ) {
	t = array[i];
	array[i] = array[i+1];
	array[i+1] = t;
	changed = 1;
      }
    }
    n--;
  }
}

// - - MERGE SORT

void buttom_up_merge ( int *a, int left, int right, int end, int *b ) {
  int i = left;
  int j = right;
  int k = 0;
  for ( k = left; k < end; k ++ ) {
    // - - 5,6 | 3,4 -> 3,4,5,6
    // - - 1,2 | 3,4 -> 1,2,3,4
    // - - 1,3 | 2,4 -> 1,2,3,4
    if ( i < right && ( j >= end || a[i] <= a[j] ) ) {
      b[k] = a[i];
      i++;
    } else {
      b[k] = a[j];
      j++;
    }
  }
}

void copy_array ( int *b, int *a, int size ) {
  int i = 0;
  for ( i = 0; i < size; i++ ) {
    a[i] = b[i];
  }
}

void buttom_up_merge_sort ( int *a, int *b, int size ) {
  int width = 1;
  int i = 0;
  for ( width = 1; width < size; width = 2*width ) {
    for ( i = 0; i < size; i = i+2*width ) {
      // - - 0-1,2-3 (width=2) -> 0,2,4
      buttom_up_merge(a,i,min(i+width,size),min(i+width*2,size),b);
    }
    copy_array(b,a,size);
  }
}

void merge_sort ( int *a, int size ) {
  int *b = calloc(size,sizeof(int));
  buttom_up_merge_sort(a,b,size);
  free(b);
}

// - - QUICK SORT

int partition ( int *a, int low, int high ) {
  int pivot = a[high];
  int i = low;
  int j = 0;
  int t = 0;
  for ( j = low; j < high; j++ ) {
    if ( a[j] <= pivot ) {
      t = a[i];
      a[i] = a[j];
      a[j] = t;
      i++;
    }
  }
  t = a[i];
  a[i] = a[high];
  a[high] = t;
  return(i);
}

void quick_sort ( int *a, int low, int high ) {
  int p = 0;
  if ( low < high ) {
    p = partition(a,low,high);
    quick_sort(a,low,p-1);
    quick_sort(a,p+1,high);
  }
}

// - - HEAP SORT

#define parent(i) (floor((i-1)/2))
#define left_child(i) (2*i+1)
#define right_child(i) (2*i+2)

void sift_down ( int *a, int parent, int end ) {
  int child_l = left_child(parent);
  int child_r = right_child(parent);
  int root = parent;
  int temp;
  int swap;
  while ( child_l <= end ) {
    swap = root;
    if ( a[swap] < a[child_l] ) {
      swap = child_l;
    }
    if ( child_r <= end && a[swap] < a[child_r] ) {
      swap = child_r;
    }
    if ( swap == root ) {
      return;
    } else {
      temp = a[root];
      a[root] = a[swap];
      a[swap] = temp;
      root = swap;
    } 
    child_l = left_child(root);
    child_r = right_child(root);
  }
}

void heapify ( int *a, int size ) {
  int start = parent(size-1);
  while ( start >= 0 ) {
    sift_down(a,start,size-1);
    start--;
  }
}

void heap_sort ( int *a, int size ) {
  int end = size-1;
  int temp;
  heapify(a,size);
  while ( end > 0 ) {
    temp = a[0];
    a[0] = a[end];
    a[end] = temp;
    end--;
    sift_down(a,0,end);
  }
}

#ifndef _USE_DSA_IN_R_

int main ( int argc, char **argv ) {

  int size = 30000;
  int i = 0;
  clock_t start, end;
  int *array = calloc(size,sizeof(int));
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - insertion sort
  start = clock();
  insert_sort(array,size);
  end = clock();
  print_ar(array,25);
  printf("Insert time: %lu\n",(end-start)/1000);
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - selection sort
  start = clock();
  selection_sort(array,size);
  end = clock();
  print_ar(array,25);
  printf("Selection time: %lu\n",(end-start)/1000);
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - bubble sort
  start = clock();
  bubble_sort(array,size);
  end = clock();
  print_ar(array,25);
  printf("Bubble time: %lu\n",(end-start)/1000);
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - merge sort
  start = clock();
  merge_sort(array,size);
  end = clock();
  print_ar(array,25);
  printf("Merge time: %lu\n",(end-start)/1000);
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - quick sort
  start = clock();
  quick_sort(array,0,size-1);
  end = clock();
  print_ar(array,25);
  printf("Quick time: %lu\n",(end-start)/1000);
  // - - - - - - -
  // - - randomize
  srand(1234567);
  for ( i = 0; i < size; i++ ) {
    array[i] = rand()%size;
  }
  print_ar(array,25);
  // - - heap sort


//int tarray[8] = {6,5,3,1,8,7,2,4};
//size = 8;

  start = clock();
  heap_sort(array,size);
  end = clock();
  print_ar(array,25);
  printf("Heap time: %lu\n",(end-start)/1000);
  // - - cleanup
  free(array);

}

#endif

