#include <telebot.h>

#define IMG_ALL 0
#define MG_SMALL 1
#define IMG_MEDIUM 2
#define IMG_LARGE 3

static const char * Token = NULL;

void telebot_init () {

//#ifndef CONFIG_DEFAULT /* read or not read config file */
//    read_config();
//#endif
    network_init();
/*    log_init();*/
}

/* Authentic bot token */
Bot * telebot(const char *token) {

    User *bot_user = get_me(token);
    
    if (bot_user) {
        Bot *obot = bot(token, bot_user);
        Token = alloc_string(obot->token);

        return obot;
    }

    return NULL;
}
/**
 * Returns a User object of the owner bot.
 * https://core.telegram.org/bots/api#getme
 */ 
User *get_me (const char *token) {
    
    if (!token)
        return NULL;

    json_t *get_me_res = generic_method_call(token, "getMe");
    return user_parse(get_me_res);
}
/**
 * Returns the updates list
 * https://core.telegram.org/bots/api#getupdates
 */ 
Update *get_updates (Bot *bot, char *extra) {

    json_t *update_array;
    if (extra) {
        update_array = generic_method_call(bot->token, "getUpdates?%s", extra);
    } else {
        update_array = generic_method_call(bot->token, "getUpdates");
    }
    
    size_t length, i;
    length = json_array_size(update_array);

    Update *up = NULL, *_temp = NULL;

    if (length > 0) {
        up = update_parse(json_array_get(update_array, 0));

        for (i = 1; i < length; i++) {
            _temp = update_parse(json_array_get(update_array, i));
            if (_temp) {
                update_add(up, _temp);
            }
        }
    }

    return up;
}
/**
 * Sends the given message to the given chat.
 * TODO:
 *  - Change the type of 'chat_id'
 * https://core.telegram.org/bots/api#sendmessage
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

/**
 * Returns the Chat object of the given chat_id
 * https://core.telegram.org/bots/api#getchat
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
 * https://core.telegram.org/bots/api#setchattitle
 */
int set_chat_title (Bot *bot, char *chat_id, char *title) {

    if(!chat_id || !title)
        return 0;
    
    json_t *is_chat_title = generic_method_call(bot->token, "setChatTitle?chat_id=%s&title=%s", chat_id, title);
    return json_is_true(is_chat_title);
}
/**
 * Returns the requested ChatMember object.
 * https://core.telegram.org/bots/api#getchatmember
 */
