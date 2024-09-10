#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "list.h"
#include "document_frequency.h"
#include "document.h"
#include "vector.h"
#include "WordIndexer.h"

#define MAX_DIRECTORY 1000


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

int main(int argc, char *argv[]) 
{

    // Verifica se o diretorio para a pasta de impressões foi informado

    if (argc <= 1) 
        exit(printf("ERRO: o diretorio para a pasta de impressões nao foi informado\n"));

    char dir[MAX_DIRECTORY];
    sprintf(dir, "%s", argv[1]);
    FILE *file = fopen(dir, "r");

    if (file == NULL) 
        exit(printf("ERRO: nao foi possivel abrir o arquivo\n"));

    // Lê o número de documentos
    int qtd_docs;
    fscanf(file, "%d\n", &qtd_docs);

    // Tamanho da tabela hash
    int table_size = 1999;

    // Criação do indexador de palavras
    WordIndexer *indexer = word_indexer_construct(table_size, hash_str, cmp_str);

    // Processa cada documento
    for (int i = 0; i < qtd_docs; i++) 
    {
        // Processa cada documento
        char doc_name[MAX_DOC_NAME];
        int qtd_words;

        fscanf(file, "%[^:]: %d: ", doc_name, &qtd_words);

        // Processa cada palavra do documento
        for (int k = 0; k < qtd_words; k++)
        {
            char *word = (char *)malloc(100 * sizeof(char));
            fscanf(file, "%s", word);
            word_indexer_add_word(indexer, word, doc_name);
        }

        fscanf(file, "\n");
    }

    // Exibe o indexador de palavras no formato esperado
    word_indexer_print(indexer);

    // Libera a memória alocada
    word_indexer_destroy(indexer);
    fclose(file);

    return 0;
}
