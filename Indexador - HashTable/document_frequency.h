#ifndef _DOCUMENT_FREQUENCY_H_
#define _DOCUMENT_FREQUENCY_H_


#include "document.h"
#define MAX_DOC_NAME 100


typedef struct DocumentFrequency DocumentFrequency;


DocumentFrequency *doc_freq_construct(char *doc_name);

Document* doc_freq_get_doc(DocumentFrequency *df);

int doc_freq_get_frequency(DocumentFrequency *df);
void doc_freq_increment(DocumentFrequency *df);

int cmp_doc_freq(DocumentFrequency* a, DocumentFrequency* b);

void doc_freq_destroy(DocumentFrequency *df);

#endif