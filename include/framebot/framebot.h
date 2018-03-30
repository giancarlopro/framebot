#ifndef FRAMEBOT_H
#define FRAMEBOT_H

/* Functions API */

#define API_GETME "getMe"

#define API_GETUPDATES "getUpdates\
?offset=%ld\
&limit=%ld\
&timeout=%ld\
&allowed_updates=%s"

#define API_SENDMESSAGE "sendMessage\
?chat_id=%s\
&text=%s\
&parse_mode=%s\
&disable_web_page_preview=%s\
&disable_notification=%s\
&reply_to_message_id=%ld\
&reply_markup=%s"

#define API_getChat "getChat\
?chat_id=%s"

#define API_setChatTitle "setChatTitle\
?chat_id=%s\
&title=%s"

#define API_getChatMember "getChatMember\
?chat_id=%s\
&user_id=%ld"

#define API_setChatDescription "setChatDescription\
?chat_id=%s\
&description=%s"

#define API_getChatMemberCount "getChatMemberCount\
?chat_id=%s"

#define API_kickChatMember "kickChatMember\
?chat_id=%s\
&user_id=%ld\
&until_date=%s"

#define API_restrictChatMember "restrictChatMember\
?chat_id=%s\
&user_id=%ld\
&until_date=%ld\
&can_send_messages=%s\
&can_send_media_messages=%s\
&can_send_other_messages=%s\
&can_add_web_page_previews=%s"

#define API_unbanChatMember "unbanChatMember\
?chat_id=%s\
&user_id=%ld"

#define API_leaveChat "leaveChat\
?chat_id=%s"

#define API_promoteChatMember "promoteChatMember\
?chat_id=%s\
&user_id=%ld\
&can_change_info=%s\
&can_post_messages=%s\
&can_edit_messages=%s\
&can_delete_messages=%s\
&can_invite_users=%s\
&can_restrict_members=%s\
&can_pin_messages=%s\
&can_promote_members=%s"

#define API_exportChatInviteLink "exportChatInviteLink"

#define API_deleteChatPhoto "deleteChatPhoto\
?chat_id=%s"

#define API_getChatAdministrators "getChatAdministrators\
?chat_id=%s"

#define API_pinChatMessage "pinChatMessage\
?chat_id=%s\
&message_id=%ld\
&disable_notification=%s"

#define API_unpinChatMessage "unpinChatMessage\
?chat_id=%s"

#define API_getfile "getfile\
?file_id=%s"

#define API_getUserProfilePhotos "getUserProfilePhotos\
?user_id=%s\
&offset=%ld\
&limit=%ld"

#define API_forwardMessage "forwardMessage\
?chat_id=%s\
&from_chat_id=%s\
&disable_notification=%s\
&message_id=%ld"

#define API_sendLocation "sendLocation\
?chat_id=%s\
&latitude=%f\
&longitude=%f\
&live_period=%ld\
&disable_notification=%s\
&reply_to_message_id=%ld\
&reply_markup=%s"

#define API_sendContact "sendContact\
?chat_id=%s\
&phone_number=%s\
&first_name=%s\
&last_name=%s\
&disable_notification=%s\
&reply_to_message_id=%ld\
&reply_markup=%s"

#define API_sendChatAction "sendChatAction\
?chat_id=%s\
&action=%s"

#define API_sendVenue "sendVenue\
?chat_id=%s\
&latitude=%f\
&longitude=%f\
&title=%s\
&address=%s\
&foursquare_id=%s\
&disable_notification=%s\
&reply_to_message_id=%ld\
&reply_markup=%s"

#define API_editMessageLiveLocation "editMessageLiveLocation\
?chat_id=%s\
&message_id=%ld\
&inline_message_id=%s\
&latitude=%f\
&longitude=%f\
&reply_markup=%s"

#define API_stopMessageLiveLocation "stopMessageLiveLocation\
?chat_id=%s\
&message_id=%ld\
&inline_message_id=%s\
&reply_markup=%s"

#define API_editMessageText "editMessageText\
?chat_id=%s\
&message_id=%ld\
&inline_message_id=%s\
&text=%s\
&parse_mode=%s\
&disable_web_page_preview=%d\
&reply_markup=%s"

#define API_editMessageCaption "editMessageCaption\
?chat_id=%s\
&message_id=%ld\
&inline_message_id=%s\
&caption=%s\
&reply_markup=%s"

