#ifndef _DOCUMENT_FREQUENCY_H_
#define _DOCUMENT_FREQUENCY_H_


typedef struct DocumentFrequency DocumentFrequency;


#define MAX_DOC_NAME 100

DocumentFrequency *doc_freq_create(char *doc_name);

void doc_freq_destroy(DocumentFrequency *df);

#endif