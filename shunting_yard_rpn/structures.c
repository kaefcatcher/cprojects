#include "structures.h"

void create_stack_f (sf *s){
    s->top=-1;
}
void create_stack_s (ss *s){
    s->top=-1;
}



bool is_full_f(sf *s){
    if (s->top==MAX_LENGTH-1) return true;
    return false;
}

bool is_full_s(ss *s){
    if (s->top==MAX_LENGTH-1) return true;
    return false;
}

bool is_empty_f(sf *s){
    if (s->top==-1) return true;
    return false;
}

bool is_empty_s(ss *s){
    if (s->top==-1)return true;
    return false;
}

void push_f(sf *s,float num){
    if (is_full_f(s)) return;
    s->items[++s->top]=num;
}
void push_s(ss *s,char operand){
    if (is_full_s(s))return;
    s->items[++s->top]=operand;
}

float pop_f (sf *s){
    if (is_empty_f(s)) return -INT_MAX;
    return s->items[s->top--];
}
char pop_s (ss *s){
    if (is_empty_s(s)) return -CHAR_MAX;
    return s->items[s->top--];
}


void print_sf(sf *s)
{
    printf("Reversed Stack: ");
  while (!is_empty_f(s)) {
    int i=s->top;
    printf("%f ", s->items[i]);
    pop_f(s);
  }
  printf("\n");
}
void print_ss(ss *s){
    printf("Reversed Stack: ");
  while (!is_empty_s(s)) {
    int i=s->top;
    printf("%c ", s->items[i]);
    pop_s(s);
  }
  printf("\n");
}

float view_top_f(sf *s){
    if (is_empty_f(s))return -INT_MAX;
    return s->items[s->top];
}
char view_top_s (ss *s){
    if (is_empty_s(s)) return -CHAR_MAX;
    return s->items[s->top];
}


void enqueue(node_t **head, float val) {
   node_t *new_node = malloc(sizeof(node_t));
   if (!new_node) return;

   new_node->val = val;
   new_node->next = *head;

   *head = new_node;
}

float dequeue(node_t **head) {
   node_t *current, *prev = NULL;
   float retval = -1;

   if (*head == NULL) return -1;

   current = *head;
   while (current->next != NULL) {
      prev = current;
      current = current->next;
   }

   retval = current->val;
   free(current);

   if (prev)
      prev->next = NULL;
   else
      *head = NULL;

   return retval;
}