#define API_editMessageReplyMarkup "editMessageReplyMarkup\
?chat_id=%s\
&message_id=%ld\
&inline_message_id=%s\
&reply_markup=%s"

#define API_deleteMessage "deleteMessage\
?chat_id=%s\
&message_id=%ld"

#define API_setChatStickerSet "setChatStickerSet\
?chat_id=%s\
&sticker_set_name=%s"

#define API_deleteChatStickerSet "deleteChatStickerSet\
?chat_id=%s"

#define API_answerInlineQuery "answerInlineQuery\
?inline_query_id=%s\
&results=%s\
&cache_time=%ld\
&is_personal=%d\
&next_offset=%s\
&switch_pm_text=%s\
&switch_pm_parameter=%s"

/* analyze parameter API methods */
#define PARSE_MODE(p) (p == NULL ? "" : p) 
#define DISABLE_WEB_PAGE_PREVIEW(p) (p > 0 ? "true" : "0")
#define DISABLE_NOTIFICATION(p) (p > 0 ? "true" : "0")
#define REPLY_MARKUP(p) (p == NULL ? "" : p)

#define CAN_SEND_MESSAGES(p) (p > 0 ? "true" : "0")
#define CAN_SEND_MEDIA_MESSAGES(p) (p > 0 ? "true" : "0")
#define CAN_SEND_OTHER_MESSAGES(p) (p > 0 ? "true" : "0")
#define CAN_ADD_WEB_PAGE_PREVIEWS(p) (p > 0 ? "true" : "0")

#define CAN_CHANGE_INFO(p) (p > 0 ? "true" : "0")
#define CAN_POST_MESSAGES(p) (p > 0 ? "true": "0")
#define CAN_EDIT_MESSAGES(p) (p > 0 ? "true" : "0")
#define CAN_DELETE_MESSAGES(p) (p > 0 ? "true" : "0")
#define CAN_INVITE_USERS(p) (p > 0 ? "true": "0")
#define CAN_RESTRICT_MEMBERS(p) (p > 0 ? "true" : "0")
#define CAN_PIN_MESSAGES(p) (p > 0 ? "true" : "0")
#define CAN_PROMOTE_MEMBERS(p) (p > 0 ? "true" : "0")

#define DURATION(p) (p > 0 ? api_ltoa(p) : NULL)
#define REPLY_TO_MESSAGE_ID(p) (p > 0 ? api_ltoa(p) : NULL)
#define WIDTH(p) (p > 0 ? api_ltoa(p) : NULL)
#define HEIGHT(p) (p > 0 ? api_ltoa(p) : NULL)
#define LENGTH(p) (p > 0 ? api_ltoa(p) : NULL)

#define IF_STRING_NULL(p) (p == NULL?"null":p)

#define UPDATE_ID_LAST(x, y) (x->update_id > y->update_id ? x->update_id : y->update_id)

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <errno.h>


#ifdef __linux__
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#elif _WIN32
#include <Windows.h>
#include <io.h>
#else
# error "Only windows or Linux"
#endif

#include <limits.h>
#include <ctype.h>

#ifdef _MSC_VER
//cURL Fix
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#define CURL_STATICLIB
// --//--
#endif

/* type bool */
typedef int bool;
#define true  1
#define false 0

/* parameter parse_mode */
#define MODE_HTML "HTML"
#define MODE_MARKDOWN "Markdown"

#include <curl/curl.h>
#include <jansson.h>
#include <pthread.h>

#include <framebot/memory.h>
#include <framebot/objects.h>
#include <framebot/network.h>
#include <framebot/json.h>
#include <framebot/format.h>
#include <framebot/util.h>


void framebot_init();
Bot * framebot(const char *token);
refjson *generic_method_call (const char *token, char *formats, ...);
Error * show_error();

/** Available methods **/
User * get_me(const char *token);
Framebot *get_updates (Bot *bot, Framebot *framebot, long int offset, long int limit,
            long int timeout, char *allowed_updates);

/* sendMessage */
Message * send_message (Bot *bot, char * chat_id, char *text, char * parse_mode,
            bool disable_web_page_preview, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);
Message * send_message_chat (Bot *bot, long int chat_id, char *text, char * parse_mode,
            bool disable_web_page_preview, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);

/* ForwardMessage */
Message * forward_message_from (Bot * bot, long int chat_id, char * from_chat_id,
        bool disable_notification, long int message_id);
