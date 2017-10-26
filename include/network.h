#ifndef NETWORK_H
#define NETWORK_H

#include <telebot.h>

#define API_URL "https://api.telegram.org/bot"
#define API_URL_LEN 28

#define API_URL_FILE "https://api.telegram.org/file/bot"
#define API_URL_FILE_LEN 33

typedef struct _mem_store {
    char *content;
    size_t size;
} MemStore;
typedef MemStore* MemStorePtr;

void network_init();
MemStore * mem_store();
void mem_store_free(MemStore * memStore);
size_t mem_write_callback(void *content, size_t size, size_t nmemb, void *userp);
MemStore *call_method(const char *token, char *method);
char * call_method_download(const char * token, char * dir, File * ofile);


#endif
