
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"

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
    HashTable *h = hash_table_construct(11, hash_str, cmp_str);

    int n;
    
    scanf("%d", &n); // Numero de palavras no texto

    // Contador de frequencia de palavras no texto

    for(int i = 0; i < n; i++) {
        char *name = malloc(sizeof(char) * 100);
        scanf("%s", name);
        void *prev = hash_table_get(h, name);
        
        if (prev == NULL) {
            // Inserir nova palavra
            int *freq = malloc(sizeof(int));
            *freq = 1;
            hash_table_set(h, name, freq);
        } else {
            // Palavra já existe, atualizar frequência
            int *count = (int *) prev;
            (*count)++;
            free(name); // Liberar, já que não será usada
        }
    }


    Vector *v = hash_to_vector(h);
    vector_sort(v, cmp_string);

    int size = vector_size(v);
    for(int i = 0; i < size; i++) {
        void *pair = vector_pop_front(v);
        printf("%s %d\n", (char *)((HashTableItem *)pair)->key, *(int *)((HashTableItem *)pair)->val);
    }

    vector_destroy(v);
    hash_table_destroy(h);

    return 0;
}
