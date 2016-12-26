#ifndef TELEBOT_OBJECTS_H
#define TELEBOT_OBJECTS_H

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
    struct _message * reply_to_message;
    long int edit_date;
    char * text;
    MessageEntity (* entities)[];
}Message;

User * telebot_user(long int id,char * first_name,char * last_name,char * username);
void telebot_user_free(User * usr);

Chat * telebot_chat(long int id,char * type,char * title,char * username,char * first_name,char * last_name,int all_members_are_administrators);
void telebot_chat_free(Chat * cht);
#endif // TELEBOT_OBJECTS_H_
