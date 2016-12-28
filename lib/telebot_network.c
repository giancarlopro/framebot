#include <telebot_network.h>

void telebot_network_init(){
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

char * telebot_network_request(Bot * bot,char * method){
	//https://api.telegram.org/bot 28
	//312367410:AAE0GKFSHt8CId9sQ8yKOODnRF8j-Kk_avQ 45

	int msz = 73 + strlen(method) + 1;
	char * url = (char *)malloc(msz);

	strcpy(url,"https://api.telegram.org/bot");
	strcat(url,bot->token);
	strcat(url,"/");
	strcat(url,method);

	CURL * curl;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);

	CURLcode res;
	res = curl_easy_perform(curl);

	return url;
}
