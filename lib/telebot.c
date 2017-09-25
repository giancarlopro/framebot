#include <telebot.h>

void telebot_init() {

    network_init();
    log_init();
    read_config();
}

/* Authentic bot token */
Bot * telebot(char *token) {
    User *bot_user;

    bot_user = get_me(token);
    
    if (bot_user) {
        Bot *obot = bot(token, bot_user);
        return obot;
    }

    return NULL;
}

/* A simple method for testing your bot's auth token */
User *get_me(char *token) {
    User *ouser;
    char *message_log;

    MemStore *data = call_method(token, "getMe");

    if (data) {
        ouser = get_me_parse(data->content);
        mem_store_free(data);

        if (ouser){
            get_me_log(ouser);
            return ouser;
        }
    }

    get_me_log(NULL);

    return NULL;
}

/* Pull new message 'bot'*/
Update *get_updates(Bot *bot, char *extra) {
    MemStore *json;
    char *base;
    size_t update_len, i;
    json_t *root = NULL, *ok, *result;
    Update *up = NULL, *_up = NULL;

    if(extra){
        base = format("getUpdates?%s", extra);
        json = call_method(bot->token, base);
        free(base);
    }else{
        json = call_method(bot->token, "getUpdates");
    }

    root = load(json->content);
    if(json_is_object(root)) {
        ok = json_object_get(root, "ok");

        if(json_is_true(ok)) {
            result = json_object_get(root, "result");
            update_len = json_array_size(result);

            if(update_len > 0) {
                for (i = 0; i < update_len; i++) {
                    if(!up) {
                        up = update_parse(json_array_get(result, i));
                        continue;
                    }
                    _up = update_parse(json_array_get(result, i));
                    if(_up != NULL)
                        update_add(up, _up);
                }

                if(up){
                    json_decref(root);
                    return up;
                }
            }
        }
        json_decref(root);
    }

    return NULL;
}

/* send message to telegram */
int send_message(Bot *bot, long int chat_id, char *text, char *extra) {
    MemStore *json;
    char *method_base = NULL;
    json_t *root, *ok;


    if (!chat_id || !text)
        return -1;

    if (extra) {
        method_base = format("sendMessage?chat_id=%ld&text=%s&%s", chat_id, text, extra);

        free(extra);
    } else {
        method_base = format("sendMessage?chat_id=%ld&text=%s", chat_id, text);
    }
    

    json = call_method(bot->token, method_base);

    free(method_base);

    if (!json)
        return -1;

    root = load(json->content);

    if (json_is_object(root)) {
        ok = json_object_get(root, "ok");
    
        if (json_is_true(ok)){
            json_decref(root);

            return 1;
        }
    }
    return 0;
}

void telebot_polling(Bot *bot) {

    Update *updates, *up;

    while(1){
        updates = get_updates(bot, NULL);

        up = updates;

        while(up){

            if(up->message)
                to_message(bot, up);

            up = up->next;
        }

        sleep(1);
    }
}

void to_message(Bot *bot, Update *update) {
    char *response = NULL;
    int local_space = 0;
    Update *tmp_update, *up = update;

    printf("%s\n", up->message->text);

    response = search_command(up->message->text, &local_space);

    if(!response) {
        printf("name %s | id %ld\n", up->message->from->username, up->message->from->id);
    }
    else {
        send_message(bot, up->message->chat->id, response, NULL);
    }
}
/* Gets Chat Object */
Chat *get_chat (Bot *bot, char *chat_id) {

    if (!chat_id)
        return NULL;

    char *method_base = format("getChat?chat_id=%s", chat_id);
    MemStore *json = call_method(bot->token, method_base);
    free(method_base);

    json_t *root = load(json->content),
           *ok,
           *result;

    if (json_is_object(root)) {
        ok = json_object_get(root, "ok");
        if (json_is_true(ok)) {
            result = json_object_get(root, "result");
            return chat_parse(result);
        }
    }

    return NULL;
}
/**
 * Changes the title of the given chat_id
 *
 * Return code:
 *  -1 You don't have permissions
 *  -2 Missing arguments
 */
int set_chat_title (Bot *bot, char *chat_id, char *title) {

    if(!chat_id || !title)
        return -2;
    
    char *method_base = format("setChatTitle?chat_id=%s&title=%s", chat_id, title);
    MemStore *json = call_method(bot->token, method_base);
    free(method_base);

    json_t *root = load(json->content),
           *ok,
           *result;

    if (json_is_object(root)) {
        ok = json_object_get(root, "ok");
        if (json_is_true(ok)) {
            result = json_object_get(root, "result");
            if (json_is_true(result)) {
                json_decref(root);
                return 1;
            }
        }
    }

    return -1;
}
/** 
 * 
*/
ChatMember *get_chat_member(Bot *bot, char *chat_id, char *user_id) {

    if (!chat_id || !user_id)
        return NULL;

    char *method_base = format("getChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    MemStore *json = call_method(bot->token, method_base);
    free(method_base);

    json_t *root = load(json->content),
           *ok,
           *result;

    if (json_is_object(root)) {
        ok = json_object_get(root, "ok");
        if (json_is_true(ok)) {
            result = json_object_get(root, "result");
            return chat_member_parse(result);
        }
    }

    return NULL;
}