#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*double f(double x){
    return 3 * x;
}
int main(void){
    int k = 7;
    double y;
    y = f(k);

    printf("%.2f", y);
    return 0;
}*/

typedef struct node{
  int data;
  struct node *next;
} node_t;

node_t *build(void){
  node_t *head = NULL;
  return head;
}

node_t *push(node_t *head, int num){
  node_t *pushnode = malloc(sizeof(node_t));
  assert(pushnode != NULL);
  pushnode->data = num;
  pushnode->next = head;

  return pushnode;
}

int recursive_length(node_t *node){
  if(node == NULL){
    return 0;
  }
  return 1 + recursive_length(node->next);
}

int main(void){
  node_t *linkedasslisthead = build();

  for(int i = 3; i > 0; i--){
    linkedasslisthead = push(linkedasslisthead, i);
  }

  for( node_t *p = linkedasslisthead; p != NULL; p = p->next){
    printf("%d", p->data);
  }

  printf("\nLength: %d", recursive_length(linkedasslisthead));
}



