
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node
{
    data_type value;
    struct Node *prev;
    struct Node *next;
};

Node *node_construct(data_type value, Node *prev, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    n->prev = prev;
    return n;
}

void node_destroy(Node *n)
{
    free(n);
}

void node_print_debug(Node *n, void (*print_fn)(data_type))
{
    printf("(");

    if (n->prev == NULL)
        printf("NULL");
    else
        print_fn(n->prev->value);

    printf(", ");
    print_fn(n->value);
    printf(", ");

    if (n->next == NULL)
        printf("NULL");
    else
        print_fn(n->next->value);

    printf(")");
}

void node_print(Node *n, void (*print_fn)(data_type))
{
    print_fn(n->value);
}

void node_set_prev(Node *n, Node *prev)
{
    n->prev = prev;
}

void node_set_next(Node *n, Node *next)
{
    n->next = next;
}

void node_set_value(Node *n, data_type value)
{
    n->value = value;
}

Node *node_get_prev(Node *n)
{
    return n->prev;
}

Node *node_get_next(Node *n)
{
    return n->next;
}

data_type node_get_value(Node *n)
{
    return n->value;
}