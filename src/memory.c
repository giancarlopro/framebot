#include <framebot/memory.h>

char * alloc_string(const char * str){

    if (str) {
        char *nstr = (char *) malloc(fstrlen(str) + 1);
        strcpy(nstr, str);

        return nstr;
    }

    return NULL;
}

char *realloc_string (char *base, char *str) {
    if (!str)
        return base;
    
    char *tmp = (char *) realloc(base, fstrlen(base) + fstrlen(str) + 1);

    if (tmp)
        strcat(tmp, str);

    return tmp;
}