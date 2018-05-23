#include <framebot/framebot.h>

void framebot_init () {
    network_init();
}


/**
 * Authentic bot token
 */
Bot * framebot (const char *token) {
	Bot *obot = bot(token, NULL);

    User *bot_user = get_me(obot);

    if (bot_user) {
        obot->user = bot_user;

        return obot;
    }

    bot_free(obot);

    return NULL;
}



/**
 * Returns a User object of the owner bot.
 * https://core.telegram.org/bots/api#getme
 */ 
User *get_me (Bot *bot) {
    User * user = NULL;
    refjson *s_json = NULL;

    s_json = generic_method_call(bot->token, API_GETME);
    if(!s_json)
        return NULL;

    user = user_parse(s_json->content);

    close_json(s_json);

    return user;
}



/**
 * Returns the updates list
 * https://core.telegram.org/bots/api#getupdates
 */ 
Framebot *get_updates (Bot *bot, Framebot *framebot, long int offset, long int limit,
                     long int timeout, char *allowed_updates) {

    refjson *s_json = NULL;
    Update *up = NULL;

    s_json = generic_method_call(bot->token, API_GETUPDATES,
        offset, limit, timeout, STRING_NULL(allowed_updates) );

    if( !framebot ){
        framebot = calloc(1, sizeof( Framebot ));
    }

    if(!s_json){
        return framebot;
    }

    size_t length, i;
    length = json_array_size(s_json->content);
    if(length == 0){
        close_json(s_json);
        return framebot;
    }

    for (i = 0; i < length; i++) {
        up = update_parse(json_array_get(s_json->content, i));
        framebot_add( framebot, up );
    }

    close_json(s_json);

    return framebot;
}


/**
 * Sends the given message to the given chat.
 * TODO:
 *  - Change the type of 'chat_id'
 * https://core.telegram.org/bots/api#sendmessage
 */
Message * send_message (Bot *bot, char * chat_id, char *text, char * parse_mode,
            bool disable_web_page_preview, bool disable_notification, long int reply_to_message_id,
            char * reply_markup) {
    Message * message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_SENDMESSAGE,
        chat_id, text, PARSE_MODE(parse_mode),
        DISABLE_WEB_PAGE_PREVIEW(disable_web_page_preview),
        DISABLE_NOTIFICATION(disable_notification),
        reply_to_message_id, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json ( s_json );

    return message;
}

Message * send_message_chat (Bot *bot, long int chat_id, char *text, char *parse_mode,
            bool disable_web_page_preview, bool disable_notification, long int reply_to_message_id,
            char * reply_markup) {
    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);


    message =  send_message(bot, cchat_id, text, parse_mode,
        disable_web_page_preview, disable_notification, reply_to_message_id,
        reply_markup);

    free(cchat_id);

    return message;
}



/**
 * Returns the Chat object of the given chat_id
 * https://core.telegram.org/bots/api#getchat
 */ 
Chat *get_chat (Bot *bot, char *chat_id) {
    Chat * chat;
    refjson *s_json = generic_method_call(bot->token, API_getChat, chat_id);
 
    if(!s_json)
        return NULL;

    chat = chat_parse(s_json->content);

    close_json(s_json);

    return chat;
}


Chat * get_chat_chat(Bot *bot, long int chat_id){
    Chat * chat;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    chat = get_chat(bot, cchat_id);

    free(cchat_id);

    return chat;
}


/**
 * Changes the title of the given chat_id
 * Returns 1 in success, 0 otherwise
 * https://core.telegram.org/bots/api#setchattitle
 */
int set_chat_title (Bot *bot, char *chat_id, char *title) {
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_setChatTitle,
        chat_id, title);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}


int set_chat_title_chat (Bot *bot, long int chat_id, char *title) {
    int result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = set_chat_title (bot, cchat_id, title);

    free(cchat_id);

    return result;
}


/**
 * Returns the requested ChatMember object.
 * https://core.telegram.org/bots/api#getchatmember
 */
ChatMember *get_chat_member (Bot *bot, char *chat_id, long int user_id) {
    refjson *s_json;
    ChatMember * chat_member;

    s_json = generic_method_call(bot->token, API_getChatMember,
        chat_id, user_id);

    if(!s_json)
        return NULL;

    chat_member = chat_member_parse(s_json->content);

    close_json(s_json);

    return chat_member;
}


