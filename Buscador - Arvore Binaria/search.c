#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

void load_index(BinaryTree *index_tree, const char *file_name) 
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

        // Adiciona a palavra e sua lista de frequências na arvore binaria
        // strdup é usada para duplicar as strings de palavra 
        // para garantir que a memória seja gerenciada corretamente
        binary_tree_add(index_tree, strdup(word), doc_freq_list);
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

    fclose(file);
}

void process_query(BinaryTree *index_tree, Vector *stopwords, 
                    CmpFn cmp_fn,
                    KeyDestroyFn key_destroy_fn,
                    ValDestroyFn val_destroy_fn)
{
    // Lê a consulta do usuário
    char query[MAX_QUERY_SIZE];
    Vector *query_words = vector_construct();

    // Leitura da query (consulta do usuário)
    scanf(" %[^\n]", query);

    // Separar as palavras da consulta
    char *word = strtok(query, " ");
    while (word != NULL) 
    {
        // Se não for uma stopword, adiciona a palavra ao vetor de palavras da consulta
        if (vector_binary_search(stopwords, word, cmp_fn) == -1)
            vector_push_back(query_words, strdup(word));

        word = strtok(NULL, " ");
    }

    // Cria uma arvore binaria para armazenar a relevância de cada documento
    BinaryTree *doc_relevances = binary_tree_construct(cmp_fn, key_destroy_fn, val_destroy_fn);

    // Para cada palavra da consulta
    for (int i = 0; i < vector_size(query_words); i++) 
    {
        char *word = vector_get(query_words, i);

        // Busca a palavra na arvore binaria
        List *doc_freq_list = binary_tree_get(index_tree, word);

        // Verifica se a palavra foi encontrada e se a lista é válida
        if (doc_freq_list != NULL) 
        {
            // Para cada DocumentFrequency da palavra
            Node *n = list_get_head(doc_freq_list);
            while (n != NULL) 
            {
                DocumentFrequency *doc_freq = (DocumentFrequency *)n->value;
                char *doc_name = doc_freq_get_name(doc_freq);
                int freq = doc_freq_get_frequency(doc_freq);

                // Se o documento já está na arvore de relevância, incrementa a relevância
                int *relevance = binary_tree_get(doc_relevances, doc_name);
                if (relevance != NULL) 
                {
                    *relevance += freq;
                }
                else // Se o documento não está na arvore de relevância, adiciona
                {
                    binary_tree_add(doc_relevances, strdup(doc_name), new_int(freq));
                }

                n = n->next;
            }
        }
    }

    // Exibe os documentos mais relevantes
    display_top_documents(doc_relevances);

    // Destrói a arvore de relevâncias
    binary_tree_destroy(doc_relevances);

    // Destruição do vetor de palavras da consulta
    int query_words_size = vector_size(query_words);
    for (int i = 0; i < query_words_size; i++) 
        free(vector_get(query_words, i));

    vector_destroy(query_words);

    // Destruição da arvore de relevancia
    Vector *v = binary_tree_inorder_traversal(doc_relevances);
    
    for (int i = 0; i < vector_size(v); i++)
    {
        KeyValPair *kvp = (KeyValPair *)vector_get(v, i);
        key_val_pair_destroy(kvp);
    }

    vector_destroy(v);
    binary_tree_destroy(doc_relevances);
}

void display_top_documents(BinaryTree *doc_relevances)
{
    Vector *documents = binary_tree_inorder_traversal(doc_relevances);

    // Imprime qtd de documentos encontrados
    printf("%d\n", vector_size(documents));

    for (int i = 0; i < vector_size(documents); i++)
    {
        KeyValPair *kvp = (KeyValPair *)vector_get(documents, i);
        char *doc_name = (char *)kvp->key;
        int relevance = *((int *)kvp->value);

        printf("%s %d\n", doc_name, relevance);
    }

    for (int i = 0; i < vector_size(documents); i++)
    {
        KeyValPair *kvp = (KeyValPair *)vector_get(documents, i);
        key_val_pair_destroy(kvp);
    }

    vector_destroy(documents);
}
