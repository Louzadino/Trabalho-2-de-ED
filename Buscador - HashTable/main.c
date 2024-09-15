#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

int hash_str(HashTable *h, void *data)
{
    char *str = (char *)data;

    long hash_val = 0;
    int base = 127;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int cmp_string(const void *a, const void *b)
{
    return cmp_str((char *)a, (char *)b);
}

int main()
{
    // Tamanho da tabela hash (mesmo usado no Indexador)
    int table_size = 2011;

    // Criação da tabela hash
    HashTable *index_table = hash_table_construct(table_size, hash_str, cmp_str);

    // Carrega o índice do arquivo
    char index_file[MAX_DOC_NAME];
    scanf("%s", index_file);
    load_index(index_table, index_file);

    // Leitura das stopwords
    Vector *stopwords = vector_construct();

    char stopwords_file[MAX_DOC_NAME];
    scanf("%s", stopwords_file);
    load_stopwords(stopwords, stopwords_file, cmp_string);

    // Leitura e processamento das palavras da consulta
    process_query(index_table, stopwords, cmp_string);

    // Libera a memória alocada
    hash_table_destroy(index_table);
    vector_destroy(stopwords);

    return 0;
}
