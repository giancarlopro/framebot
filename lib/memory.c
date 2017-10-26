#include <memory.h>

char * alloc_string(const char * str){

    if (str) {
        char *nstr = (char *) malloc(strlen(str) + 1);
        strcpy(nstr, str);

        return (char *) nstr;
    }

    return (char *) NULL;
}

char *realloc_string (char *base, char *str) {
    if (!str)
        return base;
    
    char *tmp = (char *) realloc(base, strlen(base) + strlen(str) + 1);

    if (tmp)
        strcat(tmp, str);

    return tmp;
}