#include <telebot.h>

/* start curl in telebot_init */
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

/* mem_write_callback is response of request Telegram */
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

/* send data to telegram */
MemStore * call_method(char *token, char *method){
	size_t url_size = strlen(API_URL) + strlen(token) + strlen(method) + 2;
	char * url = (char *)malloc(url_size);

	strcpy(url, API_URL);
	strcat(url, token);
	strcat(url, "/");
	strcat(url, method);

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

MemStore *call_method_wp(char *token, char *method, char *params) {
	size_t len = strlen(method) + strlen(params) + 1;
	char *tmp = (char *)malloc(len);
	MemStore *ms = call_method(token, tmp);
	free(tmp);

	return ms;
}

void *handle_network(void *vbot) {
	Bot *bot = (Bot *) vbot;
	Update *update;

	receives->bot = bot;


	while(1){
		update = get_updates(receives->bot, NULL);
		if(update){
			if(!receives->update)
				receives->update = update;
			else{
				update_add(receives->update, update);
			}
		}

		handle_send_network();

		sleep(2);
	}
}

int handle_send_network(){

	int result_send;
	long int message_id;
	char *text, *extra;
	long int id_chat;
	Send *send;
	Bot *bot;

	/*if(gives->send){
		send = gives->send;
		bot = gives->bot;
		id_chat = send->id_chat;
		text = send->text;
		extra = send->extra;

		result_send = send_message(bot, send->id_chat, send->text, send->extra);
		
		if(result_send == 0){
			printf("ERRO enviar %lu\n", id_chat);
		}

		/* region critic */
		/*gives->send = send->next;

	}*/

	return 0;
}
