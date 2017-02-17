#include <telebot.h>

void network_init(){
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

MemStore * mem_store() {
	MemStore *mem = (MemStore *)malloc(sizeof(MemStore));

	mem->content = (char *)malloc(1);
	mem->size = 0;

	return mem;
}
void mem_store_free(MemStore * memStore) {
	if (memStore->content)
		free(memStore->content);
	free(memStore);
}

size_t mem_write_callback(void *data, size_t size, size_t nmemb, void *userp) {
	size_t finalsz = size * nmemb;
	MemStore *json = (MemStore *)userp;

	json->content = (char *)realloc(json->content, json->size + finalsz + 1);

	if (json->content) {
		strcpy(json->content, (char *)data);
		json->size += finalsz;
		json->content[json->size] = '\0';

		return finalsz;
	}

	return 0;
}

MemStore * call_method(char *token, char *method){
	size_t url_size = strlen(token) + strlen(API_URL) + strlen(method) + 2;
	char * url = (char *)malloc(url_size);

	strcpy(url, API_URL);
	strcat(url, token);
	strcat(url,"/");
	strcat(url,method);

	CURL * curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	MemStore *buff = mem_store();

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)buff);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mem_write_callback);

	if (curl_easy_perform(curl) == CURLE_OK) {
		return buff;
	}

	return NULL;
}
