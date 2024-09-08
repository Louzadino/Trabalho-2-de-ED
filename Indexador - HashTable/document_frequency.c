#include "document_frequency.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A estrutura eh um par de documento e a frequencia da palavra no documento
struct DocumentFrequency {
    char doc_name[MAX_DOC_NAME];
    int frequency;
};

DocumentFrequency *doc_freq_create(char *doc_name)
{
    DocumentFrequency *df = (DocumentFrequency *)malloc(sizeof(DocumentFrequency));

    if (df == NULL) exit(printf("ERRO: Falha ao alocar memoria para DocumentFrequency\n"));

    strcpy(df->doc_name, doc_name);
    df->frequency = 1; // Inicialialmente, a palavra aparece uma vez no documento

    return df;
}

void doc_freq_destroy(DocumentFrequency *df)
{
    free(df);
}