ChatMember *get_chat_member_chat (Bot *bot, long int chat_id, long int user_id) {
    ChatMember * chat_member;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    chat_member = get_chat_member (bot, cchat_id, user_id);

    free(cchat_id);

    return chat_member;
}


/**
 * Changes the given chat or channel description
 * https://core.telegram.org/bots/api#setchatdescription
 */
bool set_chat_description (Bot *bot, char *chat_id, char *description) {
    refjson *s_json;
    bool result;

    s_json = generic_method_call(bot->token, API_setChatDescription,
        chat_id, description);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}



bool set_chat_description_chat (Bot *bot, long int chat_id, char *description) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = set_chat_description (bot, cchat_id, description);

    free(cchat_id);

    return result;
}



/**
 * Returns the number of members in the given chat
 *https://core.telegram.org/bots/api#getchatmemberscount
 */ 
int get_chat_members_count (Bot *bot, char *chat_id) {
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_getChatMemberCount, chat_id);
    
    if(!s_json)
        return -1;

    result = json_integer_value(s_json->content);

    close_json(s_json);

    return result;
}



int get_chat_members_count_chat (Bot *bot, long int chat_id) {
    int result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = get_chat_members_count (bot, cchat_id);

    free(cchat_id);

    return result;
}


/**
 * Ban a chat user
 * https://core.telegram.org/bots/api#kickchatmember
 */
bool kick_chat_member (Bot *bot, char *chat_id, long int user_id, long int until_date) {
    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_kickChatMember, chat_id,
        user_id, until_date);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

bool kick_chat_member_chat (Bot *bot, long int chat_id, long int user_id, long int until_date) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = kick_chat_member (bot, cchat_id, user_id, until_date);

    free(cchat_id);

    return result;
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
bool restrict_chat_member (Bot *bot, char *chat_id, long int user_id, long int until_date,
            bool can_send_messages, bool can_send_media_messages, bool can_send_other_messages,
            bool can_add_web_page_previews) {

    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_restrictChatMember,
        chat_id, user_id, until_date,
        CAN_SEND_MESSAGES(can_send_messages),
        CAN_SEND_MEDIA_MESSAGES(can_send_media_messages),
        CAN_SEND_OTHER_MESSAGES(can_send_other_messages),
        CAN_ADD_WEB_PAGE_PREVIEWS(can_add_web_page_previews) );

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}


bool restrict_chat_member_chat (Bot *bot, long int chat_id, long int user_id, long int until_date,
            bool can_send_messages, bool can_send_media_messages, bool can_send_other_messages,
            bool can_add_web_page_previews) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = restrict_chat_member (bot, cchat_id, user_id, until_date,
            can_send_messages, can_send_media_messages, can_send_other_messages,
            can_add_web_page_previews);

    free(cchat_id);

    return result;
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
bool unban_chat_member (Bot *bot, char *chat_id, long int user_id) {
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_unbanChatMember,
        chat_id, user_id);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}



bool unban_chat_member_chat (Bot *bot, long int chat_id, long int user_id) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = unban_chat_member (bot, cchat_id, user_id);

    free(cchat_id);

    return result;
}


/**
 * leaveChat
 * Use this method for your bot to leave a group, supergroup or channel. Returns True on success.
 * https://core.telegram.org/bots/api#leavechat
 */
bool leave_chat (Bot *bot, char *chat_id) {
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_leaveChat, chat_id);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}



bool leave_chat_chat (Bot *bot, long int chat_id) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = leave_chat (bot, cchat_id);

    free(cchat_id);

    return result;
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
bool promote_chat_member (Bot *bot, char *chat_id, long int user_id, bool can_change_info,
            bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
            bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
            bool can_promote_members) {
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_promoteChatMember,
        chat_id, user_id, CAN_CHANGE_INFO(can_change_info),
        CAN_POST_MESSAGES(can_post_messages),
        CAN_EDIT_MESSAGES(can_edit_messages),
        CAN_DELETE_MESSAGES(can_delete_messages),
        CAN_INVITE_USERS(can_invite_users),
        CAN_RESTRICT_MEMBERS(can_restrict_members),
        CAN_PIN_MESSAGES(can_pin_messages),
        CAN_PROMOTE_MEMBERS(can_promote_members));

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}


