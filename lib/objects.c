/*
MIT License

Copyright (c) 2016 2017 Giancarlo da Silva Rocha

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <telebot.h>

static Error * _error = NULL;

void error(long int error_code, const char * description){
    Error * oerror = (Error *) malloc(sizeof(Error));
    if(!oerror)
        oerror = NULL;

    oerror->error_code = error_code;
    oerror->description = alloc_string(description);

    _error = oerror;

}

void error_free(){
    if(_error){
        if(_error->description)
            free(_error->description);
        free(_error);
        _error = NULL;
    }
}

Error * get_error(){
    return _error;
}

User * user(long int id, bool is_bot, const char *first_name, const char *last_name, const char *username, const char *language_code){
    User * user = (User *) malloc(sizeof(User));
    if(!user)
        return NULL;

    user->id = id;
    user->is_bot = is_bot;
    user->first_name    = alloc_string(first_name);
    user->last_name     = alloc_string(last_name);
    user->username      = alloc_string(username);
    user->language_code = alloc_string(language_code);

    return user;
}


void user_free(User * usr){
    if(usr->first_name)
        free(usr->first_name);

    if(usr->last_name)
        free(usr->last_name);

    if(usr->username)
        free(usr->username);
    
    if(usr->language_code)
        free(usr->language_code);

    free(usr);
    usr = NULL;
}

Bot * bot(const char * token, User * user){
    Bot * bot = (Bot *)malloc(sizeof(Bot));
    if(!bot)
        return NULL;

    bot->token = alloc_string(token);
    bot->user = user;

    return bot;
}

void bot_free(Bot * bot){

    if(bot->token)
        free(bot->token);

    user_free(bot->user);

    free(bot);
    bot = NULL;
}


Chat * chat(
    long int id, const char * type, const char * title, const char * username,
    const char * first_name, const char * last_name,
    bool all_members_are_administrators, ChatPhoto * ochat_photo,
    const char * description, const char * invite_link, Message * opinned_message,
    const char * sticker_set_name, bool can_set_sticker_set){

    Chat * chat = (Chat *) malloc(sizeof(Chat));
    if(!chat)
        return NULL;

    chat->id = id;
    chat->type = alloc_string(type);
    chat->title = alloc_string(title);
    chat->username = alloc_string(username);
    chat->first_name = alloc_string(first_name);
    chat->last_name = alloc_string(last_name);
    chat->all_members_are_administrators = all_members_are_administrators;
    chat->photo = ochat_photo;
    chat->description = alloc_string(description);
    chat->invite_link = alloc_string(invite_link);
    chat->pinned_message = opinned_message;
    chat->sticker_set_name = alloc_string(sticker_set_name);
    chat->can_set_sticker_set = can_set_sticker_set;

    return chat;
}


void chat_free(Chat * cht){

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

    if(cht->photo)
        chat_photo_free(cht->photo);

    if(cht->description)
        free(cht->description);

    if(cht->invite_link)
        free(cht->invite_link);

    if(cht->pinned_message)
        message_free(cht->pinned_message);

    if(cht->sticker_set_name)
        free(cht->sticker_set_name);

    free(cht);
    cht = NULL;
}

MessageEntity * message_entity(const char * type, long int offset, long int length, const char * url, User * user){
    MessageEntity * msgett = (MessageEntity *)malloc(sizeof(MessageEntity));
    if(!msgett)
        return NULL;

    msgett->offset = offset;
    msgett->length = length;
    msgett->user = user;

    msgett->type = alloc_string(type);
    msgett->url = alloc_string(url);

    return msgett;
}


void message_entity_free(MessageEntity * msgett){
    MessageEntity * cm = msgett, *tofree;
    
    if(!cm)
        return;

    while(cm){
        if(msgett->type)
            free(msgett->type);

        if(msgett->url)
            free(msgett->url);

        user_free(msgett->user);

        tofree = cm;
        cm = cm->next;
        free(tofree);
        tofree = NULL;
    }
}

void message_entity_add(MessageEntity * dest, MessageEntity * src){
    MessageEntity *tmp = dest;
    
    while (tmp->next)
        tmp = tmp->next;
    
    tmp->next = src;
}

size_t message_entity_len(MessageEntity * message_entity){
    size_t i;
    MessageEntity *tmp = message_entity;

    if(!tmp)
        return 0;

    for (i = 0; tmp; i++)
        tmp = tmp->next;

    return i;
}

MessageEntity * message_entity_get(MessageEntity * message_entity, int index){

}

Audio * audio(const char * file_id, long int duration, const char * performer, const char * title, const char * mime_type, long int file_size){
    Audio * audio = (Audio *)malloc(sizeof(Audio));
    if(!audio)
        return NULL;

    audio->duration = duration;
    audio->file_size = file_size;

    audio->file_id = alloc_string(file_id);
    audio->performer = alloc_string(performer);
    audio->title = alloc_string(title);
    audio->mime_type = alloc_string(mime_type);

    return audio;
}


void audio_free(Audio * audio){
    if(audio->file_id)
        free(audio->file_id);

    if(audio->performer)
        free(audio->performer);

    if(audio->title)
        free(audio->title);

    if(audio->mime_type)
        free(audio->mime_type);

    free(audio);
    audio = NULL;
}


PhotoSize * photo_size(const char * file_id,int width,int height,long int file_size){
    PhotoSize * photoSize = (PhotoSize *)malloc(sizeof(PhotoSize));
    if(!photoSize)
        return NULL;

    photoSize->file_id = alloc_string(file_id);
    photoSize->width = width;
    photoSize->height = height;
    photoSize->file_size = file_size;
    photoSize->next = NULL;

    return photoSize;
}


void photo_size_free(PhotoSize * photoSize){
    if(photoSize->file_id)
        free(photoSize->file_id);

    free(photoSize);
    photoSize = NULL;
}


void photo_size_add(PhotoSize * root, PhotoSize * newps){
    PhotoSize * aux = root;

    while(aux->next)
        aux = aux->next;

    aux->next = newps;
}


PhotoSize * photo_size_get(PhotoSize * root, int i){
    int j = 0;
    PhotoSize * aux = root;
    while(aux){
        if(j == i)
            return aux;
        j++;
        aux = aux->next;
    }
    return NULL;
}

size_t photo_size_len(PhotoSize * ophoto_size){
    size_t i;
    PhotoSize *tmp = ophoto_size;

    if(!tmp)
        return 0;

    for (i = 0; tmp; i++)
        tmp = tmp->next;

    return i;
}

Document * document(const char * file_id,PhotoSize * thumb,const char * file_name,const char * mime_type,long int file_size){
    Document * document = (Document *)malloc(sizeof(Document));
    if(!document)
        return NULL;

    document->file_id = alloc_string(file_id);
    document->thumb = thumb;
    document->file_name = alloc_string(file_name);
    document->mime_type = alloc_string(mime_type);
    document->file_size = file_size;

    return document;
}


void document_free(Document * document){
    free(document->file_id);
    photo_size_free(document->thumb);
    free(document->file_name);
    free(document->mime_type);
    free(document);
    document = NULL;
}

Animation * animation(const char * file_id,PhotoSize * thumb,const char * file_name,const char * mime_type,long int file_size){
    Animation * animation = (Animation *)malloc(sizeof(Animation));
    if(!animation)
        return NULL;

    animation->file_id = alloc_string(file_id);
    animation->thumb = thumb;
    animation->file_name = alloc_string(file_name);
    animation->mime_type = alloc_string(mime_type);
    animation->file_size = file_size;

    return animation;
}


void animation_free(Animation * animation){
    free(animation->file_id);
    free(animation->file_name);
    free(animation->mime_type);
    photo_size_free(animation->thumb);
    free(animation);
    animation = NULL;
}

Game * game( const char * title, const char * description, PhotoSize * photo, const char * text, MessageEntity * text_entities, Animation * animation){
    Game * game = (Game *)malloc(sizeof(Game));
    if(!game)
        return NULL;

    game->title = alloc_string(title);
    game->description = alloc_string(description);
    game->photo = photo;
    game->text = alloc_string(text);
    game->text_entities = text_entities;
    game->animation = animation;

    return game;
}


void game_free(Game * game){
    free(game->title);
    free(game->description);
    photo_size_free(game->photo);
    free(game->text);
    message_entity_free(game->text_entities);
    animation_free(game->animation);
    free(game);
    game = NULL;
}

Sticker * sticker(const char * file_id,int width,int height,PhotoSize * thumb,const char * emoji,long int file_size){
    Sticker * _sticker = (Sticker *)malloc(sizeof(Sticker));
    if(!_sticker)
        return NULL;

    _sticker->file_id = alloc_string(file_id);
    _sticker->emoji = alloc_string(emoji);

    _sticker->width = width;
    _sticker->height = height;
    _sticker->file_size = file_size;

    _sticker->thumb = thumb;

    return _sticker;
}


void sticker_free(Sticker * _sticker){
    if(_sticker->file_id)
        free(_sticker->file_id);

    if(_sticker->emoji)
        free(_sticker->emoji);

    if(_sticker->thumb)
        photo_size_free(_sticker->thumb);

    free(_sticker);
    _sticker = NULL;
}

Video * video(const char * file_id,int width,int height,long int duration,PhotoSize * thumb,const char * mime_type,long int file_size){
    Video * _video = (Video *)malloc(sizeof(Video));
    if(!_video)
        return NULL;

    _video->file_id = alloc_string(file_id);
    _video->mime_type = alloc_string(mime_type);

    _video->width = width;
    _video->height = height;
    _video->duration = duration;
    _video->file_size = file_size;

    _video->thumb = thumb;

    return _video;
}


void video_free(Video * _video){
    if(_video->file_id)
        free(_video->file_id);
    if(_video->mime_type)
        free(_video->mime_type);
    if(_video->thumb)
        free(_video->thumb);
    free(_video);
    _video = NULL;
}

Voice * voice(const char * file_id,long int duration,const char * mime_type,long int file_size){
    Voice * _voice = (Voice *)malloc(sizeof(Voice));
    if(!_voice)
        return NULL;

    _voice->file_id = alloc_string(file_id);
    _voice->mime_type = alloc_string(mime_type);

    _voice->duration = duration;
    _voice->file_size = file_size;

    return _voice;
}


void voice_free(Voice * _voice){
    if(_voice->file_id)
        free(_voice->file_id);
    if(_voice->mime_type)
        free(_voice->mime_type);
    free(_voice);
    _voice = NULL;
}

Contact * contact(const char * phone_number,const char * first_name,const char * last_name,long int user_id){
    Contact * _contact = (Contact *)malloc(sizeof(Contact));
    if(!_contact)
        return NULL;

    _contact->phone_number = alloc_string(phone_number);
    _contact->first_name = alloc_string(first_name);
    _contact->last_name = alloc_string(last_name);

    _contact->user_id = user_id;

    return _contact;
}


void contact_free(Contact * _contact){
    if(_contact->phone_number)
        free(_contact->phone_number);
    if(_contact->first_name)
        free(_contact->first_name);
    if(_contact->last_name)
        free(_contact->last_name);
    free(_contact);
    _contact = NULL;
}

Location * location(float latitude,float longitude){
    Location * _location = (Location *)malloc(sizeof(Location));
    if(!_location)
        return NULL;

    _location->latitude = latitude;
    _location->longitude = longitude;

    return _location;
}

void location_free(Location * _location){
    free(_location);
    _location = NULL;
}

Venue * venue(Location * location,const char * title,const char * address,const char * foursquare_id){
    Venue * _venue = (Venue *)malloc(sizeof(Venue));
    if(!_venue)
        return NULL;

    _venue->location = location;

    _venue->title = alloc_string(title);
    _venue->address = alloc_string(address);
    _venue->foursquare_id = alloc_string(foursquare_id);

    return _venue;
}

void venue_free(Venue * _venue){
    if(_venue->location)
        location_free(_venue->location);
    if(_venue->title)
        free(_venue->title);
    if(_venue->address)
        free(_venue->address);
    if(_venue->foursquare_id)
        free(_venue->foursquare_id);
    free(_venue);
    _venue = NULL;
}

Message * message(long int message_id,User * from, long int date, Chat * chat,
                  User * forward_from,Chat * forward_from_chat,long int forward_from_message_id,
                  const char * forward_signature, long int forward_date,Message * reply_to_message,long int edit_date,
                  const char * author_signature, const char * text,MessageEntity * entities, MessageEntity * ocaption_entities, Audio * audio,Document * document,
                  Game * game,PhotoSize * photo,Sticker * sticker,Video * video,Voice * voice,
                  VideoNote * video_note, const char * caption,Contact * contact,Location * location,Venue * venue,
                  User * new_chat_member,User * left_chat_member,const char * new_chat_title,
                  PhotoSize * new_chat_photo,int delete_chat_photo,int group_chat_created,
                  int supergroup_chat_created,int channel_chat_created,long int migrate_to_chat_id,
                  long int migrate_from_chat_id,Message * pinned_message, Invoice  * oinvoice, SuccessfulPayment * successful_payment){
    
    Message * message = (Message *)malloc(sizeof(Message));
    if(!message)
        return NULL;

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
    message->forward_from_chat = forward_from_chat;
    message->reply_to_message = reply_to_message;
    message->entities = entities;
    message->caption_entities = ocaption_entities;
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
    message->video_note = video_note;
    message->invoice = oinvoice;
    message->successful_payment = successful_payment;
    //STRINGS
    message->text = alloc_string(text);
    message->caption = alloc_string(caption);
    message->new_chat_title = alloc_string(new_chat_title);
    message->forward_signature = alloc_string(forward_signature);
    message->author_signature = alloc_string(author_signature);

    return message;
}


void message_free(Message * message){
    if(message->from)
        user_free(message->from);
    if(message->chat)
        chat_free(message->chat);
    if(message->forward_from)
        user_free(message->forward_from);
    if(message->forward_from_chat)
        chat_free(message->forward_from_chat);
    if(message->reply_to_message)
        message_free(message->reply_to_message);
    if(message->entities)
        message_entity_free(message->entities); //FREE THE ENTITIES
    if(message->audio)
        audio_free(message->audio);
    if(message->document)
        document_free(message->document);
    if(message->game)
        game_free(message->game);
    if(message->photo)
        //photo_free(message->photo);
    if(message->sticker)
        sticker_free(message->sticker);
    if(message->video)
        video_free(message->video);
    if(message->voice)
        voice_free(message->voice);
    if(message->contact)
        contact_free(message->contact);
    if(message->location)
        location_free(message->location);
    if(message->venue)
        venue_free(message->venue);
    if(message->new_chat_member)
        user_free(message->new_chat_member);
    if(message->left_chat_member)
        user_free(message->left_chat_member);
    if(message->pinned_message)
        message_free(message->pinned_message);
    if(message->invoice)
        invoice_free(message->invoice);

    free(message);
    message = NULL;
}


Update * update(long int update_id, Message * message, Message * edited_message, Message * channel_post, Message * edited_channel_post, InlineQuery * inline_query, ChosenInlineResult * chosen_inline_result,CallbackQuery * callback_query, ShippingQuery * shipping_query, PreCheckoutQuery * pre_checkout_query){
    Update * oupdate = (Update *)malloc(sizeof(Update));
    if(!oupdate)
        return NULL;

    oupdate->update_id = update_id;
    oupdate->message = message;
    oupdate->edited_message = edited_message;
    oupdate->channel_post = channel_post;
    oupdate->edited_channel_post = edited_channel_post;
    oupdate->inline_query = inline_query;
    oupdate->chosen_inline_result = chosen_inline_result;
    oupdate->callback_query = callback_query;
    oupdate->shipping_query = shipping_query;
    oupdate->pre_checkout_query = pre_checkout_query;

    oupdate->next = NULL;

    return oupdate;
}


void update_free(Update * oupdate){
    if(oupdate->message)
        message_free(oupdate->message);

    if(oupdate->edited_message)
        message_free(oupdate->edited_message);

    if(oupdate->channel_post)
        message_free(oupdate->channel_post);

    if(oupdate->edited_channel_post)
        message_free(oupdate->edited_channel_post);

    if(oupdate->inline_query)
        free(oupdate->inline_query);

    if(oupdate->chosen_inline_result)
        free(oupdate->chosen_inline_result);

    if(oupdate->callback_query)
        free(oupdate->callback_query);

    free(oupdate);
}

void update_add(Update *dest, Update *src) {
    Update *tmp = dest;
    
    while (tmp->next)
        tmp = tmp->next;
    
    tmp->next = src;
}


Update *update_get(Update *u, int index) {

    int i;
    Update *tmp = u;

    for (i = 0; tmp; i++) {
        if (i == index)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

size_t update_len(Update *u) {
    size_t i;
    Update *tmp = u;

    if(!tmp)
        return 0;

    for (i = 0; tmp; i++)
        tmp = tmp->next;

    return i;
}

ChatMember *chat_member(User *user, const char *status, long int until_date, bool can_be_edited,
                        bool can_change_info, bool can_post_messages, bool can_edit_messages,
                        bool can_delete_messages, bool can_invite_users, bool can_restrict_members,
                        bool can_pin_messages, bool can_promote_members, bool can_send_messages,
                        bool can_send_media_messages, bool can_send_other_messages, 
                        bool can_add_web_page_previews) {
    
    ChatMember *_cmember = (ChatMember *) malloc(sizeof(ChatMember));
    if(!_cmember)
        return NULL;

    _cmember->user               = user;
    _cmember->status             = alloc_string(status);
    _cmember->until_date         = until_date;
    _cmember->can_be_edited      = can_be_edited;
    _cmember->can_change_info    = can_change_info;
    _cmember->can_post_messages  = can_post_messages;
    _cmember->can_edit_messages  = can_edit_messages;
    _cmember->can_delete_messages = can_delete_messages;
    _cmember->can_invite_users  = can_invite_users;
    _cmember->can_restrict_members = can_restrict_members;
    _cmember->can_pin_messages  = can_pin_messages;
    _cmember->can_promote_members = can_promote_members;
    _cmember->can_send_messages = can_send_messages;
    _cmember->can_send_media_messages = can_send_media_messages;
    _cmember->can_send_other_messages = can_send_other_messages;
    _cmember->can_add_web_page_previews = can_add_web_page_previews;
    
    return _cmember;
}

void chat_member_free(ChatMember *chatMember) {
    if(chatMember->user)
        user_free(chatMember->user);

    if(chatMember->status)
        free(chatMember->status);

    free(chatMember);
    chatMember = NULL;
}

void chat_member_add (ChatMember *dest, ChatMember *src) {
    ChatMember *tmp = dest;
    while(tmp->next)
        tmp = tmp->next;
    
    tmp->next = src;
}

ChatMember *chat_member_get (ChatMember *chatMember, int index) {
    ChatMember *tmp = chatMember;

    int i;
    for (i = 0; tmp; i++) {
        if (i == index)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

size_t chat_member_len (ChatMember *chatMember) {
    ChatMember *tmp = chatMember;
    if (!tmp)
        return 0;
    
    int i;
    for (i = 0; tmp; i++) {
        tmp = tmp->next;
    }
    return i;
}

ChosenInlineResult * chosen_inline_result(const char *result_id, User *from,
                                             Location *location, const char *inline_message_id, const char * query) {

    ChosenInlineResult * cir = (ChosenInlineResult *) malloc (sizeof(ChosenInlineResult));
    if(!cir)
        return NULL;

    cir->result_id = alloc_string(result_id);
    cir->from      = from;
    cir->location  = location;
    cir->inline_message_id = alloc_string(inline_message_id);
    cir->query     = alloc_string(query);

    return cir;
}

void chosen_inline_result_free(ChosenInlineResult * cir){
    if(cir->result_id){
        free(cir->result_id);
    }

    if(cir->from){
        user_free(cir->from);
        free(cir->from);
    }

    if(cir->location) {
        location_free(cir->location);
        free(cir->location);
    }

    if(cir->inline_message_id){
        free(cir->inline_message_id);
    }

    if(cir->query){
        free(cir->query);
    }

    free(cir);
    cir = NULL;
}

InlineQuery * inline_query(const char * id, User * user, Location * location, const char *query, const char * offset){

    InlineQuery * inline_query = (InlineQuery *) malloc(sizeof(InlineQuery));
    if(!inline_query)
        return NULL;

    inline_query->id = alloc_string(id);
    inline_query->from = user;
    inline_query->location = location;
    inline_query->query = alloc_string(query);
    inline_query->offset = alloc_string(offset);

    return inline_query;
}

void inline_query_free(InlineQuery * inline_query){
    if(inline_query->id)
        free(inline_query->id);

    if(inline_query->from)
        user_free(inline_query->from);

    if(inline_query->location)
        location_free(inline_query->location);

    if(inline_query->query)
        free(inline_query->query);

    if(inline_query->offset)
        free(inline_query->offset);

    free(inline_query);
    inline_query = NULL;
}

CallbackQuery * callback_query(const char * id, User * user, Message * message, const char * inline_message_id, const char * chat_instance, const char * data, const char * game_short_name) {
    CallbackQuery * ocallbac_query = (CallbackQuery *) malloc(sizeof(CallbackQuery));
    if(!ocallbac_query)
        return NULL;

    ocallbac_query->id = alloc_string(id);
    ocallbac_query->from = user;
    ocallbac_query->message = message;
    ocallbac_query->inline_message_id = alloc_string(inline_message_id);
    ocallbac_query->chat_instance = alloc_string(chat_instance);
    ocallbac_query->data = alloc_string(data);
    ocallbac_query->game_short_name = alloc_string(game_short_name);

    return ocallbac_query;
}

void callback_query_free(CallbackQuery * callback_query){
    if(callback_query->id)
        free(callback_query->id);

    if(callback_query->from)
        user_free(callback_query->from);

    if(callback_query->message)
        message_free(callback_query->message);

    if(callback_query->chat_instance)
        free(callback_query->chat_instance);

    if(callback_query->inline_message_id)
        free(callback_query->inline_message_id);

    if(callback_query->data)
        free(callback_query->data);

    if(callback_query->game_short_name)
        free(callback_query->game_short_name);

    free(callback_query);
    callback_query = NULL;
}

VideoNote * video_note(const char * file_id, long length, long duration, PhotoSize * photo_size, long file_size){
    VideoNote * ovide_note = (VideoNote *) malloc(sizeof(VideoNote));
    if(!ovide_note)
        return NULL;

    ovide_note->file_id = alloc_string(file_id);
    ovide_note->length = length;
    ovide_note->duration = duration;
    ovide_note->thumb = photo_size;
    ovide_note->file_size = file_size;

    return ovide_note;
}

void video_note_free(VideoNote * video_note){
    if(video_note->file_id)
        free(video_note->file_id);

    if(video_note->thumb)
        photo_size_free(video_note->thumb);

    free(video_note);
    video_note = NULL;
}

Invoice * invoice(const char * title, const char * description, const char * start_parameter, const char * currency, long total_amount){
    Invoice  * oinvoice = (Invoice *) malloc(sizeof(Invoice));
    if(!oinvoice)
        return NULL;

    oinvoice->title = alloc_string(title);
    oinvoice->description = alloc_string(description);
    oinvoice->start_parameter = alloc_string(start_parameter);
    oinvoice->currency = alloc_string(currency);
    oinvoice->total_amount = total_amount;

    return oinvoice;
}

void invoice_free(Invoice * invoice){
    if(invoice->title)
        free(invoice->title);

    if(invoice->description)
        free(invoice->description);

    if(invoice->start_parameter)
        free(invoice->start_parameter);

    if(invoice->currency)
        free(invoice->currency);

    free(invoice);
    invoice = NULL;
}

ShippingQuery * shipping_query(const char *id, User * from, const char * invoice_payload, ShippingAddress * shipping_address){
    ShippingQuery * oshipping_query = (ShippingQuery *) malloc(sizeof(ShippingQuery));
    if(!oshipping_query)
        return NULL;

    oshipping_query->id = alloc_string(id);
    oshipping_query->from = from;
    oshipping_query->invoice_payload = alloc_string(invoice_payload);
    oshipping_query->shipping_address = shipping_address;

    return oshipping_query;
}

void shipping_query_free(ShippingQuery * shipping_query){
    if(shipping_query->id)
        free(shipping_query->id);

    if(shipping_query->from)
        user_free(shipping_query->from);

    if(shipping_query->invoice_payload)
        free(shipping_query->invoice_payload);

    if(shipping_query->shipping_address)
        shipping_address_free(shipping_query->shipping_address);

    free(shipping_query);
    shipping_query = NULL;
}

ShippingAddress * shipping_address(const char * country_code, const char * state, const char * city, const char * street_line1, const char * street_line2, const char * post_code){
    ShippingAddress * oshipping_address = (ShippingAddress *) malloc(sizeof(ShippingAddress));
    if(!oshipping_address)
        return NULL;

    oshipping_address->country_code = alloc_string(country_code);
    oshipping_address->state = alloc_string(state);
    oshipping_address->city = alloc_string(city);
    oshipping_address->street_line1 = alloc_string(street_line1);
    oshipping_address->street_line2 = alloc_string(street_line2);
    oshipping_address->post_code = alloc_string(post_code);

    return oshipping_address;
}

void shipping_address_free(ShippingAddress * shipping_address){
    if(shipping_address->country_code)
        free(shipping_address->country_code);

    if(shipping_address->state)
        free(shipping_address->state);

    if(shipping_address->city)
        free(shipping_address->city);

    if(shipping_address->street_line1)
        free(shipping_address->street_line1);

    if(shipping_address->street_line2)
        free(shipping_address->street_line2);

    if(shipping_address->post_code)
        free(shipping_address->post_code);

    free(shipping_address);
    shipping_address = NULL;
}

PreCheckoutQuery * pre_checkout_query(const char * id, User * from, const char * currency, long total_amount, const char * invoice_payload, const char * shipping_option_id, OrderInfo * order_info){
    PreCheckoutQuery * opre_checkout_query = (PreCheckoutQuery *) malloc(sizeof(PreCheckoutQuery));
    if(!opre_checkout_query)
        return NULL;

    opre_checkout_query->id = alloc_string(id);
    opre_checkout_query->user = from;
    opre_checkout_query->currency = alloc_string(currency);
    opre_checkout_query->total_amount = total_amount;
    opre_checkout_query->invoice_payload = alloc_string(invoice_payload);
    opre_checkout_query->shipping_option_id = opre_checkout_query->shipping_option_id;
    opre_checkout_query->order_info = order_info;

    return opre_checkout_query;
}

void pre_checkout_query_free(PreCheckoutQuery * pcq){

    if(pcq->id)
        free(pcq->id);

    if(pcq->user)
        user_free(pcq->user);

    if(pcq->currency)
        free(pcq->currency);

    if(pcq->invoice_payload)
        free(pcq->invoice_payload);

    if(pcq->shipping_option_id)
        free(pcq->shipping_option_id);

    if(pcq->order_info)
        order_info_free(pcq->order_info);

    free(pcq);
    pcq = NULL;
}

OrderInfo * order_info(const char * name, const char * phone_number, const char * email, ShippingAddress * shipping_address){
    OrderInfo * oorder_info = (OrderInfo *) malloc(sizeof(OrderInfo));
    if(!order_info)
        return NULL;

    oorder_info->name = alloc_string(name);
    oorder_info->phone_number = alloc_string(phone_number);
    oorder_info->email = alloc_string(email);
    oorder_info->shipping_address = shipping_address;

    return oorder_info;
}

void order_info_free(OrderInfo * order_info){
    if(order_info->name)
        free(order_info->name);

    if(order_info->phone_number)
        free(order_info->phone_number);

    if(order_info->email)
        free(order_info->email);

    if(order_info->shipping_address)
        shipping_address_free(order_info->shipping_address);

    free(order_info);
    order_info = NULL;
}

SuccessfulPayment * successful_payment(const char * currency, long total_amount, const char * invoice_payload, const char * shipping_option_id, OrderInfo * oorder_info, const char * telegram_payment_charge_id, const char * provider_payment_charge_id){
    SuccessfulPayment * spayment = (SuccessfulPayment *) malloc(sizeof(oorder_info));
    if(!spayment)
        return NULL;

    spayment->currency = alloc_string(currency);
    spayment->total_amount = total_amount;
    spayment->invoice_payload = alloc_string(invoice_payload);
    spayment->shipping_option_id = alloc_string(shipping_option_id);
    spayment->order_info = oorder_info;
    spayment->telegram_payment_charge_id = alloc_string(telegram_payment_charge_id);
    spayment->provider_payment_charge_id = alloc_string(provider_payment_charge_id);

    return spayment;
}

void successful_payment_free(SuccessfulPayment * spayment){
    if(spayment->currency)
        free(spayment->currency);

    if(spayment->invoice_payload)
        free(spayment->invoice_payload);

    if(spayment->shipping_option_id)
        free(spayment->shipping_option_id);

    if(spayment->order_info)
        order_info_free(spayment->order_info);

    if(spayment->telegram_payment_charge_id)
        free(spayment->telegram_payment_charge_id);

    if(spayment->provider_payment_charge_id)
        free(spayment->provider_payment_charge_id);

    free(spayment);
    spayment = NULL;
}

File * file(const char * file_id, long int file_size, const char * file_path){
    File * ofile = (File *) malloc(sizeof(File));
    if(!ofile)
        return NULL;

    ofile->file_id = alloc_string(file_id);
    ofile->file_size = file_size;
    ofile->file_path = alloc_string(file_path);

    return ofile;
}

void file_free(File * ofile){
    if(ofile->file_id)
        free(ofile->file_id);

    if(ofile->file_path)
        free(ofile->file_path);

    free(ofile);
    ofile = NULL;
}



UserProfilePhotos * user_profile_photos(long int total_count, PhotoSize ** photos){
    UserProfilePhotos * oupp = (UserProfilePhotos *) malloc(sizeof(UserProfilePhotos));
    if(!oupp)
        return NULL;

    oupp->total_count = total_count;
    oupp->photos = photos;

    return oupp;
}

void user_profile_photos_free(UserProfilePhotos * oupp){
    size_t i, x;

    if(oupp->photos){
        for(i = 0; i < oupp->total_count; i++){
                photo_size_free(oupp->photos[i]);
        }
    }

    free(oupp);
    oupp = NULL;
}

ChatPhoto * chat_photo(const char * small_file_id, const char * big_file_id){
    ChatPhoto * o_cp = (ChatPhoto *) malloc(sizeof(ChatPhoto));
    if(!o_cp)
        return NULL;

    o_cp->small_file_id = alloc_string(small_file_id);
    o_cp->big_file_id   = alloc_string(big_file_id); 

    return o_cp;
}

void chat_photo_free(ChatPhoto * ochat_photo){
    if(ochat_photo->small_file_id)
        free(ochat_photo->small_file_id);

    if(ochat_photo->big_file_id)
        free(ochat_photo->big_file_id);

    free(ochat_photo);
    ochat_photo = NULL;
}
