#ifndef MEMORY_H
#define MEMORY_H

#include <telebot.h>

char *alloc_string(const char * str);
char *realloc_string(char *base, char *str);

#endif
