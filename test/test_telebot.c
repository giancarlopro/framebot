#include <telebot.h>
#include <string.h>

#define TOKEN "312367410:AAE0GKFSHt8CId9sQ8yKOODnRF8j-Kk_avQ"

void test_set_chat_title(Bot *test_bot) {
    char test_chat_id[] = "-220937252";
    char test_new_title[] = "newtitletest";
    
    printf("\n[?] Testing set_chat_title()");
    int r = set_chat_title(test_bot, test_chat_id, test_new_title);

    if (r == 1) {
        Chat *chat = get_chat(test_bot, test_chat_id);

        if (strcmp(chat->title, test_new_title) == 0) {
            printf("\n[!] set_chat_title() OK!");
        } else {
            printf("\n[?] set_chat_title() ERROR!");
        }
    }
}

int main(void) {
    telebot_init();
    Bot *test_bot = telebot(TOKEN);
    if (test_bot) {
        printf("\n[+] Starting...");
        test_set_chat_title(test_bot);
    } else {
        printf("\n[!] Error!");
    }
    
    return 0;
}