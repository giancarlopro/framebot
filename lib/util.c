#include <util.h>

// format = (char *param_alias), (bool param), (char *param_alias), (bool param), ...
char *vsboolean_param_parser (char *base, int psize, ...) {
    va_list params;
    va_start(params, psize);
    
    int i;

    char *alias, *tmp, *base_tmp = base;
    bool param;

    for (i = 0; i < psize; i++) {
        alias = va_arg(params, char*);
        param = va_arg(params, bool);

        if (param) {
            tmp = format("&%s=True", alias);
        } else {
            tmp = format("&%s=False", alias);
        }

        base_tmp = realloc_string(base_tmp, tmp);
        free(tmp);
    }

    return base_tmp;
}

char * api_ltoa(long int n){
    int len;
    char * str;

    len = sprintf(NULL, "%ld", n);
    str = malloc((size_t)len + 1);

    snprintf(str, (size_t)len + 1, "%lu", n);

    return str;
}

char * api_itoa(int n){
    int len;
    char * str;

    len = sprintf(NULL, "%d", n);
    str = malloc((size_t)len + 1);

    snprintf(str, (size_t)len + 1, "%d", n);

    return str;
}

int api_atoi(char * str_int){
    return atoi(str_int);
}

long int api_atol(char * str_long){
    return atol(str_long);
}