bool promote_chat_member_chat (Bot *bot, long int chat_id, long int user_id, bool can_change_info,
            bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
            bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
            bool can_promote_members) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = promote_chat_member(bot, cchat_id, user_id, can_change_info,
            can_post_messages, can_edit_messages, can_delete_messages,
            can_invite_users, can_restrict_members, can_pin_messages,
            can_promote_members);

    free(cchat_id);

    return result;
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

    refjson *s_json;
    char * invite_link;

    s_json = generic_method_call(bot->token, API_exportChatInviteLink);

    if(!s_json)
        return NULL;

    invite_link = alloc_string(json_string_value(s_json->content));

    close_json(s_json);

    return invite_link;
}


char *export_chat_invite_link_chat (Bot *bot, long int chat_id) {
    char * invite_link, *cchat_id;

    cchat_id = api_ltoa(chat_id);

    invite_link = export_chat_invite_link(bot, cchat_id);

    free(cchat_id);

    return invite_link;
}

/**
 * setChatPhoto
 * https://core.telegram.org/bots/api#setchatphoto
 */
int set_chat_photo(Bot *bot, char * chat_id, char *filename){
    bool result;

    IFile ifile;

    ifile.type = SETCHATPHOTO;
    
    /* Unique identifier for the target */
    ifile.chatphoto.chat_id = chat_id;

    ifile.chatphoto.filename = filename;

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return 0;

    s_json = start_json(input->content);
    mem_store_free(input);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

int set_chat_photo_chat(Bot *bot, long int chat_id, char *filename){
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = set_chat_photo(bot, cchat_id, filename);

    free(cchat_id);

    return result;
}


/**
 * deleteChatPhoto
 * https://core.telegram.org/bots/api#deletechatphoto
 */
int delete_chat_photo(Bot *bot, char *chat_id){
    refjson *s_json;
    bool btrue;

    s_json = generic_method_call(bot->token, API_deleteChatPhoto,
        chat_id);

    if(!s_json)
        return -1;

    btrue = json_is_true(s_json->content);

    close_json(s_json);

    return btrue;
}

int delete_chat_photo_chat(Bot *bot, long int chat_id){
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = delete_chat_photo(bot, cchat_id);

    free(cchat_id);

    return result;
}

/**
 * getChatAdministrators
 * Use this method to get a list of administrators in a chat.
 * On success, returns an Array of ChatMember objects
 * that contains information about all chat administrators except other bots.
 * If the chat is a group or a supergroup and no administrators were appointed,
 * only the creator will be returned.
 * https://core.telegram.org/bots/api#getchatadministrators
 */
ChatMember *get_chat_administrators (Bot *bot, char *chat_id) {
    ChatMember * chat_member_adm;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_getChatAdministrators, chat_id);

    if(!s_json)
        return NULL;

    chat_member_adm = chat_member_array_parse(s_json->content);

    close_json(s_json);

    return chat_member_adm;
}

ChatMember *get_chat_administrators_chat(Bot *bot, long int chat_id){
    ChatMember *chat_member_adm;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    chat_member_adm = get_chat_administrators(bot, cchat_id);

    free(cchat_id);

    return chat_member_adm;
}

/**
 * https://core.telegram.org/bots/api#pinchatmessage
 */
bool pin_chat_message (Bot *bot, char *chat_id, long int message_id, bool disable_notification) {
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_pinChatMessage, chat_id, message_id,
        DISABLE_NOTIFICATION(disable_notification));

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

bool pin_chat_message_chat(Bot *bot, long int chat_id, long int message_id, bool disable_notification) {
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = pin_chat_message(bot, cchat_id, message_id, disable_notification);

    free(cchat_id);

    return result;
}


/**
 * unpinChatMessage
 * https://core.telegram.org/bots/api#unpinchatmessage
 */
bool unpin_chat_message(Bot *bot, char *chat_id){
    int result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_unpinChatMessage,
            chat_id);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

bool unpin_chat_message_chat(Bot *bot, long int chat_id){
    bool result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = unpin_chat_message(bot, cchat_id);

    free(cchat_id);

    return result;
}

/**
 * Generic method to handle Telegram API Methods responses
 * TODO:
 *  - Error filtering
 */
refjson *generic_method_call (const char *token, char *formats, ...) {
    refjson *s_json = NULL;
    va_list params;
    va_start(params, formats);

    char *method_base = vsformat(formats, params);
    MemStore *response = call_method(token, method_base);
    free(method_base);

    if(response){
        s_json = start_json(response->content);
        mem_store_free(response);

        return s_json;
    }

    return NULL;
}



