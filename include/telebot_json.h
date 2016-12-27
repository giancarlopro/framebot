#ifndef TELEBOT_JSON_H
#define TELEBOT_JSON_H

#include <telebot_objects.h>
#include <jansson.h>

User * telebot_json_user(char * json);

#endif