#include <network.h>

void network_init(){
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

int network_request(Bot * bot,char * method){
	size_t url_sz = strlen(bot->token) + strlen(API_URL) + strlen(method) + 2;
	char * url = (char *)malloc(url_sz);

	strcpy(url, API_URL);
	strcat(url, bot->token);
	strcat(url,"/");
	strcat(url,method);

	CURL * curl;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);

	FILE * buff = fopen("test.txt","w");//= tmpfile();
	char * buffer = (char *)malloc(MAX_BUFFER_SIZE);

	if(buff){
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, buff);

		CURLcode res = curl_easy_perform(curl);
		if(res == CURLE_OK)
			fscanf(buff,"%s",buffer);
        return res;
	}


	//return buffer;
}

User * get_me(Bot * bot){
	return NULL;
}
