#ifndef TELEBOT_H
#define TELEBOT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//cURL Fix
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#define CURL_STATICLIB
// --//--

#include <curl/curl.h>
#include <jansson.h>

#include <memory.h>
#include <objects.h>
#include <network.h>
#include <json.h>
#include <param.h>
#include <format.h>

void telebot_init();
Bot * telebot(char *token);
User * get_me(char *token);
Update *get_updates(Bot *bot, Param *p);

#endif
