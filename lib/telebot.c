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
    
    send_message = generic_method_call(bot->token, "sendMessage?chat_id=%ld&text=%s&%s",
            chat_id, text, extra);

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
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message =  send_message_channel(bot, cchat_id, text, extra);

    free(cchat_id);

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
    
    json_t *is_chat_title = generic_method_call(bot->token, "setChatTitle?chat_id=%s&title=%s",
        chat_id, title);
    return json_is_true(is_chat_title);
}



/**
 * Returns the requested ChatMember object.
 * https://core.telegram.org/bots/api#getchatmember
 */
ChatMember *get_chat_member (Bot *bot, char *chat_id, char *user_id) {
    
    json_t *chat_member = generic_method_call(bot->token, "getChatMember?chat_id=%s&user_id=%s",
        chat_id, user_id);

    return chat_member_parse(chat_member);
}



/**
 * Changes the given chat or channel description
 * https://core.telegram.org/bots/api#setchatdescription
 */
bool set_chat_description (Bot *bot, char *chat_id, char *description) {
    
    json_t *is_description = generic_method_call(bot->token, "setChatDescription?chat_id=%s&description=%s",
        chat_id, description);

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

    json_t *is_kicked = generic_method_call(bot->token,
        "kickChatMember?chat_id=%s&user_id=%s&until_date=%s", chat_id, user_id, until_date);

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
            bool can_send_messages, bool can_send_media_messages, bool can_send_other_messages,
            bool can_add_web_page_previews) {

    json_t *is_restricted = generic_method_call(bot->token, "\
restrictChatMember?chat_id=%s\
&user_id=%s\
&until_date=%ld\
&can_send_messages=%s\
&can_send_media_messages=%s\
&can_send_other_messages=%s\
&can_add_web_page_previews=%s",
        chat_id, user_id, until_date,
        (can_send_messages > 0 ? "true" : "0"),
        (can_send_media_messages > 0 ? "true" : "0"),
        (can_send_other_messages > 0 ? "true" : "0"),
        (can_add_web_page_previews > 0 ? "true" : "0") );

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
    
    json_t *is_unbanned = generic_method_call(bot->token, "unbanChatMember?chat_id=%s&user_id=%s",
        chat_id, user_id);

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
    



/*    char *base = alloc_string("promoteChatMember?chat_id=%s&user_id=%s");
    base = vsboolean_param_parser(base, 8, "can_change_info", can_change_info, "can_post_messages",
                can_post_messages, "can_edit_messages", can_edit_messages, "can_delete_messages",
                can_delete_messages, "can_invite_users", can_invite_users, "can_restrict_members",
                can_restrict_members, "can_pin_messages", can_pin_messages, "can_promote_members",
                can_promote_members );*/


    json_t *is_restricted = generic_method_call(bot->token, "\
promoteChatMember?chat_id=%s&user_id=%s\
&can_change_info=%s\
&can_post_messages=%s\
&can_edit_messages=%s\
&can_delete_messages=%s\
&can_invite_users=%s\
&can_restrict_members=%s\
&can_pin_messages=%s\
&can_promote_members=%s",
        chat_id, user_id,
        (can_change_info > 0 ? "true" : "0"),
        (can_post_messages > 0 ? "true": "0"),
        (can_edit_messages > 0 ? "true" : "0"),
        (can_delete_messages > 0 ? "true" : "0"),
        (can_invite_users > 0 ? "true": "0"),
        (can_restrict_members > 0 ? "true" : "0"),
        (can_pin_messages > 0 ? "true" : "0"),
        (can_promote_members > 0 ? "true" : "0"));
   
/*    free(base); */

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

    json_t *cm_array = generic_method_call(bot->token, 
        "getChatAdministrators?chat_id=%s", chat_id);
    
    return chat_member_array_parse(cm_array);
}



/**
 * https://core.telegram.org/bots/api#pinchatmessage
 */
