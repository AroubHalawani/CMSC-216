#include <stdio.h>
#include <stdlib.h>
#ifndef wstring_graph_datastructure_h
#define wstring_graph_datastructure_h

typedef struct graph{
  int size;
  struct vertex *root;
  
} WString_graph;

typedef struct edge{
  struct vertex *vertex;
  struct edge *new_edge;
  int cost;
  
}Edge;

typedef struct vertex{
  struct vertex *new;
  Edge *list;
  char *name;

}Vertex;
#endif