ChatMember *get_chat_member (Bot *bot, char *chat_id, char *user_id) {

    if (!chat_id || !user_id)
        return NULL;
    
    json_t *chat_member = generic_method_call(bot->token, "getChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    return chat_member_parse(chat_member);
}
/**
 * Changes the given chat or channel description
 * https://core.telegram.org/bots/api#setchatdescription
 */
bool set_chat_description (Bot *bot, char *chat_id, char *description) {
    if (!chat_id) 
        return false;
    
    json_t *is_description = generic_method_call(bot->token, "setChatDescription?chat_id=%s&description=%s", chat_id, description);
    return json_is_true(is_description);
}
/**
 * Returns the number of members in the given chat
 *https://core.telegram.org/bots/api#getchatmemberscount
 */ 
int get_chat_member_count (Bot *bot, char *chat_id) {
    if (!chat_id)
        return false;
    
    json_t *count = generic_method_call(bot->token, "getChatMemberCount?chat_id=%s", chat_id);
    return json_integer_value(count);
}
/**
 * Ban a chat user
 * https://core.telegram.org/bots/api#kickchatmember
 */
bool kick_chat_member (Bot *bot, char *chat_id, char *user_id, char *until_date) {
    if(!chat_id || !user_id)
        return false;

    json_t *is_kicked = generic_method_call(bot->token, "kickChatMember?chat_id=%s&user_id=%s&until_date=%s", chat_id, user_id, until_date);
    return json_is_true(is_kicked);
}
/**
 * restrictChatMember
 * Use this method to restrict a user in a supergroup. 
 * The bot must be an administrator in the supergroup
 * for this to work and must have the appropriate admin rights. 
 * Pass True for all boolean parameters to lift restrictions from a user. 
 * Returns True on success.
 * https://core.telegram.org/bots/api#restrictchatmember
 */
bool restrict_chat_member (Bot *bot, char *chat_id, char *user_id, long int until_date,
                           bool can_send_messages, bool can_send_media_messages,
                           bool can_send_other_messages, bool can_add_web_page_previews) {
    
    if (!chat_id || !user_id) 
        return false;
    
    char base[300];
    strcpy(base, "restrictChatMember?chat_id=%s&user_id=%s&until_date=%ld");

    if (can_send_messages) {
        strcat(base, "&can_send_messages=True");
    }
    if (can_send_media_messages) {
        strcat(base, "&can_send_media_messages=True");
    }
    if (can_send_other_messages) {
        strcat(base, "&can_send_other_messages=True");
    }
    if (can_add_web_page_previews) {
        strcat(base, "&can_add_web_page_previews=True");
    }

    json_t *is_restricted = generic_method_call(bot->token, base, chat_id, user_id, until_date);
    return json_is_true(is_restricted);
}
/**
 * unbanChatMember
 * Use this method to unban a previously kicked user in a supergroup or channel. 
 * The user will not return to the group or channel automatically, 
 * but will be able to join via link, etc. 
 * The bot must be an administrator for this to work. 
 * Returns True on success.
 * https://core.telegram.org/bots/api#unbanchatmember
 */
bool unban_chat_member (Bot *bot, char *chat_id, char *user_id) {
    if (!chat_id || !user_id)
        return false;
    
    json_t *is_unbanned = generic_method_call(bot->token, "unbanChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    return json_is_true(is_unbanned);
}
/**
 * leaveChat
 * Use this method for your bot to leave a group, supergroup or channel. Returns True on success.
 * https://core.telegram.org/bots/api#leavechat
 */
bool leave_chat (Bot *bot, char *chat_id) {
    if (!chat_id) 
        return false;
    
    json_t *is_leave = generic_method_call(bot->token, "leaveChat?chat_id=%s", chat_id);
    return json_is_true(is_leave);
}
/**
 * promoteChatMember
 * Use this method to promote or demote a user in a supergroup or a channel.
 * The bot must be an administrator in the chat for this to work
 * and must have the appropriate admin rights.
 * Pass False for all boolean parameters to demote a user.
 * Returns True on success.
 * https://core.telegram.org/bots/api#promotechatmember
 */
bool promote_chat_member (Bot *bot, char *chat_id, char *user_id, bool can_change_info,
                          bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
                          bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
                          bool can_promote_members) {
    if (!chat_id || !user_id) 
        return false;
    
    char *base = alloc_string("promoteChatMember?chat_id=%s&user_id=%s");
    base = vsboolean_param_parser(base, 8, "can_change_info", can_change_info, "can_post_messages", can_post_messages,
                                  "can_edit_messages", can_edit_messages, "can_delete_messages", can_delete_messages,
                                  "can_invite_users", can_invite_users, "can_restrict_members", can_restrict_members,
                                  "can_pin_messages", can_pin_messages, "can_promote_members", can_promote_members
                                );

    json_t *is_restricted = generic_method_call(bot->token, base, chat_id, user_id);
    free(base);
    return json_is_true(is_restricted);
}
/**
 * exportChatInviteLink
 * Use this method to export an invite link to a supergroup or a channel.
 * The bot must be an administrator in the chat for this to work
 * and must have the appropriate admin rights.
 * Returns exported invite link as String on success.
 * 
 * You must release the returned string
 * https://core.telegram.org/bots/api#exportchatinvitelink
 */
char *export_chat_invite_link (Bot *bot, char *chat_id) {
    if (!chat_id) 
        return NULL;
    
    json_t *invite_link = generic_method_call(bot->token, "exportChatInviteLink");
    return alloc_string(json_string_value(invite_link));
}
/**
 * getChatAdministrators
 * Use this method to get a list of administrators in a chat.
 * On success, returns an Array of ChatMember objects
 * that contains information about all chat administrators except other bots.
 * If the chat is a group or a supergroup and no administrators were appointed,
 * only the creator will be returned.
 */
ChatMember *get_chat_administrators (Bot *bot, char *chat_id) {
    if (!chat_id)
        return NULL;

    json_t *cm_array = generic_method_call(bot->token, "getChatAdministrators?chat_id=%s", chat_id);
    return chat_member_array_parse(cm_array);
}
/**
 * https://core.telegram.org/bots/api#pinchatmessage
 */
bool pin_chat_message (Bot *bot, char *chat_id, long int message_id, bool disable_notification) {
    if (!chat_id || !message_id)
        return NULL;

    json_t *is_pin 
    if (disable_notification)
        is_pin = generic_method_call(bot->token, "pinChatMessage?chat_id=%s&message_id=%ld&disable_notification=%s", chat_id, message_id, "True");
    else
        is_pin = generic_method_call(bot->token, "pinChatMessage?chat_id=%s&message_id=%ld", chat_id, message_id);
    
    return json_is_true(is_pin);
}
/**
 * Generic method to handle Telegram API Methods responses
 * TODO:
 *  - Error filtering
 */
json_t *generic_method_call (const char *token, char *formats, ...) {
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

/* 
 * https://core.telegram.org/bots/api#getfile
 */
const char * get_file(char * dir, const char * file_id){
    json_t *get_file;
    char *path_file;

    get_file = generic_method_call(Token, "getfile?file_id=%s", file_id);

    File * ofile = file_parse(get_file);

    path_file = call_method_download(Token, dir, ofile);

    if(ofile){
        file_free(ofile);
        return path_file;
    }

    return NULL;
}

/*
 * https://core.telegram.org/bots/api#getuserprofilephotos
 */
const char * get_user_profile_photos(char * dir, long user_id, long offset, long limit, int _img_size){
    json_t * user_profile;
    char *method, *path_file;
    size_t photosze_len, method_len = 71;
    int i;

    method = malloc(method_len);

    if(offset == 0 && limit == 0)
        snprintf(method, method_len, "getUserProfilePhotos?user_id=%ld",
                 user_id);
    else if(offset == 0)
        snprintf(method, method_len, "getUserProfilePhotos?user_id=%ld?limit=%ld",
                 user_id, limit);
    else if(limit == 0)
        snprintf(method, method_len, "getUserProfilePhotos?user_id=%ld?offset=%ld",
                 user_id, offset);
    else
        snprintf(method, method_len, "getUserProfilePhotos?user_id=%ld?offset=%ld?limit=%ld",
                 user_id, offset, limit);

    user_profile = generic_method_call(Token, method);

    UserProfilePhotos * ouser_profile_photos = user_profile_photos_parse(user_profile);
    if(!ouser_profile_photos)
        return NULL;


//    path_file = call_method_download(Token, dir, ofile);

    if(ouser_profile_photos){
        user_profile_photos_free(ouser_profile_photos);
        return path_file;
    }

    return NULL;
}