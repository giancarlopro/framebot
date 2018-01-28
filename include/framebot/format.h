#ifndef FORMAT_H
#define FORMAT_H

#include <framebot/framebot.h>

char *format(char *format, ...);
char *vsformat (char *formats, va_list params);
char *remove_newline(char *str);

#endif