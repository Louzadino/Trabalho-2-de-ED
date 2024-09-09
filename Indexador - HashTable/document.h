#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_


typedef struct Document Document;


#define MAX_DOC_NAME 100


Document *doc_construct(char *doc_name);

char* doc_get_name(Document *doc);
void doc_set_name(Document *doc, char *doc_name);

char* doc_get_content(Document *doc);
void doc_set_content(Document *doc, char *doc_content);

int doc_cmp(Document *a, Document *b);

void doc_destroy(Document *doc);

#endif