/*
  The purpose of this project is to write a program that use
  dynamically allocated memory to store grap

*/
#include <stdio.h>
#include <string.h>
#include "wstring-graph.h"

/*
  The purpose of this function is initializing the graph 
  as an empty graph
*/
void init_graph (WString_graph *const graph) {

  if (graph == NULL) {
    return;
  }
  graph-> root = NULL;
  graph-> size = 0;
}

/*
  The purpose of this is to add a new vertex to the graph
*/
int new_vertex_add (WString_graph *const graph, const char new_vertex[]) {

  /* Helping variables */
  Vertex *temp_vertex = malloc(sizeof(Vertex));
  Vertex *current_vertex = graph-> root;
  Vertex *previos_vertex = NULL;

  /* returning 0 if the graph or the vertex is NULL*/
  if (graph == NULL  || new_vertex == NULL) {
    return 0;
  }

  if (temp_vertex != NULL) {

    temp_vertex-> name = malloc (strlen(new_vertex)+1);
    strcpy (temp_vertex-> name, new_vertex);
    temp_vertex-> new = NULL;
  }

  if (current_vertex != NULL) { 

    while (current_vertex != NULL) {

      /* return 0 if the new_vertex already in the graph */
      if (strcmp(current_vertex-> name, new_vertex) == 0) {
	
	return 0;
      }
      previos_vertex = current_vertex;
      current_vertex = current_vertex->new;
    }
    
    previos_vertex->new = temp_vertex;
    graph->size++;
    
    return 1;
    
  } else {
    
    graph->root = temp_vertex;
    graph->size++;

    return 1;
  }
  
  return 0;
}

/* The purpose of this function is to return how 
   many vertices in the graph
*/
int num_vertices (const WString_graph *const graph) {
  return graph->size;
}

/* 
   The purpose of this function is to check if the name is existing 
   that is given in the graph or not
*/
int is_existing_vertex (const WString_graph *const graph, const char name[]) {

  /* helping variable */
  Vertex* current_vertex = graph->root;

  /* returning 0 if the pointer is NULL or the size is 0 */
  if (graph == NULL || graph->root == NULL ||
      name == NULL || graph->size == 0) {
    return 0;
  }

  /* going through the list to check if the vertex is exist or not */
  while (current_vertex != NULL) {

    /* returning 1 if the vertex is existing in the list */
    if (strcmp (current_vertex-> name, name) == 0) {
      return 1;
    }
    current_vertex = current_vertex-> new;
  }
  
  return 0; /* returning 0 since the vertex is not in the list */
}

/*
  The purpose of this function is to create a new dynamically
  allocated array of the graph 
*/
char **get_vertices (const WString_graph *const graph) {

  /* helping variables */
  char **answer = NULL;
  int index = 0;
  Vertex *current_vertex = graph->root;
  int var = 0;

  /* returing a dynamically allocated array if the graph is NULL */
  if (graph == NULL) {

    answer = malloc(sizeof(char));
    answer[index]= NULL;
    return answer;
  }

  /* counting how many element in the list */
  while (current_vertex != NULL) {
    index++;
    current_vertex = current_vertex->new;
  }

  /* increasing the size of the array since the last element is NULL*/
  answer = malloc(sizeof(char*)*(index+1));
  current_vertex = graph->root;
  index = 0;

  while (current_vertex != NULL) {

    if (index > 0) {

      var = index;

      while (var > 0 && strcmp(answer[var-1], current_vertex-> name) > 0) {
	/* store the name in a new dynamically allocate array */
	answer[var] = answer[var-1];
	var--;
      }
    }
    answer[var] = malloc(strlen(current_vertex-> name)*sizeof(char)+1);

    strcpy(answer[var], current_vertex-> name);

    index++;

    current_vertex = current_vertex->new;
  }		  

  answer[index] = NULL;/* initalizing the last element to NULL */
  
  return answer;
}