/**
 * getFile
 * https://core.telegram.org/bots/api#getfile
 * info file
 * https://core.telegram.org/bots/api#getfile
 */
File * get_file (Bot * bot, const char * file_id){

    refjson *s_json;
    int ok = 0;

    s_json = generic_method_call(bot->token, API_getfile, file_id);

    if(!s_json)
        return 0;

    File * ofile = file_parse(s_json->content);

    close_json(s_json);

    return ofile;
}

int file_download(Bot * bot, File * ofile, char *path){
    return call_method_download(bot->token, path, ofile);
}

/**
 * getUserProfilePhotos
 * https://core.telegram.org/bots/api#getuserprofilephotos
 */
UserProfilePhotos * get_user_profile_photos(Bot * bot, char *user_id,
            long offset, long limit) {
    UserProfilePhotos * oupp;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_getUserProfilePhotos,
        user_id, offset, limit);

    if(!s_json)
        return NULL;

    oupp = user_profile_photos_parse(s_json->content);

    close_json(s_json);

    return oupp;
}

UserProfilePhotos * get_user_profile_photos_chat (Bot * bot, long user_id,
            long offset, long limit) {
    UserProfilePhotos * oupp;
    char *cuser_id;

    cuser_id = api_ltoa(user_id);

    oupp = get_user_profile_photos(bot, cuser_id, offset, limit);

    free(cuser_id);

    return oupp;
}

/**
 * sendPhoto
 * https://core.telegram.org/bots/api#sendphoto
 */
