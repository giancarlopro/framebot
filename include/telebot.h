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
#elif _WIN32
#include <Windows.h>
#include <io.h>
#else
# error "Only windows or Linux"
#endif

#include <limits.h>
#include <ctype.h>


//cURL Fix
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#define CURL_STATICLIB
// --//--

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

#include <curl/curl.h>
#include <jansson.h>
#include <pthread.h>

#include <memory.h>
#include <objects.h>
#include <network.h>
#include <json.h>
#include <format.h>
#include <log.h>
#include <json_user.h>
#include <config.h>

void telebot_init();
Bot * telebot(const char *token);
User * get_me(const char *token);
Update *get_updates(Bot *bot, char *extra);
void handle_data(Bot *bot);
void telebot_polling(Bot *bot);
int to_process_message(Bot *bot, Message *message);
char *comands_bot(const char *text);
int send_message(Bot *bot, long int chat_id, char *text, char *extra);
void to_message(Bot *bot, Update *update);
int set_chat_title (Bot *bot, char *chat_id, char *title);
Chat *get_chat(Bot *bot, char *chat_id);
ChatMember *get_chat_member(Bot *bot, char *chat_id, char *user_id);
json_t *generic_method_call (char *token, char *formats, ...);


#endif
