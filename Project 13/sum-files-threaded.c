#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <semaphore.h>
#include <pthread.h>
/* (c) Larry Herman, 2020.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

static void *sum (void *argc) {
  int n = 0;
  FILE *fp;
  char *filename = (char*)argc;
  long *one_file_sum = malloc(sizeof(*one_file_sum));  
  
  fp = fopen(filename, "r");
  if (fp != NULL) {

    *one_file_sum = 0;

    fscanf(fp, "%d", &n);

    while (!feof(fp)) {

     *one_file_sum += n;

      fscanf(fp, "%d", &n);
    }
  }
  return one_file_sum;
  
}

int main(int argc, char *argv[]){
  int i = 0;
  long all_files_total = 0;
  
  pthread_t *p_t = malloc((argc-1)*sizeof(pthread_t)); 

  void** pth = (void** )malloc((argc-1)* sizeof(void *));

  for (i = 1; i < argc ; i++){

    pth [i-1] = NULL;

    pthread_create(&p_t[i - 1], NULL, sum, argv[i]);
     
    pthread_join(p_t[i -1], &pth[i - 1]);

    all_files_total += *(int*) pth[i - 1];

    free(pth[i-1]);
  }

  printf("%ld\n", all_files_total);
  free(pth);
  free(p_t);
  return 0;
  
}
