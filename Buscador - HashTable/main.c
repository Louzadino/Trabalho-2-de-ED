#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "list.h"
#include "document_frequency.h"


void load_index(HashTable *index_table, const char *file_name) 
{
    FILE * file = fopen(file_name, "r");

    if (!file) 
        exit(printf("ERRO: nao foi possivel abrir o arquivo %s\n", file_name));

    // Lẽ o número total de palavras no índice
    int total_words;
    fscanf(file, "%d\n", &total_words);
    printf("total_words: %d\n", total_words);

    // Para cada palavra no índice
    for (int i = 0; i < total_words; i++) 
    {
        char word[MAX_WORD_SIZE];
        int num_docs;

        // Lẽ a palavra e o número de documentos que ela aparece
        fscanf(file, "%s %d", word, &num_docs);
        printf("word: %s, num_docs: %d\n", word, num_docs);

        // Cria uma nova lista para armazenar os documentos-frequência
        List *doc_freq_list = list_construct();

        // Lẽ cada documento e sua frequência
        for (int j = 0; j < num_docs; j++) 
        {
            char doc_name[MAX_DOC_NAME];
            int freq;

            fscanf(file, " %s %d", doc_name, &freq);
            printf("doc_name: %s, freq: %d\n", doc_name, freq);

            // Cria um novo DocumentFrequency e o adiciona à lista
            DocumentFrequency *doc_freq = doc_freq_construct(doc_name);
            doc_freq_set_frequency(doc_freq, freq);
            list_push_front(doc_freq_list, doc_freq);
        }

        // Adiciona a palavra e sua lista de frequências na tabela hash
        // strdup é usada para duplicar as strings de palavra 
        // para garantir que a memória seja gerenciada corretamente
        hash_table_set(index_table, strdup(word), doc_freq_list);
        printf("\n");
    }

    fclose(file);
}

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
