#include <stdio.h>
#include "machine.h"

/* 
   The purpose of this function is to print the instruction that
   is passed with its regisers and its memory address
*/
void print_instruction (Hardware_word instruction) {

  /* bit shifting operation */
  
  Hardware_word temp_instruction = ( instruction >> 28 ) ;
  Hardware_word reg1 = ( instruction >> 23 ) & 0x1f;
  Hardware_word reg2 = ( instruction >> 18 )& 0x1f;
  Hardware_word reg3 = ( instruction >> 13 ) & 0x1f;
  Hardware_word memory_address = instruction & 0x0000ffff;
  
  /* Printing the relevent information of each instruction */

  if (temp_instruction == 0) {
    printf("halt");
  } else if (temp_instruction == 1) {
    printf("%s\tR%d\tR%d\tR%d", "add", reg1, reg2, reg3);
  } else if (temp_instruction == 2) {
    printf("%s\tR%d\tR%d\tR%d","sub", reg1, reg2, reg3);
  } else if (temp_instruction == 3) {
    printf("%s\tR%d\tR%d\tR%d", "mul", reg1, reg2, reg3);
  } else if (temp_instruction == 4) {
    printf("%s\tR%d\tR%d\tR%d", "div", reg1, reg2, reg3);
  } else if (temp_instruction == 5) {
    printf("%s\tR%d\tR%d\tR%d", "rem", reg1, reg2, reg3);
  } else if (temp_instruction == 6) {
    printf("%s\tR%d\tR%d", "inv", reg1, reg2);
  } else if (temp_instruction == 7) {
    printf("%s\tR%d\tR%d\tR%d", "and", reg1, reg2, reg3);
  } else if (temp_instruction == 8) {
    printf("%s\tR%d\tR%d\tR%d", "or", reg1, reg2, reg3);
  } else if (temp_instruction == 9) {
    printf("%s\tR%d\tR%d", "not", reg1, reg2);
  } else if (temp_instruction == 10) {
    printf("%s\tR%d\tR%d\tR%04d\t%d", "cmp", reg1, reg2, reg3, memory_address);
  } else if (temp_instruction == 11) {
    printf("%s\tR%d\tR%d", "mv", reg1, reg2);
  } else if (temp_instruction == 12) {
    printf("%s\tR%d\t%d", "li", reg1, memory_address );
  } else if (temp_instruction == 13) {
    printf("%s\tR%d\t%04d", "load", reg1, memory_address);
  } else if (temp_instruction == 14) {
    printf("%s\tR%d\t%04d", "store", reg1, memory_address);
  } 
}
/*
  The purpose of this function is to encode the value 
  of instruction as a 32- bit Mathlon instruction and 
  store the result into the Hardware_word
*/
unsigned int encode_instruction( unsigned short opcode, unsigned short reg1,
				 unsigned short reg2, unsigned short reg3,
				 unsigned int add_or_constant,
				 Hardware_word *const hw_word){

  /* Returning 0 if hw_word is NULL */

  if (hw_word == NULL) {
    return 0;
  }
    
  /* if any of these statments is true the instruction in invalid */
   
  if (opcode < 0 || opcode > 14) {
    return 0;
  }
  
  if (opcode >= 1 && (reg1 < 0 || reg1 > 19)) {
    return 0;
  }

  if (opcode >= 1 && opcode <= 11 && (reg2 < 0 || reg2 > 19)) {
    return 0;
  }

  if ((opcode >= 1 && opcode <= 5) || opcode == 7 ||
      opcode == 8 || opcode == 10) {
    
    if (reg3 < 0 || reg3 > 19) {
      return 0;
    }

  }
  
  if (opcode == 10 || (opcode >= 12 && opcode <= 14)) {

    if (opcode != 10 && add_or_constant % 4 != 0) {
      return 0;
    }

    if (opcode == 12 && add_or_constant > 8191) {
      return 0;
    }

    if (add_or_constant < 0 || add_or_constant > 2047) {
      return 0;
    }
  }

  if ((opcode != 0 && opcode != 10 && opcode != 14) &&
      (reg1 == 0 || reg1 == 1)) {
      
    return 0;
  }

  if (opcode == 10 && (reg3 < 0 || reg3 > 5)){
    return 0;
  }
  /*
     Using the bit operators to place the parameters' values
     in the correct bit of the variable that hw_word points to
  */

  *hw_word = 0;
  *hw_word = *hw_word | opcode << 28;
  *hw_word = *hw_word | reg1 << 23;
  *hw_word = *hw_word | reg2 << 18;
  *hw_word = *hw_word | reg3 << 13;
  *hw_word = *hw_word | add_or_constant;
  
  	  
  return 1; /* The instruction is valid */ 

}
/* 
   This is a helper function that determine if the 
   instruction is valid or not

*/
int valid (Hardware_word instruction) {

  /* bit shifting operation */
  
  Hardware_word opcode = ( instruction >> 28 ) ;
  Hardware_word reg1 = ( instruction >> 23 ) & 0x1f;
  Hardware_word reg2 = ( instruction >> 18 )& 0x1f;
  Hardware_word reg3 = ( instruction >> 13 ) & 0x1f;
  Hardware_word memory_address = instruction & 0x0000ffff;

  /* The instruction is invalid if any of these statments is true */
  
  if (opcode < 0 || opcode > 14) {
    return 0;
  }
  
  if (opcode >= 1 && (reg1 < 0 || reg1 > 19)) {
    return 0;
  }

  if (opcode >= 1 && opcode <= 11 && (reg2 < 0 || reg2 > 19)) {
    return 0;
  }

  if ((opcode >= 1 && opcode <= 5) || opcode == 7 ||
      opcode == 8 || opcode == 10) {

    if (reg3 < 0 || reg3 > 19) {
      return 0;
    }
  }
  
  if (opcode == 10 || (opcode >= 12 && opcode <= 14)) {

    if (opcode != 10 && memory_address % 4 != 0) {
      return 0;
    }

    if (opcode == 12 && memory_address > 8191) {
      return 0;
    }

    if (memory_address < 0 || memory_address > 2047) {
      return 0;
    }
  }
    
  if ((opcode != 0 && opcode != 10 && opcode != 14) &&
      (reg1 == 0 || reg1 == 1)) {
    
    return 0;
  }

  if (opcode == 10 && (reg3 < 0 || reg3 > 5)){
    return 0;
  }

  /* The instruction is valid */
    
  return 1;
}
/*
  The purpose of this function is to convert machine 
  language a Mathlon program to assembly language
*/
unsigned int disassemble (const Hardware_word memory[],
			  unsigned int memory_size, unsigned int num_instrs) {
  
  int index = 0; /* counter for the for-each loop */
  int index1 = 0; /* counter for the second for-each loop */
  
  if (memory != NULL) {

    if ((memory_size > 0) && (memory_size <= 512) && (num_instrs > 0)) {

      for (index = 0; index < num_instrs; index++) {

	if (valid(memory[index]) == 1) {

	  /* Printing the memory address in hexadecimal */
	  printf("%03x: ", index * 4);

	  /* Printing the element exactly as print instruction function */
	  print_instruction(memory[index]);
	  printf("\n");
	  
	} else {
	  /* if the instruction is invalid */
	  return 0;
	}	  
      
      }

      for (index1 = num_instrs; index1 < memory_size; index1++) {
	
	/* Printing any subsequent element of the array the represnt data */
	printf("%03x: %08x\n",index1*4, memory[index1]);
	
      }
    }
  }
  
  return 0;  
}

/* 
   This function compare instruction1 and instruction2. 
   if they represent the same Mathlone return 1. 
   Otherwise, return 0
*/
unsigned int compare_instructions(Hardware_word instr1, Hardware_word instr2){  

  if( instr1 && instr2 ){
    if (((instr1 & instr2)== instr1) && ((instr1 & instr2) == instr2)){
      return 1;
    }
  }
  return 0;
}
