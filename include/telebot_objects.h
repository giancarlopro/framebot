#ifndef TELEBOT_OBJECTS_H_
#define TELEBOT_OBJECTS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _user{
    long int id;
    char * first_name;
    char * last_name;
    char * username;
} User;

typedef struct _chat{
    long int id;
    char * type;
    char * title;
    char * username;
    char * first_name;
    char * last_name;
    int all_members_are_administrators;
}Chat;

typedef struct _message_entity{
    char * type;
    long int offset;
    long int length;
    char * url;
    User user;
} MessageEntity;

typedef struct _message{
    long int message_id;
    User from;
    long int date;
    Chat chat;
    User forward_from;
    Chat forward_from_chat;
    long int forward_from_message_id;
    long int forward_date;
    void * reply_to_message;
    long int edit_date;
    char * text;
    MessageEntity ** entities;
}Message;

User * newUser(long int id,char * first_name,char * last_name,char * username);
void freeUser(User * usr);

Chat * newChat(long int id,char * type,char * title,char * username,char * first_name,char * last_name,int all_members_are_administrators);
void freeChat(Chat * cht);
#endif // TELEBOT_OBJECTS_H_
