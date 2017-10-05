#include <memory.h>

char * alloc_string(const char * str){

    if(str != NULL){
        char * nstr = (char *)malloc(strlen(str) + 1);
        strcpy(nstr,str);

        return (char *)nstr;
    }

    return (char *)NULL;
}
