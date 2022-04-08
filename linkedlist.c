#include "linkedlist.h"

/* Node Management */

/* Allocates and initializes node */
t_node* node_create()
{
    t_node* node = (t_node*)malloc(sizeof(struct t_node));
    node->next = NULL;
    node->prev = NULL;
    node->data = -1;
    return node;
}

/* Frees node - avoid leaks */
void node_destroy(t_node* node)
{
    free(node);
}

/* Sets data inside node */
void node_sets_data(t_node* node, int data)
{
    node->data = data;
}

/* Linked List Functions */

/* Creates an empty LL */
int ll_create(t_ll* ll)
{
    /* Allocate head and tail */
    ll->head = node_create();
    ll->tail = node_create();

    /* Sets head and tail pointer */
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->head->prev = NULL;
    ll->tail->next = NULL;

    /* Sets linkedlist initial size */
    ll->sz_ll = 0;

    return ll_is_empty(ll);
}

/* Frees all elements inside LL - avoid leaks */
void ll_destroy(t_ll* ll)
{
    if(!ll_is_empty(ll))
    {
        t_node* node_iterator;
        t_node* node_destroyer;

        node_iterator = ll->head->next;

        /* Traverses through LL and destroys all nodes */
        while(node_iterator != ll->tail)
        {
            node_destroyer = node_iterator;
            node_iterator = node_iterator->next;
            node_destroy(node_destroyer);
        }
    }
    node_destroy(ll->head);
    node_destroy(ll->tail);
}

/* Check if LL is empty */
int ll_is_empty(t_ll* ll)
{
    if((ll->head->next == ll->tail) && (ll->tail->prev == ll->head) && (ll->sz_ll == 0))
        return 1; /* LL is empty */
    else
        return 0; /* LL is not empty */
}

/* Inserts nodes based on opcode given */
int ll_insert(t_ll* ll, int data, int opcode)
{
    /* Prepares node */
    t_node* new_node = node_create();
    node_sets_data(new_node, data);

    if(ll_add(ll, new_node, opcode)) /* Insertion succesful */
    {
        ll->sz_ll = ll->sz_ll + 1;
        return 1;
    }
    else /* Insertion failed */
    {
        node_destroy(new_node);
        return 0;
    }
}

/* Auxiliary function to add node to correct place on LL based on opcode */
int ll_add(t_ll* ll, t_node* new_node, int opcode)
{
    t_node* node_iterator;

    if(opcode == PUSH)
    {
        /* Saves pointer */
        node_iterator = ll->head->next;

        /* Insert new node in head */
        ll->head->next = new_node;
        new_node->prev = ll->head;
        node_iterator->prev = new_node;
        new_node->next = node_iterator;

        return 1;
    }
    else if(opcode == INSERT_TAIL)
    {
        /* Saves pointer */
        node_iterator = ll->tail->prev;

        /* Insert new node in tail */
        ll->tail->prev = new_node;
        new_node->next = ll->tail;
        node_iterator->next = new_node;
        new_node->prev = node_iterator;

        return 1;
    }
    else if(opcode == ASCENDING)
    {
        /* If linked list is empty */
        if(ll_is_empty(ll))
            ll_add(ll, new_node, PUSH);
        else /* Linked list has elements */
        {
            /* Saves pointer */
            node_iterator = ll->head->next;

            if(node_iterator->data > new_node->data)
                ll_add(ll, new_node, PUSH);
            else
            {
                /* Traverse through ll and check conditions */
                while((node_iterator->data < new_node->data) && (node_iterator != ll->tail))
                {
                    node_iterator = node_iterator->next;
                }

                /* Insert on tail */
                if(node_iterator == ll->tail)
                {
                    ll_add(ll, new_node, INSERT_TAIL);
                }
                else /* Insert somewhere in ll [nor tail nor head] */
                {
                    node_iterator->prev->next = new_node;
                    new_node->prev = node_iterator->prev;
                    new_node->next = node_iterator;
                    node_iterator->prev = new_node;
                }
            }
        }
        return 1;
    }
    else if(opcode == DESCENDING)
    {
        /* If linked list is empty */
        if(ll_is_empty(ll))
            ll_add(ll, new_node, INSERT_TAIL);
        else /* Linked list has elements */
        {
            /* Saves pointer */
            node_iterator = ll->tail->prev;

            if(node_iterator->data > new_node->data)
                ll_add(ll, new_node, INSERT_TAIL);
            else
            {
                /* Traverse through ll and check conditions */
                while((node_iterator->data < new_node->data) && (node_iterator != ll->head))
                {
                    node_iterator = node_iterator->prev;
                }

                /* Insert on head */
                if(node_iterator == ll->head)
                {
                    ll_add(ll, new_node, PUSH);
                }
                else /* Insert somewhere in ll [nor tail nor head] */
                {
                    node_iterator->next->prev = new_node;
                    new_node->next = node_iterator->next;
                    new_node->prev = node_iterator;
                    node_iterator->next = new_node;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* Extracts node based on opcode given */
int ll_extract(t_ll* ll, int key, int opcode)
{
    t_node* node_iterator;
    t_node* node_destroyer;

    /* Nothing to extract */
    if(ll_is_empty(ll))
        return 0;
    else if(opcode == POP)
    {
        node_destroyer = ll->head->next;
        ll->head->next = node_destroyer->next;
        node_destroyer->next->prev = ll->head;
        node_destroy(node_destroyer);
        ll->sz_ll = ll->sz_ll - 1;
        return 1;
    }
    else if(opcode == EXTRACT_TAIL)
    {
        node_destroyer = ll->tail->prev;
        ll->tail->prev = node_destroyer->prev;
        node_destroyer->prev->next = ll->tail;
        node_destroy(node_destroyer);
        ll->sz_ll = ll->sz_ll - 1;
        return 1;
    }
    else if(opcode == SEARCH_KEY)
    {
        node_iterator = ll->head->next;

        while((node_iterator->data != key) && (node_iterator != ll->tail))
        {
            node_iterator = node_iterator->next;
        }
        if((node_iterator->data != key) || (node_iterator == ll->tail))
            return 0;
        else
        {
            node_destroyer = node_iterator;
            node_destroyer->prev->next = node_destroyer->next;
            node_destroyer->next->prev = node_destroyer->prev;
            node_destroy(node_destroyer);
            ll->sz_ll = ll->sz_ll - 1;
            return 1;
        }
    }
    return 0;
}

/* Displays info about LL */
void ll_print(t_ll* ll)
{
    t_node* node_iterator;

    printf("LinkedList size: %d\n", ll->sz_ll);
    printf("LinkedList -> ");

    node_iterator = ll->head->next;
    while(node_iterator != ll->tail)
    {
        printf("%d ", node_iterator->data);
        node_iterator = node_iterator->next;
    }
    printf("\n");
}