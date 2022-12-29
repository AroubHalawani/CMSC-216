#if !defined(FORKFILE)
#define FORKFILE

typedef struct Forkfile{
  struct Target *root;
  struct Target *end;
  char *name;
  int count;
  
}Forkfile;

typedef struct Target {
  struct Target *new;
  char **target_array;
  char **action_array;
  int index;

  
} Target;
#endif
