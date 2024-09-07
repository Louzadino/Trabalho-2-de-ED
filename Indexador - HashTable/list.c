#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct List
{
    Node *head;
    Node *last;
    int size;
};

struct ListIterator
{
    Node *current;
};

List *list_construct()
{

    List* f = (List*) malloc(sizeof(List));

    if (!f) exit(printf("ERRO: falha ao alocar list\n"));

    f->head = NULL;
    f->last = NULL;
    f->size = 0;

    return f;
}

int list_size(List *l)
{
    if (l) return l->size;
    
    return 0;
}

void list_push_front(List *l, data_type data)
{
    Node* new_node = node_construct(data, NULL, l->head);

    if (l) 
    {
        if (l->head == NULL)
            l->head = l->last = new_node;
        else 
        {
            node_set_prev(l->head, new_node);
            l->head = new_node;
        }
        l->size++;
    }
}

void list_push_back(List *l, data_type data)
{
    Node* new_node = node_construct(data, l->last, NULL);

    if (l)
    {
        if (l->head == NULL)
            l->head = l->last = new_node;
        else
        {
            node_set_next(l->last, new_node);
            l->last = new_node;
        }
        l->size++;
    }
}

void list_print(List *l, void (*print_fn)(data_type))
{
    Node* current = l->head;  // Ponteiro auxiliar para percorrer a lista

    printf("[");
    for (int i = 0; i < list_size(l); i++)
    {
        print_fn(node_get_value(current));
        current = node_get_next(current);  // Avança para o próximo nó
        if (i < list_size(l) - 1) printf(", ");
    }
    printf("]");
} 

void list_print_reverse(List *l, void (*print_fn)(data_type))
{
    Node* current = l->last;  // Ponteiro auxiliar para percorrer a lista

    printf("[");
    while(current != NULL)
    {
        print_fn(node_get_value(current));
        if (node_get_prev(current) != NULL) printf(", ");
        current = node_get_prev(current);  // Avança para o nó anterior
    }
    printf("]");
}

data_type list_get(List *l, int i)
{

    if (i < 0 || i >= list_size(l)) 
        exit(printf("ERRO: índice fora dos limites\n"));

    Node* node = l->head;
    for (int j = 0; j < i; j++)
        node = node_get_next(node);

    return node_get_value(node);
}

data_type list_pop_front(List *l)
{

    if (l->head == NULL) exit(printf("ERRO: lista nula\n"));

    Node* node_to_pop = l->head;
    l->head = node_get_next(l->head);
    data_type value = node_get_value(node_to_pop);
    node_destroy(node_to_pop);
    l->size--;

    if (l->head != NULL)
    {
        Node* prev = node_get_prev(l->head);
        prev = NULL;
    }
    else
        l->last = l->head;

    return value;
}

data_type list_pop_back(List *l)
{
    if (l->head == NULL) exit(printf("ERRO: lista nula\n"));

    Node* node_to_pop = l->last;
    l->last = node_get_prev(l->last);
    data_type value = node_get_value(node_to_pop);
    node_destroy(node_to_pop);
    l->size--;

    if (l->last != NULL)
    {
        Node* next = node_get_next(l->last);
        next = NULL;
    }
    else
        l->head = l->last;

    return value;
}

Node* list_search_prev(List *l, int index){

    Node* curr = l->head;
    Node* prev = NULL;

    for (int count = 0; count < index; count++)
    {
        prev = curr;
        curr = node_get_next(curr);
    }

    return prev;
}

data_type list_pop_index(List *l, int index)
{

    if (index < 0 || index >= list_size(l)) printf("INVALID INDEX\n");

    Node* to_remove = l->head;
    Node* prev = list_search_prev(l, index);

    if (prev == NULL)
    {
        to_remove = l->head;
        l->head = node_get_next(l->head);
    }
    else
    {
        to_remove = node_get_next(prev);
        node_set_next(prev, node_get_next(to_remove));
    }

    data_type value = node_get_value(to_remove);
    node_destroy(to_remove);
    l->size--;

    return value;
}

List *list_reverse(List *l)
{
    List *rev_l = list_construct();
    Node* curr = l->head;

    while (curr != NULL)
    {
        list_push_front(rev_l, node_get_value(curr));
        curr = node_get_next(curr);
    }

    return rev_l;
}

void list_clear(List *l)
{

    int n_items = list_size(l);

    for (int i = 0; i < n_items; i++)
        list_pop_front(l);

    l->size = 0;
}

void list_remove(List *l, data_type val)
{

    Node* curr = l->head;
    Node* prev = NULL;
    Node* new_n = NULL;

    while (curr != NULL)
    {
        if (node_get_value(curr) == val)
        {
            if (prev == NULL)
                l->head = new_n = node_get_next(curr);
            else
            {
                node_set_next(prev, node_get_next(curr));
                new_n = node_get_next(curr);
            }

            node_destroy(curr);
            curr = new_n;
            l->size--;
        }
        else
        {
            prev = curr;
            curr = node_get_next(curr);
        }
    }
}

void list_cat(List *l, List *m){
    
    Node *curr = m->head;

    while (curr != NULL)
    {
        list_push_front(l, node_get_value(curr));   
        curr = node_get_next(curr);
    }
}

void list_destroy(List *l)
{

    if (l)
    {
        while (l->head != NULL)
        {
        Node* node_to_destroy = l->head;
        l->head = node_get_next(l->head);
        node_destroy(node_to_destroy);
        }

        free(l);
    }
}

void list_sort(List *l)
{
    Node *curr = l->head;
    Node *next = NULL;
    data_type temp;
    int swaped = 1;

    while (swaped)
    {
        swaped = 0;
        curr = l->head;
        next = node_get_next(curr);

        while (next != NULL)
        {
            data_type curr_val = node_get_value(curr);
            data_type next_val = node_get_value(next);
            if (curr_val > next_val)
            {
                temp = curr_val;
                curr_val = next_val;
                next_val = temp;
                swaped = 1;
            }

            curr = next;
            next = node_get_next(next);
        }
    }
}

ListIterator *list_front_iterator(List *l)
{
    ListIterator *it = (ListIterator*) malloc(sizeof(ListIterator));

    if (!it) exit(printf("ERRO: falha ao alocar ListIterator\n"));

    it->current = l->head;

    return it;
}

ListIterator *list_back_iterator(List *l)
{
    ListIterator *it = (ListIterator*) malloc(sizeof(ListIterator));

    if (!it) exit(printf("ERRO: falha ao alocar ListIterator\n"));

    it->current = l->last;

    return it;
}

data_type *list_iterator_next(ListIterator *it)
{
    if (it->current == NULL) return NULL;

    data_type *value = node_get_value(it->current);
    it->current = node_get_next(it->current);

    return value;
}

data_type *list_iterator_previous(ListIterator *it)
{
    if (it->current == NULL) return NULL;

    data_type *value = node_get_value(it->current);
    it->current = node_get_prev(it->current);

    return value;
}

bool list_iterator_is_over(ListIterator *it)
{
    return it->current == NULL;
}

void list_iterator_destroy(ListIterator *it)
{
    free(it);
}

Node* list_get_head(List *l)
{
    return l->head;
}

Node* list_get_last(List *l)
{
    return l->last;
}

void list_set_head(List *l, Node *n)
{
    l->head = n;
}

void list_set_last(List *l, Node *n)
{
    l->last = n;
}
