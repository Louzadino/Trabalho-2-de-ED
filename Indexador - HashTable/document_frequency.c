#include "document_frequency.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A estrutura é um par de documento e a frequência da palavra no documento
struct DocumentFrequency {
    Document* doc;   // Ponteiro para o documento
    int frequency;   // Frequência da palavra no documento
};

DocumentFrequency *doc_freq_create(char *doc_name)
{
    DocumentFrequency *df = (DocumentFrequency *)malloc(sizeof(DocumentFrequency));

    if (df == NULL) 
        exit(printf("ERRO: Falha ao alocar memória para DocumentFrequency\n"));

    df->doc = doc_create(doc_name); // Cria um novo documento associado
    df->frequency = 1;              // Inicialmente, a palavra aparece uma vez no documento

    return df;
}

Document* doc_freq_get_doc(DocumentFrequency *df)
{
    return df->doc;
}

int doc_freq_get_frequency(DocumentFrequency *df)
{
    return df->frequency;
}

void doc_freq_increment(DocumentFrequency *df)
{
    df->frequency++;
}

void doc_freq_destroy(DocumentFrequency *df)
{
    if (df->doc != NULL) 
        doc_destroy(df->doc);  // Libera o documento associado

    free(df); // Libera a estrutura DocumentFrequency
}
