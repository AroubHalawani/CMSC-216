#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
Student *new_student( const char name[], unsigned int id, float shoe_size ){

  Student *student = malloc(sizeof(*student));
  if( name == NULL){
    student-> name = malloc(1);
    strcpy(student->name, "");
  } else {
    student-> name= malloc(strlen(name)+1);
    strcpy( student-> name, name);
  }
  student->id= id;
  student->shoe_size= shoe_size;

  return student;
}

unsigned int has_id( const Student *const student, unsigned int id){
  
  if(student != NULL && student->id == id){
    return 1;
  }
  return 0;
}
unsigned int has_name( const Student *const student, const char name[]){

  if( name == NULL){
    return 0;
  }
  if( student != NULL){
    if( strcmp ((student -> name), name) == 0){
      return 1;
    }
  }
  return 0;
}
unsigned int get_id (const Student *const student){

  if( student != NULL){
    return student ->id;
  }
  return 0;
}
float get_shoe_size(const Student *const student){
  if( student == NULL){
    return 0.0;
  }
  return student->shoe_size;
    
}
void change_shoe_size (Student *const student, float new_shoe_size){
  if( student != NULL){
    student -> shoe_size = new_shoe_size;
  }
}
void change_name (Student *const student, const char new_name[]){

  if( student != NULL){
    free(student ->name);
    if(new_name != NULL){
      student -> name = malloc((strlen(new_name)+1));
      strcpy( student -> name, new_name);
    } else {
      student-> name = malloc(sizeof(char));
      strcpy(student->name,"");
    }
  }
}
void copy_student (Student *const student1 , const Student *const student2){
  if( student1== NULL || student2 == NULL){
    return;
  }
 
  free(student1->name);
  student1-> name = malloc (sizeof(strlen(student2->name)+1));
  strcpy( student1-> name, student2->name);
  student1->id = student2->id;
  student1->shoe_size = student2->shoe_size;
  
    
}
