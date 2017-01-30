#include <telebot.h>
#include <telebot_objects.h>

User * telebot_user(long int id, const char * first_name, const char * last_name, const char * username){
    User * user = (User *) malloc(sizeof(User));

    user->id = id;
    user->first_name = telebot_memory_alloc_string(first_name);
    user->last_name = telebot_memory_alloc_string(last_name);
    user->username = telebot_memory_alloc_string(username);

    return user;
}



void telebot_user_free(User * usr){
    if(usr->first_name)
        free(usr->first_name);
    
    if(usr->last_name)
        free(usr->last_name);
    
    if(usr->username)
        free(usr->username);
    
    free(usr);
}

<<<<<<< HEAD
Bot * telebot_bot(char * token,User * user){
=======


Bot * telebot_bot(char * token){
>>>>>>> a582a5d471fd2cc0b7d13c6a853adfee0437d47c
    Bot * bot = (Bot *)malloc(sizeof(Bot));

    bot->token = telebot_memory_alloc_string(token);
    bot->user = user;

<<<<<<< HEAD
=======
    //Call getMe function ...
    User * usr = NULL;

    bot->user = usr;

>>>>>>> a582a5d471fd2cc0b7d13c6a853adfee0437d47c
    return bot;
}



void telebot_bot_free(Bot * bot){
    
    if(bot->token)
        free(bot->token);

    telebot_user_free(bot->user);

    free(bot);
}



Chat * telebot_chat(long int id, char * type, char * title, char * username, char * first_name, char * last_name, int all_members_are_administrators){
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

    if(cht->type)
        free(cht->type);
    
    if(cht->title)
        free(cht->title);
    
    if(cht->username)
        free(cht->username);
    
    if(cht->first_name)
        free(cht->first_name);
    
    if(cht->last_name)
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
    
    if(msgett->type)
        free(msgett->type);
    
    if(msgett->url)
        free(msgett->url);
    
    telebot_user_free(msgett->user);
    
    free(msgett);
}



void telebot_message_entities_free(MessageEntity (* msgetts)[]){
    
    int sz = sizeof(msgetts)/sizeof(MessageEntity);
    size_t id;

    for(id = 0; id < sz; id++){
        MessageEntity * msg = &(*msgetts)[id];
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
    if(audio->file_id)
        free(audio->file_id);
    
    if(audio->performer)
        free(audio->performer);
    
    if(audio->title)
        free(audio->title);
    
    if(audio->mime_type)
        free(audio->mime_type);
    
    free(audio);
}

<<<<<<< HEAD
PhotoSize * telebot_photo_size(char * file_id,int width,int height,long int file_size){
    PhotoSize * photoSize = (PhotoSize *)malloc(sizeof(PhotoSize));
    photoSize->file_id = telebot_memory_alloc_string(file_id);
    photoSize->width = width;
    photoSize->height = height;
    photoSize->file_size = file_size;
}
void telebot_photo_size_free(PhotoSize * photoSize){
    free(photoSize->file_id);
    free(photoSize);
}
void telebot_photo_sizes_free(PhotoSize *(* photoSize)){
    int sz = sizeof photoSize;//sizeof(PhotoSize);
    printf("sz=%s\n",sz );
    int i;
    for(i=0;i<sz;i++){
        PhotoSize * phSz = &(*photoSize)[i];
        telebot_photo_size_free(phSz);
    }
}

Document * telebot_document(char * file_id,PhotoSize * thumb,char * file_name,char * mime_type,long int file_size){
    Document * document = (Document *)malloc(sizeof(Document));

    document->file_id = telebot_memory_alloc_string(file_id);
    document->thumb = thumb;
    document->file_name = telebot_memory_alloc_string(file_name);
    document->mime_type = telebot_memory_alloc_string(mime_type);
    document->file_size = file_size;

    return document;
}
void telebot_document_free(Document * document){
    free(document->file_id);
    telebot_photo_size_free(document->thumb);
    free(document->file_name);
    free(document->mime_type);
    free(document);
}

Animation * telebot_animation(char * file_id,PhotoSize * thumb,char * file_name,char * mime_type,long int file_size){
    Animation * animation = (Animation *)malloc(sizeof(Animation));

    animation->file_id = telebot_memory_alloc_string(file_id);
    animation->thumb = thumb;
    animation->file_name = telebot_memory_alloc_string(file_name);
    animation->mime_type = telebot_memory_alloc_string(mime_type);
    animation->file_size = file_size;

    return animation;
}
void telebot_animation_free(Animation * animation){
    free(animation->file_id);
    free(animation->file_name);
    free(animation->mime_type);
    telebot_photo_size_free(animation->thumb);
    free(animation);
}

Game * telebot_game(char * title,char * description,PhotoSize (*photo)[],char * text,MessageEntity (*text_entities)[],Animation * animation){
    Game * game = (Game *)malloc(sizeof(Game));

    game->title = telebot_memory_alloc_string(title);
    game->description = telebot_memory_alloc_string(description);
    game->photo = photo;
    game->text = telebot_memory_alloc_string(text);
    game->text_entities = text_entities;
    game->animation = animation;

    return game;
}
void telebot_game_free(Game * game){
    free(game->title);
    free(game->description);
    telebot_photo_sizes_free(game->photo);
    free(game->text);
    telebot_message_entities_free(game->text_entities);
    telebot_animation_free(game->animation);
    free(game);
}
=======

>>>>>>> a582a5d471fd2cc0b7d13c6a853adfee0437d47c

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
