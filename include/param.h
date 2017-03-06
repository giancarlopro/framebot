#ifndef PARAM_H
#define PARAM_H

#include <telebot.h>

typedef struct _param{
    char *data;
    char *last_encoded;
    size_t length;
    size_t param_size;
}Param;

Param *param();
void param_add(Param *p, char *key, char *value);
char *param_parse(Param *p);
void param_free(Param *p);
#endif