Message * forward_message_from_chat (Bot * bot, char * chat_id, long int from_chat_id,
        bool disable_notification, long int message_id);
Message * forward_message (Bot * bot, char * chat_id, char * from_chat_id,
        bool disable_notification, long int message_id);
Message * forward_message_chat (Bot * bot, long int chat_id, long int from_chat_id,
        bool disable_notification, long int message_id);

/* sendphoto */
Message * send_photo(Bot * bot, char * chat_id, char * filename, char * caption,
        bool disable_notification, long int reply_to_message_id, char * reply_markup);
Message * send_photo_chat(Bot * bot, long int chat_id, char * filename, char * caption, 
        bool disable_notification, long int reply_to_message_id, char * reply_markup);

/* sendaudio */
Message * send_audio(Bot *bot, char * chat_id, char * filename, char * caption, long int duration,
        char * performer, char * title, bool disable_notification, long int reply_to_message_id,
        char * reply_markup);
Message * send_audio_chat(Bot * bot, long int chat_id, char * filename, char * caption, long int duration,
        char * performer, char * title, bool disable_notification, long int reply_to_message_id,
        char * reply_markup);

/* senddocument */
Message * send_document(Bot * bot, char * chat_id, char * filename, char * caption,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);
Message * send_document_chat(Bot * bot, long int chat_id, char * filename, char * caption,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);

/* sendvideo */
Message * send_video(Bot * bot, char * chat_id, char * video, long int duration, long int width,
        long int height, char * caption, bool disable_notification, long int reply_to_message_id,
         char * reply_markup);
Message * send_video_chat(Bot * bot, long int chat_id, char * video, long int duration, long int width,
        long int height, char * caption, bool disable_notification, long int reply_to_message_id,
         char * reply_markup);

/* sendvoice */
Message * send_voice(Bot *bot, char * chat_id, char * filename, char * caption, long int duration,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);
Message * send_voice_chat(Bot *bot, long int chat_id, char * filename, char * caption, long int duration,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);

Message * send_video_note(Bot * bot, char * chat_id, char * filename, long int duration,
        long int length, bool disable_notification, long int reply_to_message_id,  char * reply_markup);

Message * send_video_note_chat(Bot * bot, long int chat_id, char * filename,
        long int duration, long int length, bool disable_notification, long int reply_to_message_id,
        char * reply_markup);

// sendMediaGroup

/* sendlocation */
Message * send_location (Bot * bot, char * chat_id, float latitude,
            float longitude, long int live_period, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);
Message * send_location_chat (Bot * bot, long int chat_id, float latitude, float logitude,
            long int live_period, bool disable_notification, long int reply_to_message_id,
            char * reply_markup);

/* editMessageLiveLocation */
Message * edit_message_live_location(Bot * bot, char * chat_id, long int message_id,
        char * inline_message_id, float latitude, float longitude, char * reply_markup);
Message * edit_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,
        char * inline_message_id, float latitude, float longitude, char * reply_markup);

/* stopMessageLiveLocation */
Message * stop_message_live_location(Bot * bot, char * chat_id, long int message_id,
            char * inline_message_id, char * reply_markup);
Message * stop_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,
            char * inline_message_id, char * reply_markup);

/* sendVenue */
Message * send_venue(Bot * bot, char * chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);
Message * send_venue_chat(Bot * bot, long int chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);

/* sendContact */
Message * send_contact(Bot * bot, char * chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id,
            char * reply_markup);
Message * send_contact_chat(Bot * bot, long int chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id,
            char * reply_markup);

/* sendChatAction */
int send_chat_action(Bot * bot, char * chat_id, char * action);
int send_chat_action_chat(Bot * bot, long int chat_id, char * action);

/* getUserProfilePhotos */
UserProfilePhotos * get_user_profile_photos(Bot * bot, char * dir, char *user_id,
    long offset, long limit);
UserProfilePhotos * get_user_profile_photos_chat(Bot * bot, char * dir, long user_id,
    long offset, long limit);

/* getFile */
File * get_file(Bot * bot, const char * file_id);
int file_download(Bot * bot, File * ofile, char *path);

/* kickChatMember */
bool kick_chat_member (Bot *bot, char *chat_id, long int user_id, char *until_date);
bool kick_chat_member_chat (Bot *bot, long int chat_id, long int user_id, char *until_date);

