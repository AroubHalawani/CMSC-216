/*
  This project is an extention of project 8, and the purpose of it
  is to correctly free memory for such data structure
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wstring-graph.h"
/*
  The purpose of this function is to free all dynamically allocated
  memory of the array name
*/
void free_vertex_list (char**const name) {

  /* helping variable*/
  int index = 0;
  
  /* Doing nothing if the graph is NULL */
  if (name == NULL) {
    return;
  }

  /* Going through each element and free it */
  while (name[index] != NULL) { 

    free(name[index]);
    index++;
  }

  /* free the name itself */
  free(name);
}

/*
  The purpose of this function is to destroy the graph 
  with all its data
*/
void destroy_graph (WString_graph *const graph) {

  /* helping variables */
  Vertex *current_vertex = NULL;
  Vertex *saved_vertex = NULL;
  Edge *current_edge = NULL;
  Edge *saved_edge = NULL;

  /* Doing nothing if the graph is NULL */
  if (graph == NULL || graph->root == NULL) {
    return;
  }

  current_vertex = graph->root;

  /* going through the list */
  while (current_vertex != NULL) {

    /* check if the current vertex has an edge */
    if (current_vertex->list != NULL) {
      
      current_edge = current_vertex->list;

      /* free the edges of the current vertex */
      while (current_edge != NULL) {

	saved_edge = current_edge;
	current_edge = current_edge->new_edge;
	free(saved_edge);
      }
      
      current_vertex->list = NULL;
    }
    /* free the vertexs of the graph */
    saved_vertex = current_vertex;
    current_vertex = current_vertex->new;
    free(saved_vertex->name);
    free(saved_vertex);
  }
}
/*
  The purpose of this function is to remove the edge that is going 
  from the source to the edge in the graph and delocate the memory
*/
int remove_edge (WString_graph *const graph, const char source[],
		 const char dest[]) {

  /* helper variables */
  Vertex *temp_vertex;
  Vertex *current_vertex;
  Edge *previos_edge;
  Edge *current_edge;

  /* returning 0 if the graph, source,or dest is NULL */
  if (graph == NULL || source == NULL || dest == NULL) {
    return 0;
  }
  /* returning 0 if the source is not existing in the graph*/
  if (is_existing_vertex(graph, source) == 0) {
    return 0;
  }
  
  /* returning 0 if the dest is not existing in the graph*/
  if (is_existing_vertex(graph, dest) == 0) {
    return 0;
  }
  
  current_vertex = graph->root;

  /* going through the graph to check the edge is existing in which vertex */
  while (current_vertex != NULL) {
    
    /* if the edge is found */
    if (strcmp(source, current_vertex->name) == 0) {

      /* saving the vertex of the edge */
      temp_vertex = current_vertex;
    }
    /* moving to the next vertex*/
    current_vertex = current_vertex->new;
  }
  
  current_edge = temp_vertex->list;
  previos_edge = NULL;

  /* going through the vertex to check which edge to remove */
  while (current_edge != NULL && strcmp( current_edge->vertex->name, dest ) != 0) {
    previos_edge = current_edge;
    current_edge = current_edge->new_edge;
  }

  if (previos_edge == NULL) {
    
    temp_vertex->list = current_edge->new_edge;
   
  } else {

    previos_edge->new_edge = current_edge->new_edge;
  }
  /* removing the edge */
  free(current_edge);
  
  return 1;
}

