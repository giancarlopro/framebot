#ifndef TELEBOT_H
#define TELEBOT_H

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

/* clear windows */
#define CSCREEN "\e[1;1H\e[2J"

/* color */
#define CBLACK    "\033[22;30m" /* black */
#define CRED      "\033[22;31m" /* red */
#define CGREEN    "\033[22;32m" /* green */
#define CBROWN    "\033[22;33m" /* brown */
#define CBLUE     "\033[22;34m" /* blue */
#define CMAGENTA  "\033[22;35m" /* magenta */
#define CCYAN     "\033[22;36m" /* cyan */
#define CGRAY     "\033[22;37m" /* gray */
#define CDGRAY    "\033[01;30m" /* dark gray */
#define CLRED     "\033[01;31m" /* light red */
#define CLGREEN   "\033[01;32m" /* light green */
#define CYELLOW   "\033[01;33m" /* yellow */
#define CLBLUE    "\033[01;34m" /* light blue */
#define CLMAGENTA "\033[01;35m" /* light magenta */
#define CLCYAN    "\033[01;36m" /* light cyan */
#define CWHITE    "\033[01;37m" /* white */
#define CRESET    "\e[0;37m"    /* default */

/* type bool */
typedef int bool;
#define true  1
#define false 0

/* parameter parse_mode */
#define MODEHTML "HTML"
#define MODEMARKDOWN "MARKDOWN"

#include <curl/curl.h>
#include <jansson.h>
#include <pthread.h>

#include <memory.h>
#include <objects.h>
#include <network.h>
#include <json.h>
#include <format.h>
#include <util.h>


void telebot_init();
Bot * telebot(const char *token);
User * get_me(const char *token);
Update *get_updates(Bot *bot, char *extra);
int to_process_message(Bot *bot, Message *message);
char *comands_bot(const char *text);

Message * send_message_channel (Bot *bot, char * chat_id, char *text, char * parse_mode,
            bool disable_web_page_preview, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);
Message * send_message_chat (Bot *bot, long int chat_id, char *text, char * parse_mode,
            bool disable_web_page_preview, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);

void to_message(Bot *bot, Update *update);

int set_chat_title_channel (Bot *bot, char *chat_id, char *title);
int set_chat_title_chat (Bot *bot, long int chat_id, char *title);

Chat *get_chat_channel(Bot *bot, char *chat_id);
Chat *get_chat_chat(Bot *bot, long int chat_id);

ChatMember *get_chat_member_channel(Bot *bot, char *chat_id, long int user_id);
ChatMember *get_chat_member_chat(Bot *bot, long int chat_id, long int user_id);

json_t *generic_method_call (const char *token, char *formats, ...);
char * get_file(Bot * bot, char * dir, const char * file_id);

bool set_chat_description_channel (Bot *bot, char *chat_id, char *description);
bool set_chat_description_chat (Bot *bot, long int chat_id, char *description);

int get_chat_members_count_channel (Bot *bot, char *chat_id);
int get_chat_members_count_chat (Bot *bot, long int chat_id);

bool kick_chat_member_channel (Bot *bot, char *chat_id, long int user_id, char *until_date);
bool kick_chat_member_chat (Bot *bot, long int chat_id, long int user_id, char *until_date);

bool restrict_chat_member_channel (Bot *bot, char *chat_id, long int user_id,
        long int until_date, bool can_send_messages,
        bool can_send_media_messages, bool can_send_other_messages,
        bool can_add_web_page_previews);
bool restrict_chat_member_chat (Bot *bot, long int chat_id, long int user_id,
        long int until_date, bool can_send_messages,
        bool can_send_media_messages, bool can_send_other_messages,
        bool can_add_web_page_previews);


bool unban_chat_member_channel (Bot *bot, char *chat_id, long int user_id);
bool unban_chat_member_chat (Bot *bot, long int chat_id, long int user_id);

bool leave_chat_channel (Bot *bot, char *chat_id);
bool leave_chat_chat (Bot *bot, long int chat_id);

bool promote_chat_member_channel (Bot *bot, char *chat_id, long int user_id, bool can_change_info,
        bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
        bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
        bool can_promote_members);
