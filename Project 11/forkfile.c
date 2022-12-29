/*
  The purpose of this project is to write a utility functions to perform
  various operations on forkfile, such as reading a forkfile, printing
  the components of a forkfile that has been read, looking up targets
  in forkfile, perform actions in forkfile, etc
*/
#include <stdlib.h>
#include <stdio.h>
#include "forkfile.h"
#include "split.h"
#include <string.h>
#include "safe-fork.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sysexits.h>
/*
  The purpose of this function is to read the filename in the components
  of a forkfile from it, store it in forkfile, and return it
*/
Forkfile read_forkfile(const char filename[]) {

  /* helping variables */
  FILE *file;
  Forkfile forkfile;
  char array[1000];
  struct Target *target;
  

  /* doing nothing if the filename is NULL*/
  if (filename == NULL){
    return forkfile;
  }
  
  file = fopen(filename, "r");

  /* doing nothing if there is no file with this name */
  if (file == NULL){

    return forkfile;
  }

  /* read the file line by line and split it in an array */
  while (fgets(array, 1000, file)) {

    /* target line */
    if (array[0] != '#' && array[0] != '\t'&& array[0] != '\n') {

      target = malloc(sizeof(Target));
      target->target_array = split(array);

      /* action line */
      if (fgets(array, 1000, file) && array[0] =='\t') {
      
	target->action_array = split(array);

	target->index = forkfile.count++;

	/* if it is the last line */
	if (forkfile.end == NULL) {
	  
	  forkfile.root = target;
	  forkfile.end = target;
	  forkfile.end->new = NULL;

	} else { /* if there is another line */

	  forkfile.end-> new = target;
	  forkfile.end = target;
	  target->new = NULL;
	}
       
      }
    }
  }

  /* close the file and return the forkfile*/
  fclose(file);
  return forkfile;
}
/*
  The purpose of this function is to search for a rule in its forkfile
  that has the target_name and return its number
*/

int lookup_target (Forkfile forkfile, const char target_name[]) {

  /* helping varible */
  struct Target *current_target = forkfile.root;

  /* returning -1 if the target_name is NULL */
  if (target_name == NULL) {

    return -1;
  }

  /* going through the forkfile */
  while (current_target != NULL) {

    /* if the rule is found */
    if (strcmp(target_name, *current_target->target_array) == 0) {

      return current_target->index;
    }
    /* moving to the next target */
    current_target = current_target->new;
  }
  /* returning -1 since there is no rule with the target name */
  return -1;

  
}
/*
  The purpose of this function is to print the action line of
  the rule_num in its forkfile
*/
void print_action (Forkfile forkfile, int rule_num) {

  /* helping variables */
  struct Target *current_target = forkfile.root;
  char **temp;

  /* Doing nothing if the rule number is less than 0 */
  if (rule_num < 0 || forkfile.count <= rule_num) {
    return;
  }

  /* printing the action line of the rule_num */
  while (current_target != NULL) {

    /* if the rule_num is found */
    if (current_target->index == rule_num) {

      temp = current_target->action_array;

      /* printing the first word */
      printf("%s", *temp);
      temp++;

      /* printing the rest of the words with a space between them */
      while (*temp != NULL) {

	printf(" %s", *temp);
	temp++;
      }
      /* printing a newline after the last word */
      printf("\n");
    }
    
    /* moving to the next action line */
    current_target = current_target->new;
  }
}

