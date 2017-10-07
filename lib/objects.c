#include <telebot.h>

User * user(long int id, bool is_bot, const char *first_name, const char *last_name, const char *username, char *language_code){
    User * user = (User *) malloc(sizeof(User));

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
}

Bot * bot(const char * token, User * user){
    Bot * bot = (Bot *)malloc(sizeof(Bot));

    bot->token = alloc_string(token);
    bot->user = user;

    return bot;
}

void bot_free(Bot * bot){

    if(bot->token)
        free(bot->token);

    user_free(bot->user);

    free(bot);
}


Chat * chat(long int id, const char * type, const char * title, const char * username, const char * first_name, const char * last_name, int all_members_are_administrators){
    Chat * chat = (Chat *) malloc(sizeof(Chat));

    chat->id = id;
    chat->all_members_are_administrators = all_members_are_administrators;

    chat->type = alloc_string(type);
    chat->title = alloc_string(title);
    chat->username = alloc_string(username);
    chat->first_name = alloc_string(first_name);
    chat->last_name = alloc_string(last_name);

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

    free(cht);
}

MessageEntity * message_entity(const char * type, long int offset, long int length, const char * url, User * user){
    MessageEntity * msgett = (MessageEntity *)malloc(sizeof(MessageEntity));

    msgett->offset = offset;
    msgett->length = length;
    msgett->user = user;

    msgett->type = alloc_string(type);
    msgett->url = alloc_string(url);

    return msgett;
}


void message_entity_free(MessageEntity * msgett){

    if(msgett->type)
        free(msgett->type);

    if(msgett->url)
        free(msgett->url);

    user_free(msgett->user);

    free(msgett);
}

Audio * audio(const char * file_id, long int duration, const char * performer, const char * title, const char * mime_type, long int file_size){
    Audio * audio = (Audio *)malloc(sizeof(Audio));

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
}


PhotoSize * photo_size(const char * file_id,int width,int height,long int file_size){
    PhotoSize * photoSize = (PhotoSize *)malloc(sizeof(PhotoSize));

    photoSize->file_id = alloc_string(file_id);
    photoSize->width = width;
    photoSize->height = height;
    photoSize->file_size = file_size;
    photoSize->next = NULL;

    return photoSize;
}


void photo_size_free(PhotoSize * photoSize){
    PhotoSize * aux = photoSize, * tmp;
    while(aux){
        if(aux->file_id)
            free(aux->file_id);

        tmp = aux;
        aux = aux->next;
        free(tmp);
    }
}


void photo_size_add(PhotoSize * root,PhotoSize * newps){
    PhotoSize * aux = root->next;

    while(aux != NULL)
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

Document * document(const char * file_id,PhotoSize * thumb,const char * file_name,const char * mime_type,long int file_size){
    Document * document = (Document *)malloc(sizeof(Document));

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
}

Animation * animation(const char * file_id,PhotoSize * thumb,const char * file_name,const char * mime_type,long int file_size){
    Animation * animation = (Animation *)malloc(sizeof(Animation));

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
}

Game * game( const char * title, const char * description, PhotoSize * photo, const char * text, MessageEntity * text_entities, Animation * animation){
    Game * game = (Game *)malloc(sizeof(Game));

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
}

Sticker * sticker(const char * file_id,int width,int height,PhotoSize * thumb,const char * emoji,long int file_size){
    Sticker * _sticker = (Sticker *)malloc(sizeof(Sticker));

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
}

Video * video(const char * file_id,int width,int height,long int duration,PhotoSize * thumb,const char * mime_type,long int file_size){
    Video * _video = (Video *)malloc(sizeof(Video));

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
}

Voice * voice(const char * file_id,long int duration,const char * mime_type,long int file_size){
    Voice * _voice = (Voice *)malloc(sizeof(Voice));

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
}

Contact * contact(const char * phone_number,const char * first_name,const char * last_name,long int user_id){
    Contact * _contact = (Contact *)malloc(sizeof(Contact));

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
}

Location * location(float latitude,float longitude){
    Location * _location = (Location *)malloc(sizeof(Location));

    _location->latitude = latitude;
    _location->longitude = longitude;

    return _location;
}

void location_free(Location * _location){
    free(_location);
}

Venue * venue(Location * location,const char * title,const char * address,const char * foursquare_id){
    Venue * _venue = (Venue *)malloc(sizeof(Venue));

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
}

Message * message(long int message_id,User * from, long int date, Chat * chat,
                  User * forward_from,Chat * forward_from_chat,long int forward_from_message_id,
                  long int forward_date,Message * reply_to_message,long int edit_date,
                  const char * text,MessageEntity * entities,Audio * audio,Document * document,
                  Game * game,PhotoSize * photo,Sticker * sticker,Video * video,Voice * voice,
                  const char * caption,Contact * contact,Location * location,Venue * venue,
                  User * new_chat_member,User * left_chat_member,const char * new_chat_title,
                  PhotoSize * new_chat_photo,int delete_chat_photo,int group_chat_created,
                  int supergroup_chat_created,int channel_chat_created,long int migrate_to_chat_id,
                  long int migrate_from_chat_id,Message * pinned_message){
    
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
    message->forward_from_chat = forward_from_chat;
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
    message->text = alloc_string(text);
    message->caption = alloc_string(caption);
    message->new_chat_title = alloc_string(new_chat_title);

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
    free(message);
}


Update * update(long int update_id, Message * message, Message * edited_message, Message * channel_post, Message * edited_channel_post, InlineQuery * inline_query, ChoosenInlineResult * choosen_inline_result,CallbackQuery * callback_query){
    Update * oupdate = (Update *)malloc(sizeof(Update));

    oupdate->update_id = update_id;
    oupdate->message = message;
    oupdate->edited_message = edited_message;
    oupdate->channel_post = channel_post;
    oupdate->edited_channel_post = edited_channel_post;
    oupdate->inline_query = inline_query;
    oupdate->choosen_inline_result = choosen_inline_result;
    oupdate->callback_query = callback_query;

	oupdate->next = NULL;

    return oupdate;
}


void update_free(Update * oupdate){
    if(oupdate->message)
        free(oupdate->message);
    if(oupdate->edited_message)
        free(oupdate->edited_message);
    if(oupdate->channel_post)
        free(oupdate->channel_post);
    if(oupdate->edited_channel_post)
        free(oupdate->edited_channel_post);
    if(oupdate->inline_query)
        free(oupdate->inline_query);
    if(oupdate->choosen_inline_result)
        free(oupdate->choosen_inline_result);
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

	int i = 0;
	Update *tmp = u;

	for (; tmp; i++) {
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

	for (i = 1; tmp; i++)
		tmp = tmp->next;

	return (i - 1);
}

ChatMember *chat_member(User *user, const char *status, long int until_date, bool can_be_edited,
                        bool can_change_info, bool can_post_messages, bool can_edit_messages,
                        bool can_delete_messages, bool can_invite_users, bool can_restrict_members,
                        bool can_pin_messages, bool can_promote_members, bool can_send_messages,
                        bool can_send_media_messages, bool can_send_other_messages, 
                        bool can_add_web_page_previews) {
    
    ChatMember *_cmember = (ChatMember *) malloc(sizeof(ChatMember));

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
    user_free(chatMember->user);
    free(chatMember->status);
    free(chatMember);
}
