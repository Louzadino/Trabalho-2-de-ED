#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

void load_index(HashTable *index_table, const char *file_name) 
{
    FILE * file = fopen(file_name, "r");

    if (!file) exit(printf("ERRO: nao foi possivel abrir o arquivo %s\n", file_name));

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