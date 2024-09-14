#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "hash.h"
#include "list.h"
#include "document_frequency.h"

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
    return cmp_str(((HashTableItem *)a)->key, ((HashTableItem *)b)->key);
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

    // Libera a memória alocada
    hash_table_destroy(index_table);

    return 0;
}
