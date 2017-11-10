#include <telebot.h>

void telebot_init () {

//#ifndef CONFIG_DEFAULT /* read or not read config file */
//    read_config();
//#endif
    network_init();
/*    log_init();*/
}

/**
 * Authentic bot token
 */
Bot * telebot (const char *token) {

    User *bot_user = get_me(token);
    
    if (bot_user) {
        Bot *obot = bot(token, bot_user);

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


Message * send_message_channel (Bot *bot, char * chat_id, char *text, char *extra) {

    json_t *send_message;
    if (extra) {
        send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s&%s", chat_id, text, extra);
        free(extra);
    } else {
        send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s", chat_id, text);
    }

    return message_parse(send_message);
}

/**
 * Sends the given message to the given chat.
 * TODO:
 *  - Change the type of 'chat_id'
 * https://core.telegram.org/bots/api#sendmessage
 */
Message * send_message_chat (Bot *bot, long int chat_id, char *text, char *extra) {
    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message =  send_message_channel (bot, cchat_id, text, extra);

    return message;
}

/**
 * Returns the Chat object of the given chat_id
 * https://core.telegram.org/bots/api#getchat
 */ 
Chat *get_chat (Bot *bot, char *chat_id) {
    
    json_t *chat_res = generic_method_call(bot->token, "getChat?chat_id=%s", chat_id);
    return chat_parse(chat_res);
}
/**
 * Changes the title of the given chat_id
 * Returns 1 in success, 0 otherwise
 * https://core.telegram.org/bots/api#setchattitle
 */
int set_chat_title (Bot *bot, char *chat_id, char *title) {
    
    json_t *is_chat_title = generic_method_call(bot->token, "setChatTitle?chat_id=%s&title=%s", chat_id, title);
    return json_is_true(is_chat_title);
}
/**
 * Returns the requested ChatMember object.
 * https://core.telegram.org/bots/api#getchatmember
 */
ChatMember *get_chat_member (Bot *bot, char *chat_id, char *user_id) {
    
    json_t *chat_member = generic_method_call(bot->token, "getChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    return chat_member_parse(chat_member);
}
/**
 * Changes the given chat or channel description
 * https://core.telegram.org/bots/api#setchatdescription
 */
bool set_chat_description (Bot *bot, char *chat_id, char *description) {
    
    json_t *is_description = generic_method_call(bot->token, "setChatDescription?chat_id=%s&description=%s", chat_id, description);
    return json_is_true(is_description);
}
/**
 * Returns the number of members in the given chat
 *https://core.telegram.org/bots/api#getchatmemberscount
 */ 
int get_chat_member_count (Bot *bot, char *chat_id) {
    
    json_t *count = generic_method_call(bot->token, "getChatMemberCount?chat_id=%s", chat_id);
    return json_integer_value(count);
}
/**
 * Ban a chat user
 * https://core.telegram.org/bots/api#kickchatmember
 */
bool kick_chat_member (Bot *bot, char *chat_id, char *user_id, char *until_date) {

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
    
    json_t *is_unbanned = generic_method_call(bot->token, "unbanChatMember?chat_id=%s&user_id=%s", chat_id, user_id);
    return json_is_true(is_unbanned);
}
/**
 * leaveChat
 * Use this method for your bot to leave a group, supergroup or channel. Returns True on success.
 * https://core.telegram.org/bots/api#leavechat
 */
bool leave_chat (Bot *bot, char *chat_id) {
    
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

    json_t *cm_array = generic_method_call(bot->token, "getChatAdministrators?chat_id=%s", chat_id);
    return chat_member_array_parse(cm_array);
}
/**
 * https://core.telegram.org/bots/api#pinchatmessage
 */
bool pin_chat_message (Bot *bot, char *chat_id, long int message_id, bool disable_notification) {

    json_t *is_pin;
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

    json_t *result = start_json(response->content);

    mem_store_free(response);

    return result;
}

/**
 * https://core.telegram.org/bots/api#getfile
 */
char * get_file (Bot * bot, char * dir, const char * file_id){
    json_t *get_file;
    char *path_file;

    get_file = generic_method_call(bot->token, "getfile?file_id=%s", file_id);

    File * ofile = file_parse(get_file);

    if(ofile){
        path_file = call_method_download(bot->token, dir, ofile);
        file_free(ofile);
    }

    return path_file;
}

/**
 * https://core.telegram.org/bots/api#getuserprofilephotos
 */
UserProfilePhotos * get_user_profile_photos(Bot * bot, char * dir, long user_id, long offset, long limit){
    json_t * user_profile;
    char *method, *path_file;
    size_t photosze_len, method_len = 80;
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

    user_profile = generic_method_call(bot->token, method);

    UserProfilePhotos * oupp = user_profile_photos_parse(user_profile);

    return oupp;
}

Message * send_photo_channel(Bot * bot, char * chat_id, char * filename,
                             char * caption, bool disable_notification,
                             long int reply_to_message_id){
    IFile ifile;
    int n;
    char btrue[] = "true";

    ifile.type = SENDPHOTO;
    
    /* Unique identifier for the target */
    ifile.photo.chat_id = chat_id;

    /* Photo to send */
    ifile.photo.filename = filename;

    /* Photo caption (may also be used when resending 
     * photos by file_id), 0-200 characters */
    ifile.photo.caption = caption;

    /* Sends the message silently */
    if(disable_notification > 0)
      ifile.photo.disable_notification = btrue;
    else
      ifile.photo.disable_notification = NULL;

    /* If the message is a reply, ID of the original message */
    if(reply_to_message_id < 1){
      n = snprintf(NULL, 0, "%ld", reply_to_message_id);
      char creply_to_message_id[n + 1];
      snprintf(creply_to_message_id, n + 1, "%ld", reply_to_message_id);
      creply_to_message_id[n] = '\0';
      ifile.photo.reply_to_message_id = creply_to_message_id;
    }
    else{
      ifile.photo.reply_to_message_id = NULL;
    }

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    return message_parse(message);
}

Message * send_photo_chat(Bot * bot, long int chat_id, char * filename,
                          char * caption, bool disable_notification,
                          long int reply_to_message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_photo_channel(bot, cchat_id, filename, caption,
                                 disable_notification, reply_to_message_id);

    return message;
}

Message * send_audio_channel(Bot *bot, char * chat_id, char * filename,
                             char * caption, long int duration, char * performer,
                             char * title, bool disable_notification,
                             long int reply_to_message_id){
    IFile ifile;
    int n;
    char btrue[] = "true";

    ifile.type = SENDAUDIO;

    /* Unique identifier for the target */
    ifile.audio.chat_id = chat_id;

    /* Audio file to send */
    ifile.audio.filename = filename;

    /* Audio caption, 0-200 characters */
    ifile.audio.caption = caption;

    /* Duration of the audio in seconds */
    if(duration > 0){
        n = snprintf(NULL, 0, "%ld", duration);
        char cduration[ n + 1];
        snprintf(cduration, n + 1, "%ld", duration);
        cduration[n] = '\0';
        ifile.audio.duration = cduration;
    }
    else{
        ifile.audio.duration = NULL;
    }

    /* Performer */
    ifile.audio.performer = performer;

    /* Track name */
    ifile.audio.title = title;

    /* Sends the message silently */
    if(disable_notification > 0)
        ifile.audio.disable_notification = btrue;
    else
        ifile.audio.disable_notification = NULL;

    /* If the message is a reply, ID of the original message */
    if(reply_to_message_id < 1){
        n = snprintf(NULL, 0, "%ld", reply_to_message_id);
        char creply_to_message_id[n + 1];
        snprintf(creply_to_message_id, n + 1, "%ld", reply_to_message_id);
        creply_to_message_id[n] = '\0';
        ifile.audio.reply_to_message_id = creply_to_message_id;
    }
    else{
        ifile.audio.reply_to_message_id = NULL;
    }

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    return message_parse(message);
}

Message * send_audio_chat(Bot * bot, long int chat_id, char * filename,
                             char * caption, long int duration, char * performer,
                             char * title, bool disable_notification,
                             long int reply_to_message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_audio_channel(bot, cchat_id, filename, caption, duration,
                                 performer, title, disable_notification,
                                 reply_to_message_id);

    return message;
}

Message * send_document_channel(Bot * bot, char * chat_id, char * filename,
                             char * caption, bool disable_notification,
                             long int reply_to_message_id){
    IFile ifile;
    int n;
    char btrue[] = "true";

    ifile.type = SENDDOCUMENT;

    /* Unique identifier for the target */
    ifile.document.chat_id = chat_id;

    /* Document to send */
    ifile.document.filename = filename;

    /* Document caption (may also be used when resending 
     * Documents by file_id), 0-200 characters */
    ifile.document.caption = caption;

    /* Sends the message silently */
    if(disable_notification > 0)
      ifile.document.disable_notification = btrue;
    else
      ifile.document.disable_notification = NULL;

    /* If the message is a reply, ID of the original message */
    if(reply_to_message_id < 1){
      n = snprintf(NULL, 0, "%ld", reply_to_message_id);
      char creply_to_message_id[n + 1];
      snprintf(creply_to_message_id, n + 1, "%ld", reply_to_message_id);
      creply_to_message_id[n] = '\0';
      ifile.document.reply_to_message_id = creply_to_message_id;
    }
    else{
      ifile.document.reply_to_message_id = NULL;
    }

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    return message_parse(message);
}

Message * send_document_chat(Bot * bot, long int chat_id, char * filename,
                          char * caption, bool disable_notification,
                          long int reply_to_message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_document_channel(bot, cchat_id, filename, caption,
                                 disable_notification, reply_to_message_id);

    return message;
}

Message * send_video_channel(Bot * bot, char * chat_id, char * filename,
                             long int duration, long int width, long int height,
                             char * caption, bool disable_notification,
                             long int reply_to_message_id){
    IFile ifile;
    int n;
    char btrue[] = "true";

    ifile.type = SENDVIDEO;

    /* Unique identifier for the target */
    ifile.video.chat_id = chat_id;

    /* Audio file to send */
    ifile.video.filename = filename;

    /* Duration of the audio in seconds */
    if(duration > 0){
        n = snprintf(NULL, 0, "%ld", duration);
        char cduration[ n + 1];
        snprintf(cduration, n + 1, "%ld", duration);
        cduration[n] = '\0';
        ifile.video.duration = cduration;
    }
    else{
        ifile.video.duration = NULL;
    }

    /* Video width */
    if(width > 0){
        n = snprintf(NULL, 0, "%ld", width);
        char cwidth[ n + 1];
        snprintf(cwidth, n + 1, "%ld", width);
        cwidth[n] = '\0';
        ifile.video.width = cwidth;
    }
    else{
        ifile.video.width = NULL;
    }

    /* Video height */
    if(height > 0){
        n = snprintf(NULL, 0, "%ld", height);
        char cheight[ n + 1];
        snprintf(cheight, n + 1, "%ld", height);
        cheight[n] = '\0';
        ifile.video.height = cheight;
    }
    else{
        ifile.video.height = NULL;
    }

    /* Audio caption, 0-200 characters */
    ifile.video.caption = caption;

    /* Sends the message silently */
    if(disable_notification > 0)
        ifile.video.disable_notification = btrue;
    else
        ifile.video.disable_notification = NULL;

    /* If the message is a reply, ID of the original message */
    if(reply_to_message_id < 1){
        n = snprintf(NULL, 0, "%ld", reply_to_message_id);
        char creply_to_message_id[n + 1];
        snprintf(creply_to_message_id, n + 1, "%ld", reply_to_message_id);
        creply_to_message_id[n] = '\0';
        ifile.video.reply_to_message_id = creply_to_message_id;
    }
    else{
        ifile.video.reply_to_message_id = NULL;
    }

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    return message_parse(message);
}

Message * send_video_chat(Bot * bot, long int chat_id, char * filename,
                          long int duration, long int width, long int height,
                          char * caption, bool disable_notification,
                          long int reply_to_message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_video_channel(bot, cchat_id, filename, duration, width,
                                 height, caption, disable_notification,
                                 reply_to_message_id);

    return message;
}

Message * send_voice_channel(Bot *bot, char * chat_id, char * filename,
                             char * caption, long int duration, bool disable_notification,
                             long int reply_to_message_id){
    IFile ifile;
    int n;
    char btrue[] = "true";

    ifile.type = SENDVOICE;

    /* Unique identifier for the target */
    ifile.voice.chat_id = chat_id;

    /* Audio file to send */
    ifile.voice.filename = filename;

    /* Audio caption, 0-200 characters */
    ifile.voice.caption = caption;

    /* Duration of the audio in seconds */
    if(duration > 0){
        n = snprintf(NULL, 0, "%ld", duration);
        char cduration[ n + 1];
        snprintf(cduration, n + 1, "%ld", duration);
        cduration[n] = '\0';
        ifile.voice.duration = cduration;
    }
    else{
        ifile.voice.duration = NULL;
    }

    /* Sends the message silently */
    if(disable_notification > 0)
        ifile.voice.disable_notification = btrue;
    else
        ifile.voice.disable_notification = NULL;

    /* If the message is a reply, ID of the original message */
    if(reply_to_message_id < 1){
        n = snprintf(NULL, 0, "%ld", reply_to_message_id);
        char creply_to_message_id[n + 1];
        snprintf(creply_to_message_id, n + 1, "%ld", reply_to_message_id);
        creply_to_message_id[n] = '\0';
        ifile.voice.reply_to_message_id = creply_to_message_id;
    }
    else{
        ifile.voice.reply_to_message_id = NULL;
    }

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    return message_parse(message);
}

Message * send_voice_chat(Bot *bot, long int chat_id, char * filename,
                          char * caption, long int duration, bool disable_notification,
                          long int reply_to_message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_voice_channel(bot, cchat_id, filename, caption, duration,
                                 disable_notification,reply_to_message_id);

    return message;
}

Message * send_video_note_channel(Bot * bot, char * chat_id, char * filename,
                                  long int duration, long int length,
                                  bool disable_notification, long int reply_to_message_id){
    IFile ifile;
    int n;
    char btrue[] = "true";

    ifile.type = SENDVIDEONOTE;

    /* Unique identifier for the target */
    ifile.videonote.chat_id = chat_id;

    /* Document to send */
    ifile.videonote.filename = filename;

    /* Duration of the audio in seconds */
    if(duration > 0){
        n = snprintf(NULL, 0, "%ld", duration);
        char cduration[ n + 1];
        snprintf(cduration, n + 1, "%ld", duration);
        cduration[n] = '\0';
        ifile.videonote.duration = cduration;
    }
    else{
        ifile.videonote.duration = NULL;
    }

    /* Video width and height */
    if(length > 0){
        n = snprintf(NULL, 0, "%ld", length);
        char clength[ n + 1];
        snprintf(clength, n + 1, "%ld", length);
        clength[n] = '\0';
        ifile.videonote.length = clength;
    }
    else{
        ifile.videonote.length = NULL;
    }

    /* Sends the message silently */
    if(disable_notification > 0)
      ifile.videonote.disable_notification = btrue;
    else
      ifile.videonote.disable_notification = NULL;

    /* If the message is a reply, ID of the original message */
    if(reply_to_message_id < 1){
      n = snprintf(NULL, 0, "%ld", reply_to_message_id);
      char creply_to_message_id[n + 1];
      snprintf(creply_to_message_id, n + 1, "%ld", reply_to_message_id);
      creply_to_message_id[n] = '\0';
      ifile.videonote.reply_to_message_id = creply_to_message_id;
    }
    else{
      ifile.videonote.reply_to_message_id = NULL;
    }

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    return message_parse(message);
}

Message * send_video_note_chat(Bot * bot, long int chat_id, char * filename,
                               long int duration, long int length,
                               bool disable_notification, long int reply_to_message_id){
    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_video_note_channel(bot, cchat_id, filename, duration,
                                 length, disable_notification,
                                 reply_to_message_id);

    return message;
}

Error * show_error(){
    Error * error = get_error();

    return error;
}

Message * forward_message_from_channel (
                        Bot * bot, long int chat_id, char * from_chat_id, 
                        bool disable_notification, long int message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message =  forward_message_channel (bot, cchat_id, from_chat_id, disable_notification, message_id);

    return message;
}

Message * forward_message_from_chat (
                        Bot * bot, char * chat_id, long int from_chat_id, 
                        bool disable_notification, long int message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", from_chat_id);
    char cfrom_chat_id[n + 1];
    snprintf(cfrom_chat_id, n + 1, "%ld", from_chat_id);
    cfrom_chat_id[n] = '\0';

    message =  forward_message_channel (bot, chat_id, cfrom_chat_id, disable_notification, message_id);

    return message;
}

Message * forward_message_channel (
                        Bot * bot, char * chat_id, char * from_chat_id, 
                        bool disable_notification, long int message_id){

    json_t *forward_message;
    if (disable_notification)
        forward_message = generic_method_call(bot->token, 
            "forwardMessage?chat_id=%s&from_chat_id=%s&disable_notification=%s&message_id=%ld",
            chat_id, from_chat_id, "True", message_id);
    else
        forward_message = generic_method_call(bot->token,
            "forwardMessage?chat_id=%s&from_chat_id=%s&message_id=%ld",
            chat_id, message_id, message_id);

    return message_parse(forward_message);
}

Message * forward_message_chat (
                        Bot * bot, long int chat_id, long int from_chat_id, 
                        bool disable_notification, long int message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    n = snprintf(NULL, 0, "%ld", from_chat_id);
    char cfrom_chat_id[n + 1];
    snprintf(cfrom_chat_id, n + 1, "%ld", from_chat_id);
    cfrom_chat_id[n] = '\0';

    message =  forward_message_channel (bot, cchat_id, cfrom_chat_id, disable_notification, message_id);

    return message;
}

Message * send_location_channel (Bot * bot, char * chat_id, float latitude,
    float longitude, long int live_period, bool disable_notification,
    long int reply_to_message_id){

    json_t * location;

    if(disable_notification && reply_to_message_id){
        location = generic_method_call(bot->token,
            "sendLocation?chat_id=%s&latitude=%f&longitude=%f&live_period=%ld&disable_notification=%s&reply_to_message_id=%ld",
            chat_id, latitude, longitude, live_period, "true", reply_to_message_id);
    }
    else if(disable_notification)
        location = generic_method_call(bot->token,
            "sendLocation?chat_id=%s&latitude=%f&longitude=%f&live_period=%ld&disable_notification=%s",
            chat_id, latitude, longitude, live_period, "true");
    else if(reply_to_message_id)
        location = generic_method_call(bot->token,
            "sendLocation?chat_id=%s&latitude=%f&longitude=%f&live_period=%ld&reply_to_message_id=%ld",
            chat_id, latitude, longitude, live_period, reply_to_message_id);
    else
        location = generic_method_call(bot->token,
            "sendLocation?chat_id=%s&latitude=%f&longitude=%f&live_period=%ld",
            chat_id, latitude, longitude, live_period);

    return message_parse(location);
}

Message * send_location_chat (Bot * bot, long int chat_id, float latitude,
    float logitude, long int live_period, bool disable_notification,
    long int reply_to_message_id){

    Message * message;
    int n;

    n = snprintf(NULL, 0, "%ld", chat_id);
    char cchat_id[n + 1];
    snprintf(cchat_id, n + 1, "%ld", chat_id);
    cchat_id[n] = '\0';

    message = send_location_channel(bot, cchat_id, latitude, logitude,
                    live_period, disable_notification, reply_to_message_id);

    return message;
}
