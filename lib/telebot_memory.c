#include <telebot_memory.h>

char * telebot_memory_alloc_string(char * str){
    if(str != NULL){
        char * nstr = (char *)malloc(strlen(str) + 1);
        strcpy(nstr,str);
        return (char *)nstr;
    }
    return (char *)NULL;
}