/*
  The purpose of this function is to print the components of its forkfile
*/
void print_forkfile(Forkfile forkfile){

  /* helping variables */
  struct Target *current_target = forkfile.root;
  char **temp;
 
  /* going through the forkfile */
  while (current_target != NULL) {

    temp = current_target->target_array; 

    /* printing the first name of the target line following by colon*/
    printf("%s:", *temp);

    temp++;

    /* printing the list of target dependency names */
    while (*temp != NULL) {

      printf(" %s", *temp);

      temp++;
    }
    printf("\n\t");

    temp = current_target->action_array;
    /* printing the first name of the action line */
    printf("%s", *temp);

    temp++;

    /* printing the list of action dependeny names */
    while (*temp != NULL) {

      printf(" %s", *temp);

      temp++;
    }
    printf("\n");
    
    if (current_target->new != NULL) {

      printf("\n");
    }
    
    /* moving to the next target */
    current_target = current_target->new;
  }
  
}
/*
  The purpose of this function is to return the number of
  dependencies that the rule_num has in the forkfile
*/
int num_dependencies (Forkfile forkfile, int rule_num) {

  /* helper variables */
  struct Target *current_target = forkfile.root;
  char **list;
  int retval = -1;

  /* returing -1 if the rule number is not valid */
  if (rule_num >= forkfile.count) {
    return retval;
  }

  /* going through the forkfile*/
  while (current_target != NULL) {

    /* if the rule_num is found */
    if (current_target->index == rule_num) {
      
      list = current_target->target_array;

      while (*list != NULL) {
	
	retval++;/* increment the dependencies number*/
	list++;
      }
    }
    /* moving to the next target */
    current_target = current_target->new;
  }
  return retval;
}
/*
  The purpose of this function is to return a pointer to the name
  of the dependency in its forkfile
*/
char *get_dependency (Forkfile forkfile, int rule_num, int dependency_num) {

  /* helping variables */
  struct Target *current_target = forkfile.root;
  char **list;
  int index = 0;

  /* if the rule_num or the dependency_num is less than 0 */
  if (rule_num < 0 || dependency_num < 0 || rule_num >= forkfile.count) {
    
    return NULL;
  }
  
  while(current_target != NULL) {

    if (current_target->index == rule_num) {
	  
      list = current_target->target_array;

      list++;

      while (*list != NULL) {

	if (index == dependency_num) {

	  return *list;
	}
	
	list++;
	index++;
      }
    }
    current_target= current_target->new;
  }
  
  return NULL;
	  
}
/*
  The purpose of this function is to check if the filename
  exist in the filessystem or not
*/
int exists (const char filename[]) {

  struct stat file;
  errno = 0;

  /* returning NULL if the filename is NULL */
  if (filename == NULL) {
    return 0;
  }
  
  if (stat(filename, &file) == -1 && errno == ENOENT) {

    /* the file does not exist */
    return 0;
  }
  
  /* the file exist */
  return 1;
}
/*
  The purpose of this function is to check which file is older
*/
int is_older (const char filename1[], const char filename2[]) {

  struct stat temp1;
  struct stat temp2;

  /* returning 0 if one of the files is NULL */
  if (filename1 == NULL || filename2 == NULL) {
    return 0;
  }

  /* returning 0 if one of the files is no exist in the filesystem */
  if (exists(filename1) == 0 || exists(filename2) == 0) {
    return 0;
  }
  
  if (stat(filename1, &temp1) == 0 && stat(filename2, &temp2) == 0) {

    /* if filename1 is older then filename2 */
    if (temp1.st_mtime < temp2.st_mtime) {

      return 1;
    }
  }
  return 0;
}

/*
  The purpose of this function is to perform the action of the
  rule_num in its forkfile
*/
int do_action (Forkfile forkfile, int rule_num) {

  /* helping variables */
  struct Target *current_target = forkfile.root;
  int index = 0;
  pid_t pid = safe_fork();

  if (rule_num >= forkfile.count) {
    return -1;
  }

  if (pid == 0) {

    while (current_target != NULL) {

      if (current_target->index == rule_num) {
	
	execvp(current_target->action_array[0], current_target->action_array);

      }      
      current_target = current_target->new;
    }

  }
  if (pid > 0) {

    wait(&index);

    if (WIFEXITED(index) && WEXITSTATUS(index) == 0) {

      return index;
    }   
  }
  return -1;
}
