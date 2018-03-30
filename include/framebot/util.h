#ifndef UTIL_H
#define UTIL_H

#include <framebot/framebot.h>

int api_tg_exist(const char *filename);
char * file_extension_download(char *tgname, char *namefile);
char * api_ltoa(long int n);
char * api_itoa(int n);
int api_atoi(char * str_int);
long int api_atol(char * str_long);

#endif
