#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#ifndef _MAIN_TREE_C_
#define _MAIN_TREE_C_
#endif

typedef struct nodes {
  int index;
  int value;
} node;

typedef struct graphs {
  int n_nodes;
  node **nodes;
} graph;


graph *create_graph ( int n_nodes ) {
  int i = 0;
  graph *this_graph = NULL;
  this_graph = malloc(sizeof(graph));
  this_graph->n_nodes = n_nodes;
  this_graph->nodes = calloc(n_nodes,sizeof(node *));
  for ( i = 0; i < n_nodes; i++ ) {
    this_graph->nodes[i] = NULL;
  }
  return(this_graph);
}

void add_edge ( graph *this_graph, int n1, int n2, int v ) {
  int i = 0;
  if ( n1 < this_graph->n_nodes && n2 < this_graph->n_nodes ) {
    if ( this_graph->nodes[n1] == NULL ) {
      this_graph->nodes[n1] = malloc(2*sizeof(node));
      this_graph->nodes[n1][0].index = n2;
      this_graph->nodes[n1][0].value = v;
      this_graph->nodes[n1][1].index = -1;
      this_graph->nodes[n1][1].value = 0;
    } else {
      i = 0;
      while ( this_graph->nodes[n1][i].index > -1 ) {
	if ( this_graph->nodes[n1][i].index == n2 ) {
	  this_graph->nodes[n1][i].value = v;
	  return;
	}
	i++;
	this_graph->nodes[n1] = realloc(this_graph->nodes[n1],(i+2)*sizeof(node));
	this_graph->nodes[n1][i].index = n2;
	this_graph->nodes[n1][i].value = v;
	this_graph->nodes[n1][i+1].index = -1;
	this_graph->nodes[n1][i+1].value = 0;
      }
    }
  }
}

void print_graph ( graph *this_graph, int max_print ) {
  int i = 0;
  int j = 0;
  int edges = 0;
  if ( max_print > this_graph->n_nodes ) {
    max_print = this_graph->n_nodes;
  }
  for ( i = 0; i < max_print; i++ ) {
    j = 0;
    printf("%d:",i);
    if ( this_graph->nodes[i] != NULL ) {
      while ( this_graph->nodes[i][j].index > -1 ) {
	if ( this_graph->nodes[i][j].index < max_print ) {
	  printf(" %d=%d",this_graph->nodes[i][j].index,this_graph->nodes[i][j].value);
	  edges++;
	}
	j++;
      }
    }
    printf("\n");
  }
  printf("Edges: %d\n",edges);
}

int main ( int argc, char **argv ) {

  int size = 100;
  int n1 = 0;
  int n2 = 0;
  int v = 0;
  int i = 0;
  int j = 0;
  graph *this_graph = create_graph(size);
  srand(1234567);
  // - - add
  for ( i = 0; i < 3*size; i++ ) {
    n1 = rand()%size;
    n2 = rand()%size;
    v = rand()%size;
    add_edge(this_graph,n1,n2,v);
  }
  // - - print
  print_graph(this_graph,size);
  // - - cleanup
  for ( i = 0; i < this_graph->n_nodes; i++ ) {
    if ( this_graph->nodes[i] != NULL ) {
      j = 0;
      while ( this_graph->nodes[i][j].index > -1 ) {
	//free(this_graph->nodes[i][j]);
	j++;
      }
      //free(this_graph->nodes[i][j]);
      free(this_graph->nodes[i]);
    }
    //free(this_graph->nodes);
  }
  free(this_graph);

}

