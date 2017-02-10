#include <telebot.h>
#include <curl/curl.h>

int main(){
    curl_global_init(CURL_GLOBAL_ALL);

    CURL * curl = curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,"https://www.google.com");

    if(curl_easy_perform(curl) == CURLE_OK){
        printf("OK!");
    }
	return 0;
}
