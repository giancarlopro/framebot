#ifndef TELEBOT_H
#define TELEBOT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <telebot_objects.h>
#include <telebot_json.h>

Update * telebot_get_updates(Bot * bot);

#endif
