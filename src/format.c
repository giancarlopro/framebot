#include <framebot/framebot.h>

#define MAX_URL_SZ 2000

#define STRLONG 21
#define STRINT 13 


char *vsformat (char *formats, va_list params) {
	char *buffer = (char *) calloc(1, MAX_URL_SZ);

	vsnprintf(buffer, MAX_URL_SZ, formats, params);

	return buffer;
}


char * api_ltoa(long int n){
    char * str;

    str = calloc(1, STRLONG);

    snprintf(str, STRLONG, "%ld", n);

    return str;
}

char * api_itoa(int n){
    char * str;

    str = calloc(1, STRINT);

    snprintf(str, STRINT, "%d", n);

    return str;
}

int api_atoi(char * str_int){
    return atoi(str_int);
}

long int api_atol(char * str_long){
    return atol(str_long);
}