#ifndef TELEBOT_OBJECTS_H
#define TELEBOT_OBJECTS_H

typedef struct _user{
    long int id;
    char * first_name;
    char * last_name;
    char * username;
} User;

typedef struct _bot{
    char * token;
    User * user;
} Bot;

typedef struct _chat{
    long int id;
    char * type;
    char * title;
    char * username;
    char * first_name;
    char * last_name;
    int all_members_are_administrators;
} Chat;

typedef struct _message_entity{
    char * type;
    long int offset;
    long int length;
    char * url;
    User * user;
} MessageEntity;

typedef struct _audio{
    char * file_id;
    long int duration;
    char * performer;
    char * title;
    char * mime_type;
    long int file_size;
} Audio;

typedef struct _photo_size{
    char * file_id;
    int width;
    int height;
    long int file_size;
} PhotoSize;

typedef struct _document{
    char * file_id;
    PhotoSize * thumb;
    char * file_name;
    char * mime_type;
    long int file_size;
} Document;

typedef struct _animation{
    char * file_id;
    PhotoSize * thumb;
    char * file_name;
    char * mime_type;
    long int file_size;
} Animation;

typedef struct _game{
    char * title;
    char * description;
    PhotoSize (*photo)[];
    char * text;
    MessageEntity (*text_entities)[];
    Animation * animation;
} Game;

typedef struct _sticker{
    char * file_id;
    int width;
    int height;
    PhotoSize * thumb;
    char * emoji;
    long int file_size;
} Sticker;

typedef struct _video{
    char * file_id;
    int width;
    int height;
    long int duration;
    PhotoSize * thumb;
    char * mime_type;
    long int file_size;
} Video;

typedef struct _voice{
    char * file_id;
    long int duration;
    char * mime_type;
    long int file_size;
} Voice;

typedef struct _contact{
    char * phone_number;
    char * first_name;
    char * last_name;
    long int user_id;
} Contact;

typedef struct _location{
    float latitude;
    float longitude;
} Location;

typedef struct _venue{
    Location * location;
    char * title;
    char * address;
    char * foursquare_id;
} Venue;

typedef struct _message{
    long int message_id;
    User * from;
    long int date;
    Chat * chat;
    User * forward_from;
    Chat * forward_from_chat;
    long int forward_from_message_id;
    long int forward_date;
    struct _message * reply_to_message;
    long int edit_date;
    char * text;
    MessageEntity (* entities)[];
    Audio * audio;
    Document * document;
    Game * game;
    PhotoSize (*photo)[];
    Sticker * sticker;
    Video * video;
    Voice * voice;
    char * caption;
    Contact * contact;
    Location * location;
    Venue * venue;
    User * new_chat_member;
    User * left_chat_member;
    char * new_chat_title;
    PhotoSize (*new_chat_photo)[];
    int delete_chat_photo;
    int group_chat_created;
    int supergroup_chat_created;
    int channel_chat_created;
    long int migrate_to_chat_id;
    long int migrate_from_chat_id;
    struct _message * pinned_message;
} Message;

typedef struct _inline_query{
    char * id;
    User * from;
    Location * location;
    char * query;
    char * offset;
} InlineQuery;

typedef struct _choosen_inline_result{
    char * result_id;
    User * from;
    Location * location;
    char * inline_message_id;
    char * query;
} ChoosenInlineResult;

typedef struct _callback_query{
    char * id;
    User * from;
    Message * message;
    char * inline_message_id;
    char * chat_instance;
    char * data;
    char * game_short_name;
} CallbackQuery;

typedef struct _update{
    long int update_id;
    Message * message;
    Message * edited_message;
    Message * channel_post;
    Message * edited_channel_post;
    InlineQuery * inline_query;
    ChoosenInlineResult * choosen_inline_result;
    CallbackQuery * callback_query;
} Update;
//User functions
User * telebot_user(long int id,char * first_name,char * last_name,char * username);
void telebot_user_free(User * usr);
//Chat functions
Chat * telebot_chat(long int id,char * type,char * title,char * username,char * first_name,char * last_name,int all_members_are_administrators);
void telebot_chat_free(Chat * cht);
//Message entity functions
MessageEntity * telebot_message_entity(char * type,long int offset,long int length,char * url,User * user);
void telebot_message_entity_free(MessageEntity * msgett);
//Audio functions
Audio * telebot_audio(char * file_id,long int duration,char * performer,char * title,char * mime_type,long int file_size);
void telebot_audio_free(Audio * audio);

Message * telebot_message(long int message_id,User * from,long int date,Chat * chat,User * forward_from,Chat * forward_from_chat,long int forward_from_message_id,long int forward_date,Message * reply_to_message,long int edit_date,char * text,MessageEntity (* entities)[],Audio * audio,Document * document,Game * game,PhotoSize (*photo)[],Sticker * sticker,Video * video,Voice * voice,char * caption,Contact * contact,Location * location,Venue * venue,User * new_chat_member,User * left_chat_member,char * new_chat_title,PhotoSize (*new_chat_photo)[],int delete_chat_photo,int group_chat_created,int supergroup_chat_created,int channel_chat_created,long int migrate_to_chat_id,long int migrate_from_chat_id,Message * pinned_message);
void telebot_message_free(Message * message);
#endif // TELEBOT_OBJECTS_H_
