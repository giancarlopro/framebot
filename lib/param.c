#include <telebot.h>

Param *param(char *base){
    Param *pparam = (Param *)malloc(sizeof(Param));
    pparam->data = (char *)malloc(strlen(base) + 1);
    strcpy(pparam->data,base);

    pparam->length = strlen(pparam->data);
    pparam->param_size = 0;
    pparam->last_encoded = NULL;

    return pparam;
}
void param_add(Param *p, char *key, char *value){
    size_t new_size = strlen(key) + strlen(value) + 3;
    p->data = (char *)realloc(p->data,new_size);

    if(p->param_size == 0){
        strcat(p->data,"?");
    }else{
        strcat(p->data,"&");
    }

    strcat(p->data,key);
    strcat(p->data,"=");
    strcat(p->data,value);

    p->length = strlen(p->data);
    p->param_size += 1;
}
char *param_parse(Param *p){
    CURL *curl = curl_easy_init();
    if(curl){
        char *encoded = curl_easy_escape(curl, p->data, p->length);
        if(encoded)
            if(p->last_encoded)
                curl_free(p->last_encoded);
            p->last_encoded = encoded;
            return encoded;
    }
    return NULL;
}
void param_free(Param *p){
    if(p->data)
        free(p->data);
    if(p->last_encoded)
        curl_free(p->last_encoded);
    free(p);
}