/* The purpose of this function is adding a new edge to the graph */
int add_edge (WString_graph *const graph, const char source[],
	      const char dest[], int cost) {

  /* helping variables */
  Vertex* current_vertex = graph->root;
  Edge* current_edge = NULL;
  Edge* temp_edge = malloc(sizeof(Edge));

  /* 
     returing 0 if the graph is NULL, the cost < 0 ,
     or the source or the dest is NULL 
  */
  if (graph == NULL || graph->root == NULL ||
      cost < 0 || source == NULL || dest == NULL) {

    return 0;
  }
  
  /* creat a new independent edge */
  if (temp_edge != NULL) {

    temp_edge->vertex = malloc(sizeof(Vertex));

    temp_edge->vertex->name = malloc(strlen(dest) + 1);

    strcpy(temp_edge->vertex->name, dest);

    temp_edge->cost = cost;

    temp_edge->new_edge = NULL;

  }  
  
  /* check if the graph contains the source */
  if (is_existing_vertex(graph,source) == 0) {
    new_vertex_add(graph,source);
  }

  /* check if the graph contain the dest */
  if (is_existing_vertex(graph,dest) == 0) {
    new_vertex_add(graph,dest);
  }  

  /* checking if there is already an edge going from source to dest */
  while (current_vertex != NULL) {

    if (strcmp(current_vertex->name, source) == 0) {

      current_edge = current_vertex->list;
      
      while (current_edge != NULL) {

	/* if there is an edge going from source to dest */
	if (strcmp(current_edge->vertex->name, dest) == 0) {

	  /* change the edge cost to the parameter cost and return 1 */
	  current_edge-> cost = cost;
	  return 1;
	}
	current_edge = current_edge->new_edge;
      }
      /* if there is not edge from the dest to source */
      temp_edge->new_edge = current_vertex->list;
      current_vertex->list = temp_edge;

      return 1;
    }
    current_vertex = current_vertex->new;
  }
  return 0;
}
/* 
   The purpose of this function is to return the cost of the edge in
   the graph that goes from the source to the dest 
*/
int get_weight_of_edge (const WString_graph *const graph, const char source[],
			const char dest[]) {
  /* helping variables */
  int checker1 = 0;
  int checker2 = 0;
  Vertex* current_vertex = graph->root;
  Edge* current_edge = NULL;

  /* return 0 if the graph is NULL */
  if (graph == NULL) {
    return 0;
  }
  
  if (source == NULL || dest == NULL || graph->root == NULL) {

    return -1;
  }
 
  /* check if the graph does have the source or the dest */
  if (is_existing_vertex(graph, source) == 1) {

    checker1 = 1;
  }
  if (is_existing_vertex(graph, dest) == 1) {

    checker2 = 1;
  }
  
  if (checker1 == 1 && checker2 == 1) {

    current_vertex = graph->root;

    while (current_vertex != NULL) {

      if (strcmp(current_vertex->name,source) == 0) {

	if (current_vertex->list != NULL) {

	  current_edge = current_vertex->list;

	  while (current_edge != NULL) {

	    if (strcmp(current_edge->vertex->name,dest) == 0) {

	      return current_edge->cost;
	    }
	    current_edge = current_edge->new_edge;
	  }
	}
      }
      current_vertex = current_vertex->new;
    }
  }
  return -1;
  
}
/*
  The purpose of this function is to count how many neighbors
  does the vertex have 
*/
int num_neighbors (const WString_graph *const graph, const char vertex[]) {
  
  /* helping variables */
  int num = 0;
  int temp = 0;
  Vertex* current_vertex = graph->root;
  Edge* current_edge = NULL;
  
  /* returning 0 if the graph is NULL*/
  if (graph == NULL) {

    return 0;
  }
  /* retuning -1 if the vertex is NULL or the word is not in the graph */
  if (vertex == NULL || is_existing_vertex(graph, vertex) == 0) {
    
    return -1;
  }

  while (current_vertex!= NULL && temp == 0) {

    if (strcmp(current_vertex->name,vertex) == 0) {

      temp = 1;

      if (current_vertex->list != NULL) {

	current_edge = current_vertex->list;

	while (current_edge != NULL) {

	  if (current_edge->vertex != NULL) {
	    
	    num++;
	  }
	  current_edge = current_edge->new_edge;
	}
      }
    }

    current_vertex= current_vertex->new;
  }
  
  if (temp == 0) {

    return -1;
  } else {

    return num;
  }

}


