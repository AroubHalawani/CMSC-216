#include "functions.h"

/* Write your implementations of the functions in this source file.
 * Skeleton versions of the functions already appear below.
 */

int has366(int y) {
  if(y <= 1752){
    return -1;
  }
  if(y % 4==0 && y%100 !=0){
    return 1;
  }
  if(y %400 ==0){

    return 1;
  }
  return 0;
}

long sopd(int num, int n) {
  int total =0;
  int f=1;
  int result =1;
  int count =0;
  
  if(num <0 || n<0){
    return -1;
  }
  while(f<=num){
    if(num % f==0){
      while(count< n){
	result*=f;
	count++;

      }
      count=0;
      total+=result;
      result=1;
    }
    f++;
  }
  return total;
}
