
#ifndef _NODE_H_
#define _NODE_H_

typedef void* data_type;

typedef struct Node Node;

Node *node_construct(data_type value, Node *prev, Node *next);
void node_destroy(Node *n);
void node_print(Node *l, void (*print_fn)(data_type));

void node_set_prev(Node *n, Node *prev);
void node_set_next(Node *n, Node *next);
void node_set_value(Node *n, data_type value);

Node *node_get_prev(Node *n);
Node *node_get_next(Node *n);
data_type node_get_value(Node *n);

#endif