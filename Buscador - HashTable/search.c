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

    // Para cada palavra no índice
    for (int i = 0; i < total_words; i++) 
    {
        char word[MAX_WORD_SIZE];
        int num_docs;

        // Lẽ a palavra e o número de documentos que ela aparece
        fscanf(file, "%s %d", word, &num_docs);

        // Cria uma nova lista para armazenar os documentos-frequência
        List *doc_freq_list = list_construct();

        // Lẽ cada documento e sua frequência
        for (int j = 0; j < num_docs; j++) 
        {
            char doc_name[MAX_DOC_NAME];
            int freq;

            fscanf(file, " %s %d", doc_name, &freq);

            // Cria um novo DocumentFrequency e o adiciona à lista
            DocumentFrequency *doc_freq = doc_freq_construct(doc_name);
            doc_freq_set_frequency(doc_freq, freq);
            list_push_front(doc_freq_list, doc_freq);
        }

        // Adiciona a palavra e sua lista de frequências na tabela hash
        // strdup é usada para duplicar as strings de palavra 
        // para garantir que a memória seja gerenciada corretamente
        hash_table_set(index_table, strdup(word), doc_freq_list);
    }

    fclose(file);
}

void load_stopwords(Vector *stopwords, const char *file_name, int (*cmp)(const void*, const void*))
{
    FILE *file = fopen(file_name, "r");

    if (!file) exit(printf("ERRO: nao foi possivel abrir o arquivo %s\n", file_name));

    // Lẽ o número total de stopwords
    int total_stopwords;
    fscanf(file, "%d\n", &total_stopwords);

    // Para cada stopword no arquivo
    for (int i = 0; i < total_stopwords; i++) 
    {
        char word[MAX_WORD_SIZE];
        fscanf(file, "%s", word);

        // Adiciona a stopword ao vetor
        vector_push_back(stopwords, strdup(word));
    }

    // Ordenação em ordem alfabética do vetor de stopwords
    vector_sort(stopwords, cmp);

    fclose(file);
}
