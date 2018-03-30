#ifndef UTIL_H
#define UTIL_H

#include <framebot/framebot.h>

char * file_extension_download(char *tgname, char *namefile);
char * vsboolean_param_parser (char *base, int psize, ...);
char * api_ltoa(long int n);
char * api_itoa(int n);
int api_atoi(char * str_int);
long int api_atol(char * str_long);

#endif
