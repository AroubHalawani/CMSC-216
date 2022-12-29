
typedef struct node{
  int value;
  struct node *next;
} Node;

typedef struct queue {
  struct node *head;
} Two_sided_queue;




void init(Two_sided_queue *const twosq);
int add_front(Two_sided_queue *const twosq, int new_value);
int add_back(Two_sided_queue *const twosq, int new_value);
int num_elements(Two_sided_queue *const twosq);
void print(Two_sided_queue *const twosq);
int remove_front(Two_sided_queue *const twosq, int *value);
int remove_back(Two_sided_queue *const twosq, int *value);