/*
  The purpose of this function is to remove the vertex from the graph
*/
int remove_vertex(WString_graph *const graph, const char vertex[]){

  /* helping variables */
  Vertex *temp_vertex = NULL;
  Vertex *current_vertex = graph->root;
  Vertex *previos_vertex = NULL;
  Edge *current_edge = NULL;
  Edge *temp_edge = NULL;

  /* return 0 if the graph or the vertex is NULL */
  if (graph == NULL || vertex == NULL) {
    return 0;
  }

  /* returning 0 if the vertex is not existing in the graph */
  if (is_existing_vertex(graph, vertex) == 0) {
    return 0;
  }
  current_vertex = graph->root;

  /* going through the graph */
  while (current_vertex != NULL) {

    /* if the vertex is found */
    if (strcmp(current_vertex->name, vertex) == 0) {

      current_edge = current_vertex->list;

      /* if the vertex has edges */
      while (current_edge != NULL) {

	if (strcmp( current_edge->vertex->name, vertex ) == 0) {

	  temp_edge = current_edge->new_edge;

	  /* remove the edges of the current vertex */
	  remove_edge(graph, current_vertex->name, vertex);

	  current_edge = temp_edge;
	  
	} else {

	  /* moving to the next edge */
	  current_edge = current_edge->new_edge;
	}
      }
    }
    /* moving to the next vertex */
    current_vertex = current_vertex->new;
  }
  
  current_vertex = graph->root;
  /* going through the graph */
  while (current_vertex != NULL) {

    /* checking in which vertex the name is*/
    if (strcmp( current_vertex->name, vertex ) == 0){

      temp_vertex = current_vertex;
    }
    /* moving to the next vertex */
    current_vertex = current_vertex->new;
  }
  
  current_edge = temp_vertex->list;
  /* removing any edge of the current vertex that is connected to other vertex */
  while (current_edge != NULL) {
    
    temp_edge = current_edge->new_edge;
    remove_edge( graph, vertex, current_edge->vertex->name );
    current_edge = temp_edge;
  }

  current_vertex = graph->root;
  previos_vertex = NULL;
  
  while ( strcmp( current_vertex->name, vertex ) != 0 ) {

    previos_vertex = current_vertex;

    current_vertex = current_vertex->new;
  }
  if (previos_vertex == NULL) {
    
    graph->root = current_vertex->new;
   
  } else {

    previos_vertex->new = current_vertex->new;
  }
  /* free the vertex and its name */
  free(current_vertex->name);
  free(current_vertex);
  
  graph->size--; /* decrement the size since one vertex has been removed */
  
  return 1;
}