/* unbanChatMember */
bool unban_chat_member (Bot *bot, char *chat_id, long int user_id);
bool unban_chat_member_chat (Bot *bot, long int chat_id, long int user_id);

/* restrictChatMember */
bool restrict_chat_member (Bot *bot, char *chat_id, long int user_id,
        long int until_date, bool can_send_messages,
        bool can_send_media_messages, bool can_send_other_messages,
        bool can_add_web_page_previews);
bool restrict_chat_member_chat (Bot *bot, long int chat_id, long int user_id,
        long int until_date, bool can_send_messages,
        bool can_send_media_messages, bool can_send_other_messages,
        bool can_add_web_page_previews);

/* promoteChatMember */
bool promote_chat_member (Bot *bot, char *chat_id, long int user_id, bool can_change_info,
        bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
        bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
        bool can_promote_members);
bool promote_chat_member_chat (Bot *bot, long int chat_id, long int user_id, bool can_change_info,
        bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
        bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
        bool can_promote_members);

/* exportChatInviteLink */
char *export_chat_invite_link (Bot *bot, char *chat_id);
char *export_chat_invite_link_chat (Bot *bot, long int chat_id);

/* setChatPhoto */
int set_chat_photo(Bot *bot, char * chat_id, char *filename);
int set_chat_photo_chat(Bot *bot, long int chat_id, char *filename);

/* deleteChatPhoto */
int delete_chat_photo(Bot *bot, char *chat_id);
int delete_chat_photo_chat(Bot *bot, long int chat_id);

/* setChatTitle */
int set_chat_title (Bot *bot, char *chat_id, char *title);
int set_chat_title_chat (Bot *bot, long int chat_id, char *title);

/* setChatDescription */
bool set_chat_description (Bot *bot, char *chat_id, char *description);
bool set_chat_description_chat (Bot *bot, long int chat_id, char *description);

/* pinChatMessage */
bool pin_chat_message (Bot *bot, char *chat_id, long int message_id, bool disable_notification);
bool pin_chat_message_chat(Bot *bot, long int chat_id, long int message_id, bool disable_notification);

/* unpinChatMessage */
bool unpin_chat_message(Bot *bot, char *chat_id);
bool unpin_chat_message_chat(Bot *bot, long int chat_id);

/* leaveChat */
bool leave_chat (Bot *bot, char *chat_id);
bool leave_chat_chat (Bot *bot, long int chat_id);

/* getChat */
Chat *get_chat(Bot *bot, char *chat_id);
Chat *get_chat_chat(Bot *bot, long int chat_id);

/* getChatAdministrators */
ChatMember *get_chat_administrators (Bot *bot, char *chat_id);
ChatMember *get_chat_administrators_chat(Bot *bot, long int chat_id);

/* getChatMembersCount */
int get_chat_members_count (Bot *bot, char *chat_id);
int get_chat_members_count_chat (Bot *bot, long int chat_id);

/* getChatMember */
ChatMember *get_chat_member(Bot *bot, char *chat_id, long int user_id);
ChatMember *get_chat_member_chat(Bot *bot, long int chat_id, long int user_id);

/** Updating messages **/
Message *edit_message_text(Bot *bot, char *chat_id, long int message_id,
    char *inline_message_id, char *text, char *parse_mode,
    bool disable_web_page_preview, char *reply_markup);
Message *edit_message_text_chat(Bot *bot, long int chat_id, long int message_id,
    char *inline_message_id, char *text, char *parse_mode,
    bool disable_web_page_preview, char *reply_markup);

/* editMessageText */
Message *edit_message_caption(Bot *bot, char *chat_id,
    long int message_id, char *inline_message_id, char *caption,
    char *reply_markup);
Message *edit_message_caption_chat(Bot *bot, long int chat_id,
    long int message_id, char *inline_message_id, char *caption,
    char *reply_markup);

/* editMessageCaption */
Message *edit_message_reply_markup(Bot *bot, char *chat_id, long int message_id,
        char *inline_message_id, char *reply_markup);
Message *edit_message_reply_markup_chat(Bot *bot, long int chat_id, long int message_id,
        char *inline_message_id, char *reply_markup);

bool answer_inline_query( Bot *bot, char *inline_query_id, char *results, long int cache_time, bool is_personal,
    char *next_offset, char *switch_pm_text, char *switch_pm_parameter);

#endif
