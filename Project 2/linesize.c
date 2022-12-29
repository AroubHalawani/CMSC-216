/*
This program is to read a file and store every line in an array to count:
1- How many lines on that file
2- How many lines have more than 80 chars

The program will print some spaces depending on the 2 previos factors 
and the line itself, and it will do that for all the lines. 

After that it will print how many lines are in the text and how many line
has more than 80 char

*/
#include <stdio.h>
int main(){

  /* Variables declaration */
  char single_line[1000];/* An array to store a line for do all the process */
  int length = 0;/* to count the length of every line */
  int tap = 0; /* to count how many tap in every line*/
  int space = 0 ;/* a helper variable to count number of tabs */
  int lines_number = 0;/* To count how many line in the input */
  int long_line = 0;/* To count how many line has more than 80 chars */
  int count = 0; /* used in a for loop to print an array of chars */
  int index = 0;/* a helper variable to store the char in the array */

  
  /* A loop for storing the line that was read into an array char by char*/
  while (scanf("%c", &single_line[index]) != EOF) {

    /* Checking if its not the end of the line to do all the process */
    if (single_line[index] != '\n') {

      /* Checking if the char that was stored is a space or not */
      if (single_line[index] == '\t') {
	
	/* calculate the number of spaces until the next tab */
	tap = length % 8;
	space = 8 - tap;
	length+= space; /* add the number to the length */

      } else {

	/* if the char that was stored is not a space,then the length should increase*/
	length++;
      }
      
      /* Increase the index to go to the next char in the array */
      index++;
      
    } else { /* if its the end of the line */

      lines_number++; /* Increase the number of lines */
      
      /* checking if the length of the line is greater than 80*/ 
      if (length > 80) {

	printf("X ");
	long_line++; /* Increase the number of lines that have more than 80 chars */

      } else { /* if the length of the line is 80 or less */

	printf("  ");
      }
      
      printf("%4d> ", length);

      /* A loop to print the reminder of the line */
      for( count = 0; count< index ; count++ ) {
	
	printf("%c", single_line[count]);

      }
      /* Going to the next line */
      printf("\n");

      /* To do the same process for the next line */
      length = 0;
      index = 0;
    }
  }
  
  /* Printing the last line that includes the number
     of lines and the number of long lines*/
  printf("%d %d\n", lines_number, long_line);

  return 0;
}
