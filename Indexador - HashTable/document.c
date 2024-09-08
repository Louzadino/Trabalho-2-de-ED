#include "document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A estrutura eh um par de nome do documento e o conteudo do documento
struct Document
{
    char doc_name[MAX_DOC_NAME]; // Nome do documento
    char *doc_content; // Conteudo do documento (texto)
};

Document *doc_create(char *doc_name)
{
    Document *doc = (Document *)malloc(sizeof(Document));

    if (doc == NULL) exit(printf("ERRO: Falha ao alocar memoria para Document\n"));

    strcpy(doc->doc_name, doc_name);
    doc->doc_content = NULL;

    return doc;
}

char* doc_get_name(Document *doc)
{
    return doc->doc_name;
}

void doc_set_name(Document *doc, char *doc_name)
{
    strcpy(doc->doc_name, doc_name);
}

char* doc_get_content(Document *doc)
{
    return doc->doc_content;
}

void doc_set_content(Document *doc, char *doc_content)
{

    // Libera o conteúdo anterior, se houver
    if (doc->doc_content != NULL) free(doc->doc_content);

    // Aloca memória para o novo conteúdo e copia a string fornecida
    doc->doc_content = (char *)malloc((strlen(doc_content) + 1) * sizeof(char));

    if (doc->doc_content == NULL) 
        exit(printf("ERRO: Falha ao alocar memória para o conteúdo do documento\n"));

    strcpy(doc->doc_content, doc_content);
}

void doc_destroy(Document *doc)
{
    if (doc->doc_content != NULL) 
        free(doc->doc_content); // Libera a memória alocada para o conteúdo

    free(doc); // Libera a estrutura `Document`
}
