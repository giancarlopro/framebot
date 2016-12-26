#include <telebot.h>
#include <telebot_objects.h>

User * telebot_user(long int id,char * first_name,char * last_name,char * username){

    User * _usr = (User *) malloc(sizeof(User));

    _usr->id = id;

    _usr->first_name = (char *)malloc(strlen(first_name) + 1);
    strcpy(_usr->first_name,first_name);

    if(strcmp(last_name,"None") == 0){
        _usr->last_name = NULL;
    }else{
        _usr->last_name = (char *)malloc(strlen(last_name) + 1);
        strcpy(_usr->last_name,last_name);
    }

    if(strcmp(username,"None") == 0){
        _usr->username = NULL;
    }else{
        _usr->username = (char *)malloc(strlen(username) + 1);
        strcpy(_usr->username,username);
    }

    return _usr;
}
void telebot_user_free(User * usr){
    free(usr->first_name);
    free(usr->last_name);
    free(usr->username);
    free(usr);
}

Chat * telebot_chat(long int id,char * type,char * title,char * username,char * first_name,char * last_name,int all_members_are_administrators){
    Chat * _cht = (Chat *) malloc(sizeof(Chat));

    _cht->id = id;
    _cht->all_members_are_administrators = all_members_are_administrators;

    _cht->type = (char *) malloc(strlen(type) + 1);
    strcpy(_cht->type,type);

    if(strcmp(title,"None") == 0){
        _cht->title = (char *) malloc(strlen(title) + 1);
        strcpy(_cht->title,title);
    }else{
        _cht->title = NULL;
    }

    if(strcmp(username,"None") == 0){
        _cht->username = (char *) malloc(strlen(username) + 1);
        strcpy(_cht->username,username);
    }else{
        _cht->username = NULL;
    }

    if(strcmp(first_name,"None") == 0){
        _cht->first_name = (char *) malloc(strlen(first_name) + 1);
        strcpy(_cht->first_name,first_name);
    }else{
        _cht->first_name = NULL;
    }

    if(strcmp(last_name,"None") == 0){
        _cht->last_name = (char *) malloc(strlen(last_name) + 1);
        strcpy(_cht->last_name,last_name);
    }else{
        _cht->last_name = NULL;
    }

    return _cht;
}
void telebot_chat_free(Chat * cht){
    free(cht->type);
    free(cht->title);
    free(cht->username);
    free(cht->first_name);
    free(cht->last_name);
    free(cht);
}
