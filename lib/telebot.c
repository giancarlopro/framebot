#include <telebot.h>

void telebot_init () {

    network_init();
    log_init();
    read_config();
}

/* Authentic bot token */
Bot * telebot(const char *token) {
    User *bot_user;

    bot_user = get_me(token);
    
    if (bot_user) {
        Bot *obot = bot(token, bot_user);
        return obot;
    }

    return NULL;
}

/* A simple method for testing your bot's auth token */
User *get_me(const char *token) {
    User *ouser;
    char *message_log;

    MemStore *data = call_method(token, "getMe");

    if (data) {
        ouser = get_me_parse(data->content);
        mem_store_free(data);

        return ouser;
    }

    return NULL;
}


/* Pull new message 'bot'*/
Update *get_updates (Bot *bot, char *extra) {
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
/**
 * Sends the given message to the given chat.
 * TODO:
 *  - Change the type of 'chat_id'
 */
int send_message (Bot *bot, long int chat_id, char *text, char *extra) {
    if (!text || chat_id == 0) {
        return 0;
    }

    json_t *is_send_message;
    if (extra) {
        is_send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s&%s", chat_id, text, extra);
        free(extra);
    } else {
        is_send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s", chat_id, text);
    }

    return json_is_object(is_send_message);
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
/**
 * Returns the Chat object of the given chat_id
 */ 
Chat *get_chat (Bot *bot, char *chat_id) {

    if (!chat_id) 
        return 0;
    
    json_t *chat_res = generic_method_call(bot->token, "getChat?chat_id=%s", chat_id);
    return chat_parse(chat_res);
}
/**
 * Changes the title of the given chat_id
 * Returns 1 in success, 0 otherwise
 */
int set_chat_title (Bot *bot, char *chat_id, char *title) {

    if(!chat_id || !title)
        return 0;
    
    json_t *is_chat_title = generic_method_call(bot->token, "setChatTitle?chat_id=%s&title=%s", chat_id, title);
    return json_is_true(is_chat_title);
}
/**
 * Returns the requested ChatMember object.
 */
ChatMember *get_chat_member (Bot *bot, char *chat_id, char *user_id) {

    if (!chat_id || !user_id)
        return NULL;
    
    json_t *chat_member = generic_method_call(bot->token, "getChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    return chat_member_parse(chat_member);
}

/**
 * Generic method to handle Telegram API Methods responses
 * TODO:
 *  - Error filtering
 */
json_t *generic_method_call (char *token, char *formats, ...) {
    va_list params;
    va_start(params, formats);

    char *method_base = vsformat(formats, params);
    MemStore *response = call_method(token, method_base);
    free(method_base);

    json_t *root = load(response->content),
           *ok,
           *result;
    
    mem_store_free(response);
    
    if (json_is_object(root)) {
        ok = json_object_get(root, "ok");
        if (json_is_true(ok)) {
            return json_object_get(root, "result");
        }
    }

    return NULL;
}