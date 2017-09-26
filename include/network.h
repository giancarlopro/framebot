#ifndef NETWORK_H
#define NETWORK_H

#include <telebot.h>

#define API_URL "https://api.telegram.org/bot"
#define MAX_BUFFER_SIZE (1024 * 30)

typedef struct _mem_store {
    char *content;
    size_t size;
} MemStore;
typedef MemStore* MemStorePtr;

void *handle_network(void *vbot);
void network_init();
MemStore * mem_store();
void mem_store_free(MemStore * memStore);
size_t mem_write_callback(void *content, size_t size, size_t nmemb, void *userp);
MemStore *call_method(const char *token, char *method);
int handle_send_network();

#endif
