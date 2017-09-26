#include <telebot.h>

#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#define CURL_STATICLIB 
#include <curl/curl.h>

int main(){

    telebot_init();

    /* return token authentication or not */
    Bot *bot = telebot(get_token());
    if(bot == NULL){
        printf("%s\n", GETME_ELOG);
        exit(-1);
    }

    telebot_polling(bot);

/*  Update *update_msg = get_updates(bot, NULL);
    Update *tmp = NULL;

    int i = 0, j;
    for (; i < update_len(update_msg); i++) {
        tmp = update_get(update_msg, i);

        if (tmp && tmp->message) {
            
            printf("\n[MESSAGE:%d] %s", (i + 1), tmp->message->text);
            printf("\n[SENDING:] 'Hello human' to %d@%s", tmp->message->from->id, tmp->message->from->username);

            j = send_message(bot, tmp->message->chat->id, "Hello *human* how are you", format("reply_to_message_id=%ld&parse_mode=Markdown", tmp->message->message_id));

            printf("\n[RETURNED:] %d", j);
        }
    }*/

    return 0;
}
