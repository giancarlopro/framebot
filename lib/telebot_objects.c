#include <telebot.h>
#include <telebot_objects.h>

User * telebot_user(long int id,char * first_name,char * last_name,char * username){

    User * _usr = (User *) malloc(sizeof(User));

    _usr->id = id;

    _usr->first_name = (char *)malloc(strlen(first_name) + 1);
    strcpy(_usr->first_name,first_name);

    if(last_name == NULL){
        _usr->last_name = NULL;
    }else{
        _usr->last_name = (char *)malloc(strlen(last_name) + 1);
        strcpy(_usr->last_name,last_name);
    }

    if(username == NULL){
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

Bot * telebot_bot(char * token){
    Bot * bot = (Bot *)malloc(sizeof(Bot));
    strcpy(bot->token,token);

    //Call getMe function ...
    User * usr = NULL;

    bot->user = usr;
    return bot;
}
void telebot_bot_free(Bot * bot){
    free(bot->token);
    telebot_user_free(bot->user);
    free(bot);
}

Chat * telebot_chat(long int id,char * type,char * title,char * username,char * first_name,char * last_name,int all_members_are_administrators){
    Chat * _cht = (Chat *) malloc(sizeof(Chat));

    _cht->id = id;
    _cht->all_members_are_administrators = all_members_are_administrators;

    _cht->type = (char *) malloc(strlen(type) + 1);
    strcpy(_cht->type,type);

    if(title != NULL){
        _cht->title = (char *) malloc(strlen(title) + 1);
        strcpy(_cht->title,title);
    }else{
        _cht->title = NULL;
    }

    if(username != NULL){
        _cht->username = (char *) malloc(strlen(username) + 1);
        strcpy(_cht->username,username);
    }else{
        _cht->username = NULL;
    }

    if(first_name != NULL){
        _cht->first_name = (char *) malloc(strlen(first_name) + 1);
        strcpy(_cht->first_name,first_name);
    }else{
        _cht->first_name = NULL;
    }

    if(last_name != NULL){
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

MessageEntity * telebot_message_entity(char * type,long int offset,long int length,char * url,User * user){
    MessageEntity * msgett = (MessageEntity *)malloc(sizeof(MessageEntity));

    msgett->offset = offset;
    msgett->length = length;
    msgett->user = user;

    if(type == NULL){
        msgett->type = NULL;
    }else{
        msgett->type = (char *)malloc(strlen(type) + 1);
        strcpy(msgett->type,type);
    }

    if(url == NULL){
        msgett->url = NULL;
    }else{
        msgett->url = (char *)malloc(strlen(url) + 1);
        strcpy(msgett->url,url);
    }

    return msgett;
}
void telebot_message_entity_free(MessageEntity * msgett){
    free(msgett->type);
    free(msgett->url);
    telebot_user_free(msgett->user);
    free(msgett);
}