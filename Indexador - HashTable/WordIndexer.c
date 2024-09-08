#include "WordIndexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Estrutura que armazena a palavra e a lista de frequências nos documentos
struct WordIndexer {
    HashTable *table; // Tabela de frequências das palavras nos documentos
};

WordIndexer *word_indexer_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn) 
{
    WordIndexer *indexer = (WordIndexer *)malloc(sizeof(WordIndexer));

    if (indexer == NULL)
        exit(printf("Erro ao alocar memória para o indexador de palavras\n"));

    indexer->table = hash_table_construct(table_size, hash_fn, cmp_fn);

    return indexer;
}

void word_indexer_add_word(WordIndexer *indexer, char *word, char* doc_name)
{
    List* df_list = (List *) hash_table_get(indexer->table, word); // Recupera a lista de DocumentFrequency da palavra

    // Se a palavra não foi encontrada na tabela, cria uma nova lista
    if (df_list == NULL) {
        df_list = list_construct();
        hash_table_set(indexer->table, word, df_list);
    }

    // Verifica se o documento já existe na lista de frequências
    Node *n = list_get_head(df_list);
    while (n) 
    {
        DocumentFrequency *current_df = (DocumentFrequency*) n->value;
        Document *doc = doc_freq_get_doc(current_df);
        char* current_doc_name = doc_get_name(doc);

        if (strcmp(current_doc_name, doc_name) == 0) {
            doc_freq_increment(current_df); // Incrementa a frequência se já existir
            return;
        }
        n = n->next;
    }

    // Se o documento não foi encontrado, cria um novo DocumentFrequency
    DocumentFrequency *new_df = doc_freq_construct(doc_name);
    list_push_front(df_list, new_df);
}

void word_indexer_print(WordIndexer *indexer) 
{
    HashTableIterator *it = hash_table_iterator(indexer->table);
    
    while (!hash_table_iterator_is_over(it)) {
        HashTableItem *item = hash_table_iterator_next(it);
        char *word = (char *) item->key;
        List *doc_list = (List *) item->val;
        
        printf("%s ", word);
        Node *n = list_get_head(doc_list);
        
        while (n != NULL) {
            DocumentFrequency *df = (DocumentFrequency *)n->value;
            Document *doc = doc_freq_get_doc(df);
            printf("%s %d ", doc_get_name(doc), doc_freq_get_frequency(df));
            n = n->next;
        }
        printf("\n");
    }
    
    hash_table_iterator_destroy(it);
}

void word_indexer_destroy(WordIndexer *indexer) 
{
    HashTableIterator *it = hash_table_iterator(indexer->table);

    while (!hash_table_iterator_is_over(it)) {
        HashTableItem *item = hash_table_iterator_next(it);
        List *df_list = (List *) item->val;

        // Destruir cada DocumentFrequency na lista
        Node *n = list_get_head(df_list);
        while (n != NULL) {
            DocumentFrequency *df = (DocumentFrequency *)n->value;
            doc_freq_destroy(df);
            n = n->next;
        }

        // Destruir a lista de DocumentFrequency
        list_destroy(df_list);
    }

    hash_table_iterator_destroy(it);
    
    // Destruir a tabela hash e o indexador
    hash_table_destroy(indexer->table);
    free(indexer);
}
