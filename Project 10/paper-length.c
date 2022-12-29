#include <stdio.h>
#include <stdlib.h>
#include "safe-fork.h"
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <sysexits.h>

int main(void){

  pid_t pid;
  int pipefd[2];

  pipe(pipefd);
  pid = safe_fork();
    
  if( pid > 0) {

    int index;
    
    dup2(pipefd[0], STDIN_FILENO);

    close(pipefd[0]);
    close(pipefd[1]);

    scanf("%d",&index);
    if( index < 200){

      printf("Too short!\n");
      exit(1);

    } else {

      printf("Long enough!\n");
      exit(0);

    }

  } else{

    if (pid == 0){

      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);
      execl("/usr/bin/wc","wc","-w",NULL);

      err(EX_OSERR, "error");
    } else {

      printf("error");
    }
  }
  return 0;

}