bool promote_chat_member_chat (Bot *bot, long int chat_id, long int user_id, bool can_change_info,
        bool can_post_messages, bool can_edit_messages, bool can_delete_messages,
        bool can_invite_users, bool can_restrict_members, bool can_pin_messages,
        bool can_promote_members);

char *export_chat_invite_link_channel (Bot *bot, char *chat_id);
char *export_chat_invite_link_chat (Bot *bot, long int chat_id);

UserProfilePhotos * get_user_profile_photos(Bot * bot, char * dir, long user_id, long offset, long limit);

/* send photo */
Message * send_photo_channel(Bot * bot, char * chat_id, char * filename, char * caption, 
        bool disable_notification, long int reply_to_message_id, char * reply_markup);
Message * send_photo_chat(Bot * bot, long int chat_id, char * filename, char * caption, 
        bool disable_notification, long int reply_to_message_id, char * reply_markup);

/* send audio */
Message * send_audio_channel(Bot *bot, char * chat_id, char * filename, char * caption, long int duration,
        char * performer, char * title, bool disable_notification, long int reply_to_message_id,
        char * reply_markup);
Message * send_audio_chat(Bot * bot, long int chat_id, char * filename, char * caption, long int duration,
        char * performer, char * title, bool disable_notification, long int reply_to_message_id,
        char * reply_markup);

/* send document */
Message * send_document_channel(Bot * bot, char * chat_id, char * filename, char * caption,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);
Message * send_document_chat(Bot * bot, long int chat_id, char * filename, char * caption,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);

/* send video */
Message * send_video_channel(Bot * bot, char * chat_id, char * video, long int duration, long int width,
        long int height, char * caption, bool disable_notification, long int reply_to_message_id,
         char * reply_markup);
Message * send_video_chat(Bot * bot, long int chat_id, char * video, long int duration, long int width,
        long int height, char * caption, bool disable_notification, long int reply_to_message_id,
         char * reply_markup);

/* send voice */
Message * send_voice_channel(Bot *bot, char * chat_id, char * filename, char * caption, long int duration,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);
Message * send_voice_chat(Bot *bot, long int chat_id, char * filename, char * caption, long int duration,
        bool disable_notification, long int reply_to_message_id,  char * reply_markup);

Message * send_video_note_channel(Bot * bot, char * chat_id, char * filename, long int duration,
        long int length, bool disable_notification, long int reply_to_message_id,  char * reply_markup);

Message * send_video_note_chat(Bot * bot, long int chat_id, char * filename,
        long int duration, long int length, bool disable_notification, long int reply_to_message_id,
        char * reply_markup);

Error * show_error();

Message * forward_message_from_channel (Bot * bot, long int chat_id, char * from_chat_id,
        bool disable_notification, long int message_id);
Message * forward_message_from_chat (Bot * bot, char * chat_id, long int from_chat_id,
        bool disable_notification, long int message_id);
Message * forward_message_channel (Bot * bot, char * chat_id, char * from_chat_id,
        bool disable_notification, long int message_id);
Message * forward_message_chat (Bot * bot, long int chat_id, long int from_chat_id,
        bool disable_notification, long int message_id);

Message * send_location_channel (Bot * bot, char * chat_id, float latitude,
            float longitude, long int live_period, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);
Message * send_location_chat (Bot * bot, long int chat_id, float latitude, float logitude,
            long int live_period, bool disable_notification, long int reply_to_message_id,
            char * reply_markup);

Message * send_contact_channel(Bot * bot, char * chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id,
            char * reply_markup);
Message * send_contact_chat(Bot * bot, long int chat_id, char * phone_number, char * first_name,
            char * last_name, bool disable_notification, long int reply_to_message_id,
            char * reply_markup);

int send_chat_action_channel(Bot * bot, char * chat_id, char * action);
int send_chat_action_chat(Bot * bot, long int chat_id, char * action);

Message * send_venue_channel(Bot * bot, char * chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);
Message * send_venue_chat(Bot * bot, long int chat_id, float latitude, float longitude,
            char * title, char * address, char * foursquare_id, bool disable_notification,
            long int reply_to_message_id, char * reply_markup);

Message * edit_message_live_location_channel(Bot * bot, char * chat_id, long int message_id,
            char * inline_message_id, float latitude, float longitude, char * reply_markup);
Message * edit_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,
            char * inline_message_id, float latitude, float longitude, char * reply_markup);

#endif
