#include <stdlib.h>
#include <stdio.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* Insert*/
#define PUSH 0
#define INSERT_TAIL 1 
#define ASCENDING 2
#define DESCENDING 3

/* Key Settings */
#define NO_KEY 0

/* Extract */
#define POP 4
#define EXTRACT_TAIL 5
#define SEARCH_KEY 6

typedef struct t_node
{
    /* [DATA] */
    int data;
    /* [Pointers] */
    struct t_node *next;
    struct t_node *prev;
}t_node;

typedef struct t_ll
{
    /* [SIZE] */
    int sz_ll;
    /* [Pointers] */
    struct t_node *head;
    struct t_node *tail;
}t_ll;

/* Node Management */
t_node* node_create();
void node_destroy(t_node* node);
void node_sets_data(t_node* node, int data);

/* Linked List Functions */
int ll_create(t_ll* ll);
void ll_destroy(t_ll* ll);
int ll_is_empty(t_ll* ll);
int ll_insert(t_ll* ll, int data, int opcode);
int ll_add(t_ll* ll, t_node* node, int opcode);
int ll_extract(t_ll* ll, int key, int opcode);
void ll_print(t_ll* ll);

#endif