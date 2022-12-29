#include <stdio.h>
#include "student.h"
#include <string.h>
#include <stdlib.h>
Student new_student(const char name[], unsigned int id,
		  float shoe_size){

  Student d;
  if( name == NULL){
    
    strcpy(d.name, "");
    d.id= id;
    d.shoe_size= shoe_size;
    return d;
  }
  
  strcpy(d.name, name);
  d.id= id;
  d.shoe_size= shoe_size;
  return d;
  
}
void init_student(Student *const student, const char name[], unsigned
		  int id, float shoe_size){
  if( student == NULL){
    return;
  }
  if( name == NULL){
    strcpy( student -> name, "");
  } else {
    
  strcpy( student->name, name);
  }
  student->id = id;
  student->shoe_size = shoe_size;
  
}
unsigned int has_id(Student student, unsigned int id){

  if(student.id == id){
    return 1;
  }
  return 0;
}
unsigned int has_name(Student student, const char name[]){

  if( name != NULL ){
    if(strcmp (student.name, name)== 0){
      return 1;
    }
  }

  return 0;
}
unsigned int get_id(Student student){

  return student.id;
}
float get_shoe_size(Student student){

  return student.shoe_size;
}
Student change_shoe_size(Student student, float new_shoe_size){
  student.shoe_size = new_shoe_size;
  return student;
}
void change_name(Student *const student, const char new_name[]){
  if(student == NULL){
    return;
  } else if( new_name == NULL){
    strcpy (student-> name,"");
  } else{
    strcpy (student-> name, new_name);
  }
}


