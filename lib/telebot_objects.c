#include <telebot.h>
#include <telebot_objects.h>

User * telebot_user(long int id,const char * first_name,const char * last_name,const char * username){
    User * user = (User *) malloc(sizeof(User));

    user->id = id;
    user->first_name = telebot_memory_alloc_string(first_name);
    user->last_name = telebot_memory_alloc_string(last_name);
    user->username = telebot_memory_alloc_string(username);

    return user;
}
void telebot_user_free(User * usr){
    free(usr->first_name);
    free(usr->last_name);
    free(usr->username);
    free(usr);
}

Bot * telebot_bot(char * token){
    Bot * bot = (Bot *)malloc(sizeof(Bot));

    bot->token = telebot_memory_alloc_string(token);

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
    Chat * chat = (Chat *) malloc(sizeof(Chat));

    chat->id = id;
    chat->all_members_are_administrators = all_members_are_administrators;

    chat->type = telebot_memory_alloc_string(type);
    chat->title = telebot_memory_alloc_string(title);
    chat->username = telebot_memory_alloc_string(username);
    chat->first_name = telebot_memory_alloc_string(first_name);
    chat->last_name = telebot_memory_alloc_string(last_name);

    return chat;
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

    msgett->type = telebot_memory_alloc_string(type);
    msgett->url = telebot_memory_alloc_string(url);

    return msgett;
}
void telebot_message_entity_free(MessageEntity * msgett){
    free(msgett->type);
    free(msgett->url);
    telebot_user_free(msgett->user);
    free(msgett);
}
void telebot_message_entities_free(MessageEntity (* msgetts)[]){
    int sz = sizeof(msgetts)/sizeof(MessageEntity);
    int i;
    for(i=0;i<sz;i++){
        MessageEntity * msg = &(*msgetts)[i];
        telebot_message_entity_free(msg);
    }
}

Audio * telebot_audio(char * file_id,long int duration,char * performer,char * title,char * mime_type,long int file_size){
    Audio * audio = (Audio *)malloc(sizeof(Audio));

    audio->duration = duration;
    audio->file_size = file_size;

    audio->file_id = telebot_memory_alloc_string(file_id);
    audio->performer = telebot_memory_alloc_string(performer);
    audio->title = telebot_memory_alloc_string(title);
    audio->mime_type = telebot_memory_alloc_string(mime_type);

    return audio;
}
void telebot_audio_free(Audio * audio){
    free(audio->file_id);
    free(audio->performer);
    free(audio->title);
    free(audio->mime_type);
    free(audio);
}

Message * telebot_message(long int message_id,User * from,long int date,Chat * chat,User * forward_from,Chat * forward_from_chat,long int forward_from_message_id,long int forward_date,Message * reply_to_message,long int edit_date,char * text,MessageEntity (* entities)[],Audio * audio,Document * document,Game * game,PhotoSize (*photo)[],Sticker * sticker,Video * video,Voice * voice,char * caption,Contact * contact,Location * location,Venue * venue,User * new_chat_member,User * left_chat_member,char * new_chat_title,PhotoSize (*new_chat_photo)[],int delete_chat_photo,int group_chat_created,int supergroup_chat_created,int channel_chat_created,long int migrate_to_chat_id,long int migrate_from_chat_id,Message * pinned_message){
    Message * message = (Message *)malloc(sizeof(Message));

    //PRIMITIVE TYPES
    message->message_id = message_id;
    message->date = date;
    message->forward_from_message_id = forward_from_message_id;
    message->forward_date = forward_date;
    message->edit_date = edit_date;
    message->delete_chat_photo = delete_chat_photo;
    message->group_chat_created = group_chat_created;
    message->supergroup_chat_created = supergroup_chat_created;
    message->channel_chat_created = channel_chat_created;
    message->migrate_to_chat_id = migrate_to_chat_id;
    message->migrate_from_chat_id = migrate_from_chat_id;
    //TELEBOT TYPES
    message->from = from;
    message->chat = chat;
    message->forward_from = forward_from;
    message->forward_from_chat;
    message->reply_to_message = reply_to_message;
    message->entities = entities;
    message->audio = audio;
    message->document = document;
    message->game = game;
    message->photo = photo;
    message->sticker = sticker;
    message->video = video;
    message->voice = voice;
    message->contact = contact;
    message->location = location;
    message->venue = venue;
    message->new_chat_member = new_chat_member;
    message->left_chat_member = left_chat_member;
    message->new_chat_photo = new_chat_photo;
    message->pinned_message = pinned_message;
    //STRINGS
    message->text = telebot_memory_alloc_string(text);
    message->caption = telebot_memory_alloc_string(caption);
    message->new_chat_title = telebot_memory_alloc_string(new_chat_title);

    return message;
}
void telebot_message_free(Message * message){
    telebot_user_free(message->from);
    telebot_chat_free(message->chat);
    telebot_user_free(message->forward_from);
    telebot_chat_free(message->forward_from_chat);
    telebot_message_free(message->reply_to_message);
    telebot_message_entities_free(message->entities); //FREE THE ENTITIES
    telebot_audio_free(message->audio);
    //telebot_document_free(message->document);
    //telebot_game_free(message->game);
    //telebot_photo_free(message->photo);
    //telebot_sticker_free(message->sticker);
    //telebot_video_free(message->video);
    //telebot_voice_free(message->voice);
    //telebot_contact_free(message->contact);
    //telebot_location_free(message->location);
    //telebot_venue_free(message->venue);
    telebot_user_free(message->new_chat_member);
    telebot_user_free(message->left_chat_member);
    //telebot_photo_free(message->new_chat_photo);
    telebot_message_free(message->pinned_message);
    free(message);
}