bool pin_chat_message (Bot *bot, char *chat_id, long int message_id, bool disable_notification) {

    json_t *is_pin;
    is_pin = generic_method_call(bot->token,
        "pinChatMessage?chat_id=%s&message_id=%ld&disable_notification=%s",
            chat_id, message_id, (disable_notification > 0 ? "true" : "0"));
    
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
UserProfilePhotos * get_user_profile_photos(Bot * bot, char * dir, long user_id,
            long offset, long limit){

    json_t * user_profile;

    user_profile = generic_method_call(bot->token, "getUserProfilePhotos?user_id=%ld?offset=%ld?limit=%ld",
        user_id, offset, limit);

    UserProfilePhotos * oupp = user_profile_photos_parse(user_profile);

    return oupp;
}



Message * send_photo_channel(Bot * bot, char * chat_id, char * filename,
                             char * caption, bool disable_notification,
                             long int reply_to_message_id){

    IFile ifile;

    ifile.type = SENDPHOTO;
    
    /* Unique identifier for the target */
    ifile.photo.chat_id = chat_id;

    /* Photo to send */
    ifile.photo.filename = filename;

    /* Photo caption (may also be used when resending 
     * photos by file_id), 0-200 characters */
    ifile.photo.caption = caption;

    /* Sends the message silently */
    ifile.photo.disable_notification = (disable_notification > 0 ? "true" : NULL);

    /* If the message is a reply, ID of the original message */
    ifile.photo.reply_to_message_id = reply_to_message_id > 0 ? api_ltoa(reply_to_message_id) : NULL;

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    free(ifile.photo.reply_to_message_id);

    return message_parse(message);
}



Message * send_photo_chat(Bot * bot, long int chat_id, char * filename, char * caption,
            bool disable_notification, long int reply_to_message_id){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_photo_channel(bot, cchat_id, filename, caption,
                                 disable_notification, reply_to_message_id);

    free(cchat_id);

    return message;
}



Message * send_audio_channel(Bot *bot, char * chat_id, char * filename, char * caption,
            long int duration, char * performer, char * title, bool disable_notification,
            long int reply_to_message_id){
    
    IFile ifile;

    ifile.type = SENDAUDIO;

    /* Unique identifier for the target */
    ifile.audio.chat_id = chat_id;

    /* Audio file to send */
    ifile.audio.filename = filename;

    /* Audio caption, 0-200 characters */
    ifile.audio.caption = caption;

    /* Duration of the audio in seconds */
    ifile.audio.duration = duration > 0 ? api_ltoa(duration) : NULL;


    /* Performer */
    ifile.audio.performer = performer;

    /* Track name */
    ifile.audio.title = title;

    /* Sends the message silently */
    ifile.audio.disable_notification = (disable_notification > 0 ? "true" : NULL);

    /* If the message is a reply, ID of the original message */
    ifile.audio.reply_to_message_id = reply_to_message_id > 0 ? api_ltoa(reply_to_message_id) : NULL;

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    free(ifile.audio.duration);
    free(ifile.audio.reply_to_message_id);

    return message_parse(message);
}



Message * send_audio_chat(Bot * bot, long int chat_id, char * filename, char * caption,
            long int duration, char * performer, char * title, bool disable_notification,
            long int reply_to_message_id){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_audio_channel(bot, cchat_id, filename, caption, duration,
                                 performer, title, disable_notification,
                                 reply_to_message_id);

    free(cchat_id);

    return message;
}



Message * send_document_channel(Bot * bot, char * chat_id, char * filename, char * caption,
            bool disable_notification, long int reply_to_message_id){

    IFile ifile;

    ifile.type = SENDDOCUMENT;

    /* Unique identifier for the target */
    ifile.document.chat_id = chat_id;

    /* Document to send */
    ifile.document.filename = filename;

    /* Document caption (may also be used when resending 
     * Documents by file_id), 0-200 characters */
    ifile.document.caption = caption;

    /* Sends the message silently */
    ifile.document.disable_notification = (disable_notification > 0 ? "true" : NULL);

    /* If the message is a reply, ID of the original message */
    ifile.document.reply_to_message_id = reply_to_message_id > 0 ? api_ltoa(reply_to_message_id) : NULL;

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    free(ifile.document.reply_to_message_id);

    return message_parse(message);
}




Message * send_document_chat(Bot * bot, long int chat_id, char * filename, char * caption,
            bool disable_notification, long int reply_to_message_id){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_document_channel(bot, cchat_id, filename, caption,
                                 disable_notification, reply_to_message_id);

    free(cchat_id);

    return message;
}



Message * send_video_channel(Bot * bot, char * chat_id, char * filename, long int duration,
            long int width, long int height, char * caption, bool disable_notification,
            long int reply_to_message_id){
    
    IFile ifile;

    ifile.type = SENDVIDEO;

    /* Unique identifier for the target */
    ifile.video.chat_id = chat_id;

    /* Audio file to send */
    ifile.video.filename = filename;

    /* Duration of the audio in seconds */
    ifile.video.duration = duration > 0 ? api_ltoa(duration) : NULL;

    /* Video width */
    ifile.video.width = width > 0 ? api_ltoa(width) : NULL;

    /* Video height */
    ifile.video.height = height > 0 ? api_ltoa(height) : NULL;

    /* Audio caption, 0-200 characters */
    ifile.video.caption = caption;

    /* Sends the message silently */
    ifile.video.disable_notification = (disable_notification > 0 ? "true" : NULL);

    /* If the message is a reply, ID of the original message */
    ifile.video.reply_to_message_id = reply_to_message_id > 0 ? api_ltoa(reply_to_message_id) : NULL;

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    free(ifile.video.duration);
    free(ifile.video.width);
    free(ifile.video.height);
    free(ifile.video.reply_to_message_id);

    return message_parse(message);
}



Message * send_video_chat(Bot * bot, long int chat_id, char * filename, long int duration,
            long int width, long int height, char * caption, bool disable_notification,
            long int reply_to_message_id){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_video_channel(bot, cchat_id, filename, duration, width, height, caption,
                disable_notification, reply_to_message_id);

    free(cchat_id);

    return message;
}



Message * send_voice_channel(Bot *bot, char * chat_id, char * filename, char * caption,
            long int duration, bool disable_notification, long int reply_to_message_id){

    IFile ifile;

    ifile.type = SENDVOICE;

    /* Unique identifier for the target */
    ifile.voice.chat_id = chat_id;

    /* Audio file to send */
    ifile.voice.filename = filename;

    /* Audio caption, 0-200 characters */
    ifile.voice.caption = caption;

    /* Duration of the audio in seconds */
    ifile.voice.duration = duration > 0 ? api_ltoa(duration) : NULL;

    /* Sends the message silently */
    ifile.voice.disable_notification = (disable_notification > 0 ? "true" : NULL);

    /* If the message is a reply, ID of the original message */
    ifile.voice.reply_to_message_id = reply_to_message_id > 0 ? api_ltoa(reply_to_message_id) : NULL;

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    free(ifile.voice.duration);
    free(ifile.voice.reply_to_message_id);

    return message_parse(message);
}



Message * send_voice_chat(Bot *bot, long int chat_id, char * filename, char * caption, long int duration,
            bool disable_notification, long int reply_to_message_id){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_voice_channel(bot, cchat_id, filename, caption, duration,
                                 disable_notification,reply_to_message_id);

    free(cchat_id);

    return message;
}



Message * send_video_note_channel(Bot * bot, char * chat_id, char * filename, long int duration,
            long int length, bool disable_notification, long int reply_to_message_id){

    IFile ifile;

    ifile.type = SENDVIDEONOTE;

    /* Unique identifier for the target */
    ifile.videonote.chat_id = chat_id;

    /* Document to send */
    ifile.videonote.filename = filename;

    /* Duration of the audio in seconds */
    ifile.videonote.duration = duration > 0 ? api_ltoa(duration) : NULL;

    /* Video width and height */
    ifile.videonote.length = length > 0 ? api_ltoa(length) : NULL;

    /* Sends the message silently */
    ifile.videonote.disable_notification = disable_notification > 0 ? "true" : NULL;

    /* If the message is a reply, ID of the original message */
    ifile.videonote.reply_to_message_id = (reply_to_message_id > 0 ? api_ltoa(reply_to_message_id) : NULL);

    MemStore * input;
    json_t * message;

    input = call_method_input_file(bot->token, ifile);

    message = start_json(input->content);

    free(ifile.videonote.duration);
    free(ifile.videonote.length);
    free(ifile.videonote.reply_to_message_id);

    return message_parse(message);
}



Message * send_video_note_chat(Bot * bot, long int chat_id, char * filename, long int duration,
            long int length, bool disable_notification, long int reply_to_message_id){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_video_note_channel(bot, cchat_id, filename, duration, length, disable_notification,
                reply_to_message_id);

    free(cchat_id);

    return message;
}



Error * show_error(){
    Error * error = get_error();

    return error;
}



Message * forward_message_from_channel (Bot * bot, long int chat_id, char * from_chat_id,
            bool disable_notification, long int message_id){

    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message =  forward_message_channel(bot, cchat_id, from_chat_id, disable_notification, message_id);

    free(cchat_id);

    return message;
}



Message * forward_message_from_chat (Bot * bot, char * chat_id, long int from_chat_id, 
            bool disable_notification, long int message_id){

    Message * message;
    char * cfrom_chat_id;

    cfrom_chat_id = api_ltoa(from_chat_id);

    message =  forward_message_channel(bot, chat_id, cfrom_chat_id, disable_notification, message_id);

    free(cfrom_chat_id);

    return message;
}



Message * forward_message_channel (Bot * bot, char * chat_id, char * from_chat_id, 
            bool disable_notification, long int message_id){

    json_t *forward_message;
    forward_message = generic_method_call(bot->token, 
        "forwardMessage?chat_id=%s&from_chat_id=%s&disable_notification=%s&message_id=%ld",
        chat_id, from_chat_id, (disable_notification > 0 ? "true" : "0"), message_id);

    return message_parse(forward_message);
}



Message * forward_message_chat (Bot * bot, long int chat_id, long int from_chat_id, 
            bool disable_notification, long int message_id){

    Message * message;
    char * cchat_id, *cfrom_chat_id;

    cchat_id = api_ltoa(chat_id);

    cfrom_chat_id = api_ltoa(from_chat_id);

    message =  forward_message_channel(bot, cchat_id, cfrom_chat_id, disable_notification, message_id);

    free(cchat_id);
    free(cfrom_chat_id);

    return message;
}



Message * send_location_channel (Bot * bot, char * chat_id, float latitude,
            float longitude, long int live_period, bool disable_notification,
            long int reply_to_message_id){

    json_t * location;

    location = generic_method_call(bot->token,
        "sendLocation?chat_id=%s\
&latitude=%f\
&longitude=%f\
&live_period=%ld\
&disable_notification=%s\
&reply_to_message_id=%ld",
        chat_id, latitude, longitude, live_period,
        (disable_notification > 0 ? "true" : 0), reply_to_message_id );

    return message_parse(location);
}



Message * send_location_chat (Bot * bot, long int chat_id, float latitude, float logitude,
            long int live_period, bool disable_notification, long int reply_to_message_id){

    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = send_location_channel(bot, cchat_id, latitude, logitude, live_period,
                disable_notification, reply_to_message_id);

    free(cchat_id);

    return message;
}



Message * send_contact_channel(Bot * bot, char * chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id){
    json_t * message;

    message = generic_method_call(bot->token,
        "sendContact?chat_id=%s\
&phone_number=%s\
&first_name=%s\
&last_name=%s\
&disable_notification=%s\
&reply_to_message_id=%ld",
        chat_id, phone_number, first_name, last_name,
        (disable_notification > 0 ? "true":"0"), reply_to_message_id);

    return message_parse(message);
}



Message * send_contact_chat(Bot * bot, long int chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id){
    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = send_contact_channel(bot, cchat_id, phone_number, first_name, last_name, disable_notification, reply_to_message_id);

    free(cchat_id);

    return message;
}



int send_chat_action_channel(Bot * bot, char * chat_id, char * action){
    json_t * json;
    int n;

    json = generic_method_call(bot->token, "sendChatAction?chat_id=%s&action=%s",
            chat_id, action);

    return json_is_true(json) ? 0 : -1;

}



int send_chat_action_chat(Bot * bot, long int chat_id, char * action){
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    return send_chat_action_channel(bot, cchat_id, action);
}



Message * send_venue_channel(Bot * bot, char * chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id){
    json_t * json;

    json = generic_method_call(bot->token, "sendVenue?chat_id=%s\
&latitude=%f\
&longitude=%f\
&title=%s\
&address=%s\
&foursquare_id=%s\
&disable_notification=%s\
&reply_to_message_id=%ld",
        chat_id, latitude, longitude, title, address, foursquare_id,
        (disable_notification > 0 ? "true" : "0"), reply_to_message_id);

    return message_parse(json);
}



Message * send_venue_chat(Bot * bot, long int chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id){
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    return send_venue_channel(bot, cchat_id, latitude, longitude, title,
        address, foursquare_id, disable_notification, reply_to_message_id);
}