Message * send_photo(Bot * bot, char * chat_id, char * filename,
                             char * caption, char *parse_mode, bool disable_notification,
                             long int reply_to_message_id, char * reply_markup){
    Message * message;

    IFile ifile;

    ifile.type = SENDPHOTO;
    
    /* Unique identifier for the target */
    ifile.photo.chat_id = chat_id;

    /* Photo to send */
    ifile.photo.filename = filename;

    /* Photo caption (may also be used when resending 
     * photos by file_id), 0-200 characters */
    ifile.photo.caption = caption;

    ifile.photo.parse_mode = PARSE_MODE(parse_mode);

    /* Sends the message silently */
    ifile.photo.disable_notification = DISABLE_NOTIFICATION(disable_notification);

    /* If the message is a reply, ID of the original message */
    ifile.photo.reply_to_message_id = REPLY_TO_MESSAGE_ID(reply_to_message_id);

    ifile.photo.reply_markup = REPLY_MARKUP(reply_markup);

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return NULL;

    s_json = start_json(input->content);

    if(!s_json)
        return NULL;

    free(ifile.photo.reply_to_message_id);
    mem_store_free(input);

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_photo_chat(Bot * bot, long int chat_id, char * filename, char * caption, char *parse_mode,
            bool disable_notification, long int reply_to_message_id, char * reply_markup){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_photo(bot, cchat_id, filename, caption, parse_mode,
                                 disable_notification, reply_to_message_id,
                                 REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}


/**
 * sendAudio
 * https://core.telegram.org/bots/api#sendaudio
 */
Message * send_audio(Bot *bot, char * chat_id, char * filename, char * caption, char *parse_mode,
            long int duration, char * performer, char * title, bool disable_notification,
            long int reply_to_message_id, char * reply_markup){
    
    Message * message;

    IFile ifile;

    ifile.type = SENDAUDIO;

    /* Unique identifier for the target */
    ifile.audio.chat_id = chat_id;

    /* Audio file to send */
    ifile.audio.filename = filename;

    /* Audio caption, 0-200 characters */
    ifile.audio.caption = caption;

    ifile.audio.caption = PARSE_MODE(parse_mode);

    /* Duration of the audio in seconds */
    ifile.audio.duration = DURATION(duration);


    /* Performer */
    ifile.audio.performer = performer;

    /* Track name */
    ifile.audio.title = title;

    /* Sends the message silently */
    ifile.audio.disable_notification = DISABLE_NOTIFICATION(disable_notification);

    /* If the message is a reply, ID of the original message */
    ifile.audio.reply_to_message_id = REPLY_TO_MESSAGE_ID(reply_to_message_id);

    ifile.audio.reply_markup = REPLY_MARKUP(reply_markup);

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return NULL;

    s_json = start_json(input->content);
    if(!s_json)
        return NULL;

    free(ifile.audio.duration);
    free(ifile.audio.reply_to_message_id);
    mem_store_free(input);

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_audio_chat(Bot * bot, long int chat_id, char * filename, char * caption, char *parse_mode,
            long int duration, char * performer, char * title, bool disable_notification,
            long int reply_to_message_id, char * reply_markup){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_audio(bot, cchat_id, filename, caption, parse_mode, duration,
                                 performer, title, disable_notification,
                                 reply_to_message_id, reply_markup);

    free(cchat_id);

    return message;
}


/**
 * sendDocument
 * https://core.telegram.org/bots/api#senddocument
 */
Message * send_document(Bot * bot, char * chat_id, char * filename, char * caption, char *parse_mode,
            bool disable_notification, long int reply_to_message_id, char * reply_markup){

    Message * message;

    IFile ifile;

    ifile.type = SENDDOCUMENT;

    /* Unique identifier for the target */
    ifile.document.chat_id = chat_id;

    /* Document to send */
    ifile.document.filename = filename;

    /* Document caption (may also be used when resending 
     * Documents by file_id), 0-200 characters */
    ifile.document.caption = caption;

    ifile.document.parse_mode = PARSE_MODE(parse_mode);

    /* Sends the message silently */
    ifile.document.disable_notification = DISABLE_NOTIFICATION(disable_notification);

    /* If the message is a reply, ID of the original message */
    ifile.document.reply_to_message_id = REPLY_TO_MESSAGE_ID(reply_to_message_id);

    ifile.document.reply_markup = REPLY_MARKUP(reply_markup);

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return NULL;

    s_json = start_json(input->content);

    if(!s_json)
        return NULL;

    free(ifile.document.reply_to_message_id);
    mem_store_free(input);

    message = message_parse(s_json->content);

    return message;
}




Message * send_document_chat(Bot * bot, long int chat_id, char * filename, char * caption, char *parse_mode,
            bool disable_notification, long int reply_to_message_id, char * reply_markup){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_document(bot, cchat_id, filename, caption, parse_mode,
                                 disable_notification, reply_to_message_id,
                                 REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}


/**
 * sendVideo
 * https://core.telegram.org/bots/api#sendvideo
 */
Message * send_video(Bot * bot, char * chat_id, char * filename, long int duration,
            long int width, long int height, char * caption, char *parse_mode, bool supports_streaming,
            bool disable_notification, long int reply_to_message_id, char * reply_markup){
    Message * message;

    IFile ifile;

    ifile.type = SENDVIDEO;

    /* Unique identifier for the target */
    ifile.video.chat_id = chat_id;

    /* Audio file to send */
    ifile.video.filename = filename;

    /* Duration of the audio in seconds */
    ifile.video.duration = DURATION(duration);

    /* Video width */
    ifile.video.width = WIDTH(width);

    /* Video height */
    ifile.video.height = HEIGHT(height);

    /* Audio caption, 0-200 characters */
    ifile.video.caption = caption;

    ifile.video.caption = PARSE_MODE(parse_mode);

    /* parse mode MODE_HTML or MODE_MARKDOWN */
    ifile.video.parse_mode = PARSE_MODE(parse_mode);


    ifile.video.supports_streaming = STREAMING(supports_streaming);

    /* Sends the message silently */
    ifile.video.disable_notification = DISABLE_NOTIFICATION(disable_notification);

    /* If the message is a reply, ID of the original message */
    ifile.video.reply_to_message_id = REPLY_TO_MESSAGE_ID(reply_to_message_id);

    ifile.video.reply_markup = REPLY_MARKUP(reply_markup);

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return NULL;

    s_json = start_json(input->content);
    if(!s_json)
        return NULL;

    free(ifile.video.duration);
    free(ifile.video.width);
    free(ifile.video.height);
    free(ifile.video.reply_to_message_id);
    mem_store_free(input);


    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_video_chat(Bot * bot, long int chat_id, char * filename, long int duration,
            long int width, long int height, char * caption, char *parse_mode, bool supports_streaming,
            bool disable_notification, long int reply_to_message_id, char * reply_markup){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_video(bot, cchat_id, filename, duration, width, height, caption, parse_mode,
                supports_streaming, disable_notification, reply_to_message_id, REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}


/**
 * sendVoice
 * https://core.telegram.org/bots/api#sendvoice
 */
Message * send_voice(Bot *bot, char * chat_id, char * filename, char * caption, char *parse_mode,
            long int duration, bool disable_notification, long int reply_to_message_id,
            char * reply_markup){
    Message * message;

    IFile ifile;

    ifile.type = SENDVOICE;

    /* Unique identifier for the target */
    ifile.voice.chat_id = chat_id;

    /* Audio file to send */
    ifile.voice.filename = filename;

    /* Audio caption, 0-200 characters */
    ifile.voice.caption = caption;

    ifile.voice.parse_mode = PARSE_MODE(parse_mode);

    /* Duration of the audio in seconds */
    ifile.voice.duration = DURATION(duration);

    /* Sends the message silently */
    ifile.voice.disable_notification = DISABLE_NOTIFICATION(disable_notification);

    /* If the message is a reply, ID of the original message */
    ifile.voice.reply_to_message_id = REPLY_TO_MESSAGE_ID(reply_to_message_id);

    ifile.voice.reply_markup = REPLY_MARKUP(reply_markup);

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return NULL;

    s_json = start_json(input->content);
    if(!s_json)
        return NULL;

    free(ifile.voice.duration);
    free(ifile.voice.reply_to_message_id);
    mem_store_free(input);

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_voice_chat(Bot *bot, long int chat_id, char * filename, char * caption, char *parse_mode, long int duration,
            bool disable_notification, long int reply_to_message_id, char * reply_markup){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_voice(bot, cchat_id, filename, caption, parse_mode, duration,
                                 disable_notification,reply_to_message_id,
                                 REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}


/**
 * sendVideoNote
 * https://core.telegram.org/bots/api#sendvideonote
 */
Message * send_video_note(Bot * bot, char * chat_id, char * filename, long int duration,
            long int length, bool disable_notification, long int reply_to_message_id, char * reply_markup){
    Message * message;

    IFile ifile;

    ifile.type = SENDVIDEONOTE;

    /* Unique identifier for the target */
    ifile.videonote.chat_id = chat_id;

    /* Document to send */
    ifile.videonote.filename = filename;

    /* Duration of the audio in seconds */
    ifile.videonote.duration = DURATION(duration);

    /* Video width and height */
    ifile.videonote.length = LENGTH(length);

    /* Sends the message silently */
    ifile.videonote.disable_notification = DISABLE_NOTIFICATION(disable_notification);

    /* If the message is a reply, ID of the original message */
    ifile.videonote.reply_to_message_id = REPLY_TO_MESSAGE_ID(reply_to_message_id);

    ifile.videonote.reply_markup = REPLY_MARKUP(reply_markup);

    MemStore * input;
    refjson *s_json;

    input = call_method_upload(bot->token, ifile);
    if(!input)
        return NULL;

    s_json = start_json(input->content);
    if(!s_json)
        return NULL;

    free(ifile.videonote.duration);
    free(ifile.videonote.length);
    free(ifile.videonote.reply_to_message_id);
    mem_store_free(input);


    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_video_note_chat(Bot * bot, long int chat_id, char * filename, long int duration,
            long int length, bool disable_notification, long int reply_to_message_id, char * reply_markup){

    Message * message;
    char * cchat_id;
    
    cchat_id = api_ltoa(chat_id);

    message = send_video_note(bot, cchat_id, filename, duration, length, disable_notification,
                reply_to_message_id, REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}



Error * show_error(){
    Error * error = get_error();

    return error;
}


/**
 * forwardMessage
 * https://core.telegram.org/bots/api#forwardmessage
 */
Message * forward_message_from (Bot * bot, long int chat_id, char * from_chat_id,
            bool disable_notification, long int message_id){

    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message =  forward_message(bot, cchat_id, from_chat_id, disable_notification, message_id);

    free(cchat_id);

    return message;
}



Message * forward_message_from_chat (Bot * bot, char * chat_id, long int from_chat_id, 
            bool disable_notification, long int message_id){

    Message * message;
    char * cfrom_chat_id;

    cfrom_chat_id = api_ltoa(from_chat_id);

    message =  forward_message(bot, chat_id, cfrom_chat_id, disable_notification, message_id);

    free(cfrom_chat_id);

    return message;
}



Message * forward_message (Bot * bot, char * chat_id, char * from_chat_id, 
            bool disable_notification, long int message_id){
    Message * message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_forwardMessage, chat_id, from_chat_id,
        DISABLE_NOTIFICATION(disable_notification), message_id);

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * forward_message_chat (Bot * bot, long int chat_id, long int from_chat_id, 
            bool disable_notification, long int message_id){

    Message * message;
    char * cchat_id, *cfrom_chat_id;

    cchat_id = api_ltoa(chat_id);

    cfrom_chat_id = api_ltoa(from_chat_id);

    message =  forward_message(bot, cchat_id, cfrom_chat_id, disable_notification, message_id);

    free(cchat_id);
    free(cfrom_chat_id);

    return message;
}


/**
 * sendLocation
 * https://core.telegram.org/bots/api#sendlocation
 */
Message * send_location (Bot * bot, char * chat_id, float latitude,
            float longitude, long int live_period, bool disable_notification,
            long int reply_to_message_id, char * reply_markup){
    Message * message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_sendLocation,
        chat_id, latitude, longitude, live_period,
        DISABLE_NOTIFICATION(disable_notification),
        reply_to_message_id, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_location_chat (Bot * bot, long int chat_id, float latitude, float logitude,
            long int live_period, bool disable_notification, long int reply_to_message_id,
            char * reply_markup){

    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = send_location(bot, cchat_id, latitude, logitude, live_period,
                disable_notification, reply_to_message_id, reply_markup);

    free(cchat_id);

    return message;
}


/**
 * sendContact
 * https://core.telegram.org/bots/api#sendcontact
 */
Message * send_contact(Bot * bot, char * chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id,
            char * reply_markup){
    refjson *s_json;
    Message * message;

    s_json = generic_method_call(bot->token, API_sendContact,
        chat_id, phone_number, first_name, last_name,
        DISABLE_NOTIFICATION(disable_notification),
        reply_to_message_id, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_contact_chat(Bot * bot, long int chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id, char * reply_markup){
    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = send_contact(bot, cchat_id, phone_number, first_name, last_name,
        disable_notification, reply_to_message_id, reply_markup);

    free(cchat_id);

    return message;
}


/**
 * sendChatAction
 * https://core.telegram.org/bots/api#sendchataction
 */
int send_chat_action(Bot * bot, char * chat_id, char * action){
    refjson *s_json;
    int result;

    s_json = generic_method_call(bot->token, API_sendChatAction,
            chat_id, action);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    return result > 0  ? 1 : 0;
}

int send_chat_action_chat(Bot * bot, long int chat_id, char * action){
    int result;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = send_chat_action(bot, cchat_id, action);

    free(cchat_id);

    return result;
}


/**
 * sendVenue
 * https://core.telegram.org/bots/api#sendvenue
 */
Message * send_venue(Bot * bot, char * chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id, char * reply_markup){
    refjson *s_json;
    Message * message;

    s_json = generic_method_call(bot->token, API_sendVenue,
        chat_id, latitude, longitude, title, address, foursquare_id,
        DISABLE_NOTIFICATION(disable_notification),
        reply_to_message_id, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}



Message * send_venue_chat(Bot * bot, long int chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id, char * reply_markup){
    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = send_venue(bot, cchat_id, latitude, longitude, title,
        address, foursquare_id, disable_notification, reply_to_message_id,
        REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}


/**
 * editMessageLiveLocation
 * https://core.telegram.org/bots/api#editmessagelivelocation
 */
Message * edit_message_live_location(Bot * bot, char * chat_id, long int message_id,
            char * inline_message_id, float latitude, float longitude, char * reply_markup){
    Message * message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_editMessageLiveLocation,
        chat_id, message_id, inline_message_id, latitude, longitude, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}

Message * edit_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,
            char * inline_message_id, float latitude, float longitude, char * reply_markup){
    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = edit_message_live_location(bot, cchat_id, message_id, inline_message_id,
        latitude, longitude, REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}

/**
 * stopMessageLiveLocation
 * https://core.telegram.org/bots/api#stopmessagelivelocation
 */
Message * stop_message_live_location(Bot * bot, char * chat_id, long int message_id,
            char * inline_message_id, char * reply_markup){
    refjson *s_json;
    Message * message;

    s_json = generic_method_call(bot->token, API_stopMessageLiveLocation,
                chat_id, message_id, inline_message_id,
                REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}

Message * stop_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,
            char * inline_message_id, char * reply_markup){
    Message * message;
    char * cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = stop_message_live_location(bot, cchat_id, message_id,
        inline_message_id, REPLY_MARKUP(reply_markup));

    free(cchat_id);

    return message;
}

/**
 * editMessageText
 * https://core.telegram.org/bots/api#editmessagetext
 */
Message *edit_message_text(Bot *bot, char *chat_id, long int message_id,
    char *inline_message_id, char *text, char *parse_mode,
    bool disable_web_page_preview, char *reply_markup){
    Message *message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_editMessageText, chat_id, message_id,
        inline_message_id, text, PARSE_MODE(parse_mode),
        DISABLE_WEB_PAGE_PREVIEW(disable_web_page_preview), REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}

Message *edit_message_text_chat(Bot *bot, long int chat_id, long int message_id,
    char *inline_message_id, char *text, char *parse_mode,
    bool disable_web_page_preview, char *reply_markup){
    Message *message;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = edit_message_text(bot, cchat_id, message_id,
        inline_message_id, text, parse_mode,
        disable_web_page_preview, reply_markup);

    free(cchat_id);

    return message;
}

/**
 * editMessageCaption
 * https://core.telegram.org/bots/api#editmessagecaption
 */
Message *edit_message_caption(Bot *bot, char *chat_id,
    long int message_id, char *inline_message_id, char *caption,
    char *parse_mode, char *reply_markup){
    Message *message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_editMessageCaption, chat_id,
        message_id, inline_message_id, caption, parse_mode, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}

Message *edit_message_caption_chat(Bot *bot, long int chat_id,
    long int message_id, char *inline_message_id, char *caption,
    char *parse_mode, char *reply_markup){
    Message *message;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = edit_message_caption(bot, cchat_id, message_id,
        inline_message_id, caption, PARSE_MODE(parse_mode), reply_markup);

    free(cchat_id);

    return message;
}


/**
 * editMessageReplyMarkup
 * https://core.telegram.org/bots/api#editmessagereplymarkup
 */
Message *edit_message_reply_markup(Bot *bot, char *chat_id, long int message_id,
        char *inline_message_id, char *reply_markup){
    Message *message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_editMessageReplyMarkup, chat_id,
        message_id, inline_message_id, REPLY_MARKUP(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json(s_json);

    return message;
}

Message *edit_message_reply_markup_chat(Bot *bot, long int chat_id, long int message_id,
        char *inline_message_id, char *reply_markup){
    Message *message;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    message = edit_message_reply_markup(bot, cchat_id, message_id,
        inline_message_id, reply_markup);

    free(cchat_id);

    return message;
}

/**
 * deleteMessage
 * https://core.telegram.org/bots/api#deletemessage
 */
bool delete_message(Bot *bot, char *chat_id, long int message_id){
    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_deleteMessage,
        chat_id, message_id);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

bool delete_message_chat(Bot *bot, long int chat_id, long int message_id){
    bool result;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = delete_message(bot, cchat_id, message_id);

    free(cchat_id);

    return result;
}

/**
 * setChatStickerSet
 * https://core.telegram.org/bots/api#setchatstickerset
 */
bool set_chat_sticker_set(Bot *bot, char *chat_id, long int sticker_set_name){
    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_setChatStickerSet,
        chat_id, sticker_set_name);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

bool set_chat_sticker_set_chat(Bot *bot, long int chat_id, long int sticker_set_name){
    bool result;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = set_chat_sticker_set(bot, cchat_id, sticker_set_name);

    free(cchat_id);

    return result;
}

/**
 * deleteChatStickerSet
 * https://core.telegram.org/bots/api#deletechatstickerset
 */
bool delete_chat_sticker_set(Bot *bot, char *chat_id){
    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_deleteChatStickerSet, chat_id);

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}

bool delete_chat_sticker_set_chat(Bot *bot, long int chat_id){
    bool result;
    char *cchat_id;

    cchat_id = api_ltoa(chat_id);

    result = delete_chat_sticker_set(bot, cchat_id);

    free(cchat_id);

    return result;
}

/*
 * https://core.telegram.org/bots/api#answerinlinequery
 */
bool answer_inline_query( Bot *bot, char *inline_query_id, char *results, long int cache_time, bool is_personal,
    char *next_offset, char *switch_pm_text, char *switch_pm_parameter) {
    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_answerInlineQuery, inline_query_id, results,
        cache_time, is_personal, STRING_NULL(next_offset), STRING_NULL(switch_pm_text), STRING_NULL(switch_pm_parameter));

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json( s_json );

    return result;
}