/* 
   The purpose of this function is to creat a new dynamically allocated
   array of pointers to characters to copy the names of the neighbors
*/
char **get_neighbors (const WString_graph *const graph, const char vertex[]){

  /* helper variables */
  char **result;
  int edge_count = 0;
  int i = 0;
  int check_ver = 0;
  Vertex* temp;
  Edge* curr;

  /* returning NULL if the vertex or the graph root is NULL */
  if (graph == NULL || vertex == NULL || graph->root == NULL) {

    return NULL;
  }
  temp = graph->root;

  /* going through the graph to check if the vertex in the graph or not */
  while (temp != NULL && check_ver == 0) {

    /* if the vertex is found */
    if (strcmp(temp->name,vertex) == 0) {

      check_ver = 1;
       	
    } else {
      temp = temp->new;	
    }
  }

  /* returning NULL if the vertex was not found in the graph */
  if (check_ver == 0) {
    return NULL;
  }

  curr = temp->list;

  /* counting how many edges does the vertex has */
  while (curr != NULL) {
    
    edge_count++;
    curr = curr->new_edge;
  }
  
  result = malloc(sizeof(char*)*(edge_count + 1));
  curr = temp->list;

  /* storing the name in a newly created dynamically aallocated array */
  while (curr != NULL) {

    result[i] = malloc(sizeof(char)*(strlen(curr->vertex->name) + 1));
    strcpy(result[i], curr->vertex->name);
    i++;
    curr = curr->new_edge;

  }
  result[i] = NULL;/* the last element must be NULL*/
  return result;
}
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
  Vertex *temp_vertex;
  Vertex *current_vertex = graph->root;

  /* returning 0 if the graph or the vertex is NULL*/
  if (graph == NULL  || new_vertex == NULL) {
    return 0;
  }

  /* returning 0 if the vertex is existing in the graph */
  if (is_existing_vertex(graph, new_vertex) == 1) {
    return 0;
  }
  

  /* creating a new dynamically alllocate array to store the name */
  temp_vertex = malloc(sizeof(Vertex));
  
  if (temp_vertex != NULL) {

    temp_vertex->name = malloc(strlen(new_vertex)+1);
    strcpy(temp_vertex->name, new_vertex);
    temp_vertex->new = NULL;
    temp_vertex->list = NULL;
  }
  
  if (graph->root == NULL) {

    graph->root = temp_vertex;

  } else {

    while (current_vertex->new != NULL) {

      current_vertex = current_vertex->new;
    }
    /* adding the element to the list */
    current_vertex->new = temp_vertex;
  }
  /* increacing the size of the graph since a vertex has been added */
  graph->size++;

  return 1;
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
  if (graph == NULL || name == NULL || graph->size == 0) {
    return 0;
  }

  /* going through the list to check if the vertex is exist or not */
  while (current_vertex != NULL) {

    /* returning 1 if the vertex is existing in the list */
    if (strcmp (current_vertex-> name, name) == 0) {
      return 1;
    }
    current_vertex = current_vertex-> new; /* moving to the next vertex */
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
  if (graph == NULL || graph->root == NULL) {

    answer = malloc(sizeof(char*));
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
  Edge* prev_edge = NULL; 

  /* 
     returing 0 if the graph is NULL, the cost < 0 ,
     or the source or the dest is NULL 
  */
  if (graph == NULL || cost < 0 || source == NULL || dest == NULL) {
    return 0;
  }
  
  /* check if the graph contains the source */
  if (is_existing_vertex(graph,source) == 0) {

    new_vertex_add(graph,source);
  }
    
  /* check if the graph contain the dest */
  if (is_existing_vertex(graph,dest) == 0) {

    new_vertex_add(graph,dest);
  }

  /* checking in which vertex does the graph contain the dest */
  while (current_vertex != NULL && strcmp(current_vertex->name, dest) != 0) {
    
    current_vertex = current_vertex->new;
  }
  
  temp_edge->vertex = current_vertex;
  temp_edge->cost = cost;
  temp_edge->new_edge = NULL;

  current_vertex = graph->root;

  /* going through the graph */
  while (current_vertex != NULL) {

    /* checking if there is an edge going from source to dest */

    if (strcmp(current_vertex->name, source) == 0) {

      current_edge = current_vertex->list;
      
      while (current_edge != NULL) {

	/* if there is an edge going from source to dest */
	if (strcmp(current_edge->vertex->name, dest) == 0) {

	  /* change the edge cost to the parameter cost and return 1 */
	  current_edge-> cost = cost;

	  free(temp_edge);
	  return 1;
	}
	/* moving to the next edge */
	current_edge = current_edge->new_edge;
      }
      /* put the edges in alph order */
      current_edge = current_vertex->list;

      while (current_edge != NULL && strcmp( dest, current_edge->vertex->name) > 0) {

	prev_edge = current_edge;
	current_edge = current_edge->new_edge;
      }
      
      if (prev_edge == NULL) {
	
      temp_edge->new_edge = current_vertex->list;
      current_vertex->list = temp_edge;

      } else {
	
	prev_edge->new_edge = temp_edge;
	temp_edge->new_edge = current_edge;
      }
      return 1;
    }
    /* moving to the next vertex */
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
  Vertex* current_vertex = graph->root;
  Edge* current_edge = NULL;

  /* return 0 if the graph is NULL */
  if (graph == NULL) {
    return 0;
  }
  /* returning -1 if the sorce, dest, or graph->root is NULL */
  if (source == NULL || dest == NULL || graph->root == NULL) {

    return -1;
  }
 
  /* check if the graph does have the source */
  if (is_existing_vertex(graph, source) == 0) {

    return -1;
  }
  /* check if the graph does have the dest */
  if (is_existing_vertex(graph, dest) == 0) {

    return -1;
  }
  
  current_vertex = graph->root;

  /* going through the graph */
  while (current_vertex != NULL) {

    /* checking if there is an edge going from source to dest */
    if (strcmp(current_vertex->name,source) == 0) {

      if (current_vertex->list != NULL) {

	current_edge = current_vertex->list;

	while (current_edge != NULL) {

	  /* if there is an edge going from source to dest*/
	  if (strcmp(current_edge->vertex->name,dest) == 0) {

	    /* return the cost of the edge*/
	    return current_edge->cost;
	  }
	  /* moving to the next edge */
	  current_edge = current_edge->new_edge;
	}
      }
    }
    /* moving to the next vertex */
    current_vertex = current_vertex->new;
  }
  /* returning -1 since there is no edge from source to dest */
  return -1;  
}
/*
  The purpose of this function is to count how many neighbors
  does the vertex have 
*/
int num_neighbors (const WString_graph *const graph, const char vertex[]) {
  
  /* helping variables */
  int num = 0;
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

  /* going through the graph */
  while (current_vertex != NULL) {

    /* if the vertex is found */
    if (strcmp(current_vertex->name, vertex) == 0) {

      current_edge = current_vertex->list;

      /* if the vertex has an edge */
      while (current_edge != NULL) {

	/* counting how many edge does the vertex have */
	num++;

	/* moving to the next edge */
        current_edge = current_edge->new_edge;
      }
      return num;
    }
    
    /* moving to the next vertex */
    current_vertex = current_vertex->new;
  }
  return num;
}
