/*
  Student Name: Aroub Halawani
  Class : CMSC216

  The purpose of this project is to implement a two-sided-queue
  that just stors integers by using dynamic data structure

*/

#include <stdio.h>
#include <stdlib.h>
#include "two-sided-queue.h"

/* 
   The purpose of this function is to initialize the two-sided-queue
   to be an empty queue containg no elements
*/
void init (Two_sided_queue *const twosq) {

  if (twosq == NULL) {
    return;
  }
  
  twosq-> head = NULL;
  
}

/*
  The purpose of this function is to add the new_value as a new
  element at the front of its two-sided-queue 
*/
int add_front (Two_sided_queue *const twosq, int new_value) {
 
  Node *new_node = NULL; /* helper variable */

  /* returning 0 if the pointer is NULL */
  if (twosq == NULL) {

    return 0;
  }
  /* allocate the memory for the new element */
  new_node = malloc(sizeof(*new_node));

  /* returning 0 if the memory is not allocated */
  if (new_node == NULL) {
    
    return 0;
  }
  new_node-> value = new_value;

  new_node-> next = twosq-> head;

  twosq-> head = new_node;

  return 1;
}

/* 
   The purpose of this function is to add the new_value as the new
   last element at the end of its two-sided-queue
*/
int add_back (Two_sided_queue *const twosq, int new_value) {

  /* helper variables */
  Node *current;
  Node *prev= NULL;
  Node *new_node;

  /* returning 0 if the pointer is NULL */
  if (twosq == NULL) {

    return 0;
  }
  
  current = twosq-> head; /* the first element on the list */ 

  while (current!= NULL) {

    prev = current;
    current = current-> next; /* moving to the next element */  
  }
  
  /* allocate the memory for a new element */
  new_node = malloc(sizeof(*new_node));

  /* returning 0 if the memory is not allocated */
  if (new_node == NULL) {
    
    return 0;
  }
  
  new_node-> value = new_value;
  
  new_node-> next = NULL;

  if (prev != NULL) {
    
    prev-> next = new_node;

  } else {
    
    twosq-> head = new_node;
  }
  
  return 1;
}

/*
  The purpose of this function is to count how many elements
  being stored in its queue
*/
int num_elements (Two_sided_queue *const twosq) {

  Node *current; /* a helper variable */
  int index = 0;/* a variable that count how many element on the list */

  /* returning 0 if the pointer is NULL */
  if (twosq == NULL) {
    
    return 0;
  }
  current = twosq-> head; /* The first element on the list */
  
  /* if the queue has > 0 elemnts */
  while (current != NULL) {
    
    index++;
    current = current-> next;/* moving to the next element */
  }

  return index;
}

/*
  The purpose of this function is to print 
  all elements of its two-sided-queue
*/
void print (Two_sided_queue *const twosq) {
    
  Node *current;
  int index = 0; /* a helper variable to print a new line at the end */

  /* Doing nothing if the pointer is NULL */
  if (twosq == NULL) {

    return;
  }
  
  current = twosq-> head; /* The first element on the list */

  /* if the queue has > 0 elemnts */
  while (current != NULL) {
    
    index++;

    printf( "%d", current-> value);


    /* Keeping a space between the elements */
    if (current-> next != NULL) {

      printf(" ");
    }
    current = current-> next; /* moving to the next element */
  }

  /* Printing a new line after printing the list */
  if (index > 0) {
    
    printf("\n");
  }
}
/*
  The purpose of this function is to remove the element at the front 
  of its tow-sided-queue and store it in a variable
*/

int remove_front (Two_sided_queue *const twosq, int *value) {

  Node *current; /* a helper variable */

  /* returning 0 if the pointer or the head is NULL */
  if (twosq == NULL || twosq-> head == NULL) {

    return 0;
  }
  
  current = twosq-> head;/* The first element on the list */
    
  if (current != NULL) {
    
    twosq-> head = current-> next;

    /* store the element on value */
    *value = current-> value;
  }

  /* free the element from the memory since it is no longer needed */
  free(current);
  
  return 1; 
}
/*
  The purpose of this function is to remove the element at the end 
  of its two-sided-queue and store it in a varibale
*/
int remove_back (Two_sided_queue *const twosq, int *value) {

  /* helper variables */
  Node *current;
  Node *prev = NULL;

  /* returning 0 if the pointer or the head is 0 */
  if (twosq == NULL || twosq-> head == NULL) {

    return 0;
  }
  
  current = twosq-> head;/* the first element on the list*/
    
  while (current-> next != NULL) {

    prev = current;

    current = current-> next; /* moving to the next element */
  }
    
  if (prev == NULL) {
  
    return remove_front(twosq, value);

  } else {
      
    prev-> next = current-> next;

    *value= current-> value;

    /* free the element from the memory since it is no longer needed */
    free(current);
  }
  
  return 1;
}
