#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>

#define MAX_LENGTH 255


struct stack_float
{
    float items[MAX_LENGTH];
    int top;
};
 typedef struct stack_float sf;

struct stack_str{
    char items[MAX_LENGTH];
    int top;
};
typedef struct stack_str ss;

void create_stack_f (sf *s);
void create_stack_s (ss *s);

bool is_full_f(sf *s);
bool is_full_s(ss *s);

bool is_empty_f(sf *s);
bool is_empty_s(ss *s);

void push_f(sf *s,float num);
void push_s(ss *s,char operand);

float pop_f (sf *s);
char pop_s (ss *s);


void print_sf(sf *s);
void print_ss(ss *s);

float view_top_f(sf *s);
char view_top_s (ss *s);


typedef struct node {
   float val;
   struct node *next;
} node_t;

void enqueue(node_t **head, float val);
float dequeue(node_t **head);


#endif