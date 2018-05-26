#include <framebot/memory.h>

char * alloc_string(const char * str){

    if (str) {
        size_t sizestr = fstrlen(str) + 1;
        char *nstr = (char *) calloc(1, sizestr);
        if(!nstr)
            return NULL;

        scpy(nstr, str, sizestr);

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