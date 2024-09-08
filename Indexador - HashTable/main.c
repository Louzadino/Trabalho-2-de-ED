#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "list.h"
#include "document_frequency.h"
#include "document.h"
#include "vector.h"
#include "WordIndexer.h"


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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOC_NAME 100

int main() 
{
    // Tamanho da tabela hash
    int table_size = 11;

    // Criação do indexador de palavras
    WordIndexer *indexer = word_indexer_construct(table_size, hash_str, cmp_str);

    // Lê o número de documentos
    int num_docs;
    scanf("%d", &num_docs);
    getchar(); // Para consumir o \n

    // Processa cada documento
    for (int i = 0; i < num_docs; i++) 
    {
        // Lê o nome do documento
        getchar(); // Consome '\n'
        char doc_name[MAX_DOC_NAME];
        scanf("%[^:]", doc_name);
        getchar(); // Consome ':'

        // Lê o número de palavras
        int num_words;
        scanf("%d", &num_words); // Lê e ignora o número de palavras
        getchar(); // Consome ':'

        char *content = (char *)malloc(1000 * sizeof(char));
        scanf("%[^\n]", content);

        // Processamento do conteúdo
        char *word = strtok(content, " ");
        while (word != NULL) 
        {
            // Insere a palavra no indexador
            word_indexer_add_word(indexer, word, doc_name);

            // Próxima palavra
            word = strtok(NULL, " ");
        }
    }

    // Exibe o indexador de palavras no formato esperado
    word_indexer_print(indexer);

    // Libera a memória alocada
    //word_indexer_destroy(indexer);

    return 0;
}
