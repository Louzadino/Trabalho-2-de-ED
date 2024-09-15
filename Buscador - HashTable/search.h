#ifndef _SEARCH_H_
#define _SEARCH_H_


#include "hash.h"
#include "document_frequency.h"
#include "list.h"
#include "vector.h"


#define MAX_QUERY_SIZE 1000


void load_index(HashTable *index_table, const char *file_name);

void load_stopwords(Vector *stopwords, const char *file_name, int (*cmp)(const void*, const void*));

void process_query(HashTable *index_table, Vector *stopwords, int (*cmp)(const void*, const void*));

#endif