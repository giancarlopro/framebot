/**
 * MIT License
 * Copyright (c) 2016 - 2018 Giancarlo Rocha & Ródgger Bruno
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <framebot/framebot.h>


static Error *_error = NULL;


/**
 ** Funcations error
 **/
void error(int64_t error_code, const char *description){
    Error *oerror = (Error *) malloc(sizeof(Error));
    if(!oerror)
        oerror = NULL;

    oerror->error_code = (int)error_code;
    oerror->description = alloc_string(description);

    if(_error)
        error_free();

    _error = oerror;

}

void error_free(){
    if(_error){
        if(_error->description)
            ffree(_error->description);
        ffree(_error);
        _error = NULL;
    }
}

Error *get_error(){
    return _error;
}


/**
 ** functions user
 ** https://core.telegram.org/bots/api#user
 **
 ** typedef struct _user{
 **   int64_t id;
 **   bool is_bot:1;
 **   char *first_name;
 **   char *last_name;
 **   char *username;
 **   char *language_code;
 **
 **   struct _user *next;
 ** } User;
 **/
void user_add(User *origin, User *next){
    User *o = origin;

    while(o->next){
        o = o->next;
    }

    o->next = next;
}

void user_free(User *usr){

    ffree(usr->first_name);

    ffree(usr->last_name);

    ffree(usr->username);
    
    ffree(usr->language_code);

    ffree(usr);
}


/**
 ** functions bot
 **/
Bot *bot(const char *token, User *user){
    Bot *bot = (Bot *)malloc(sizeof(Bot));
    if(!bot)
        return NULL;

    bot->token = alloc_string(token);
    bot->user = user;

    return bot;
}

void bot_free(Bot *bot){

    if(bot->token)
        ffree(bot->token);

    user_free(bot->user);

    ffree(bot);
}

/**
 ** functions Chat *
 ** https://core.telegram.org/bots/api#chat
 **
 ** typedef struct _chat{
 **    int64_t id;
 **    char *type;
 **    char *title;
 **    char *username;
 **    char *first_name;
 **    char *last_name;
 **    bool all_members_are_administrators:1;
 **    ChatPhoto *photo;
 **    char *description;
 **    char *invite_link;
 **    struct _message *pinned_message;
 **    char *sticker_set_name;
 **    bool can_set_sticker_set:1;
 **} Chat;
 **/
void chat_free(Chat *cht){

    if(cht->type)
        ffree(cht->type);

    if(cht->title)
        ffree(cht->title);

    if(cht->username)
        ffree(cht->username);

    if(cht->first_name)
        ffree(cht->first_name);

    if(cht->last_name)
        ffree(cht->last_name);

    if(cht->photo)
        chat_photo_free(cht->photo);

    if(cht->description)
        ffree(cht->description);

    if(cht->invite_link)
        ffree(cht->invite_link);

    if(cht->pinned_message)
        message_free(cht->pinned_message);

    if(cht->sticker_set_name)
        ffree(cht->sticker_set_name);

    ffree(cht);
}

/**
 ** entities
 ** https://core.telegram.org/bots/api#messageentity
 **/
void message_entity_free(MessageEntity *msgett){

    if(msgett->type)
        ffree(msgett->type);

    if(msgett->url)
        ffree(msgett->url);

    if(msgett->user)
        user_free(msgett->user);

    ffree(msgett);
}

void message_entity_add(MessageEntity *dest, MessageEntity *src){
    MessageEntity *tmp = dest;
    
    while (tmp->next)
        tmp = tmp->next;
    
    tmp->next = src;
}

size_t message_entity_len(MessageEntity *message_entity){
    size_t i;
    MessageEntity *tmp = message_entity;

    if(!tmp)
        return 0;

    for (i = 0; tmp; i++)
        tmp = tmp->next;

    return i;
}

MessageEntity *message_entity_get(MessageEntity *message_entity, int index){
    MessageEntity *m_e = message_entity;
    size_t i = 0, len = message_entity_len(m_e);

    for(i = 0; m_e && i < len; i++){
        if(i == len){
            return m_e;
        }

        m_e = m_e->next;
    }

    return NULL;;
}


void audio_free(Audio *audio){
    if(audio->file_id)
        ffree(audio->file_id);

    if(audio->performer)
        ffree(audio->performer);

    if(audio->title)
        ffree(audio->title);

    if(audio->mime_type)
        ffree(audio->mime_type);

    ffree(audio);
    audio = NULL;
}

/**
 ** functions photo_size
 ** https://core.telegram.org/bots/api#photosize
 **/
void photo_size_free(PhotoSize *photoSize){
    if(photoSize != NULL){
        if(photoSize->file_id)
            ffree(photoSize->file_id);

        ffree(photoSize);
    }

    photoSize = NULL;
}


void photo_size_add(PhotoSize *root, PhotoSize *newps){
    PhotoSize *aux = root;

    while(aux->next){
        aux = aux->next;
    }

    aux->next = newps;
}


PhotoSize *photo_size_get(PhotoSize *root, int i){
    int j = 0;
    PhotoSize *aux = root;

    while(aux){
        if(j == i)
            return aux;
        j++;
        aux = aux->next;
    }
    return NULL;
}

size_t photo_size_len(PhotoSize *ophoto_size){
    size_t i;
    PhotoSize *tmp = ophoto_size;

    if(!tmp)
        return 0;

    for (i = 0; tmp; i++)
        tmp = tmp->next;

    return i;
}

void document_free(Document *document){
    ffree(document->file_id);
    if(document->thumb)
        photo_size_free(document->thumb);
    ffree(document->file_name);
    ffree(document->mime_type);
    ffree(document);
    document = NULL;
}


void animation_free(Animation *animation){
    ffree(animation->file_id);
    ffree(animation->file_name);
    ffree(animation->mime_type);
    photo_size_free(animation->thumb);
    ffree(animation);
    animation = NULL;
}

void game_free(Game *game){
    ffree(game->title);
    ffree(game->description);
    photo_size_free(game->photo);
    ffree(game->text);
    message_entity_free(game->text_entities);
    animation_free(game->animation);
    ffree(game);
    game = NULL;
}


void sticker_free(Sticker *_sticker){
    if(_sticker->file_id)
        ffree(_sticker->file_id);

    if(_sticker->emoji)
        ffree(_sticker->emoji);

    if(_sticker->thumb)
        photo_size_free(_sticker->thumb);

    ffree(_sticker);
    _sticker = NULL;
}


void video_free(Video *_video){
    if(_video->file_id)
        ffree(_video->file_id);
    if(_video->mime_type)
        ffree(_video->mime_type);
    if(_video->thumb)
        ffree(_video->thumb);
    ffree(_video);
    _video = NULL;
}


void voice_free(Voice *_voice){
    if(_voice->file_id)
        ffree(_voice->file_id);
    if(_voice->mime_type)
        ffree(_voice->mime_type);
    ffree(_voice);
    _voice = NULL;
}

void contact_free(Contact *_contact){
    if(_contact->phone_number)
        ffree(_contact->phone_number);
    if(_contact->first_name)
        ffree(_contact->first_name);
    if(_contact->last_name)
        ffree(_contact->last_name);
    ffree(_contact);
    _contact = NULL;
}

void location_free(Location *_location){
    ffree(_location);
    _location = NULL;
}


void venue_free(Venue *_venue){
    if(_venue->location)
        location_free(_venue->location);
    if(_venue->title)
        ffree(_venue->title);
    if(_venue->address)
        ffree(_venue->address);
    if(_venue->foursquare_id)
        ffree(_venue->foursquare_id);
    ffree(_venue);
    _venue = NULL;
}

/**
 ** functions
 ** https://core.telegram.org/bots/api#message
 **/
void message_free(Message *message){
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

    if(message->entities){
        MessageEntity *m_next = message->entities, *m = m_next;
        while(m){
            m_next = m->next;
            message_entity_free(m); //FREE THE ENTITIES
            m = m_next;
        }
    }

    if(message->caption_entities){
        MessageEntity *m_next = message->caption_entities, *m = m_next;
        while(m){
            m_next = m->next;
            message_entity_free(m); //FREE THE ENTITIES
            m = m_next;
        }
    }

    if(message->audio)
        audio_free(message->audio);

    if(message->document)
        document_free(message->document);

    if(message->game)
        game_free(message->game);

    if(message->photo){
        PhotoSize *p_next = message->photo, *p = p_next;
        while(p){
            p_next = p->next;
            photo_size_free(p); //FREE THE PHOTO
            p = p_next;
        }
    }

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

    if(message->new_chat_members){
        User *u_next = message->new_chat_members, *u = u_next;
        while(u){
            u_next = u->next;
            user_free(u); //FREE THE USER
            u = u_next;
        }
    }

    if(message->left_chat_member)
        user_free(message->left_chat_member);

    if(message->new_chat_photo){
        PhotoSize *ncp_next = message->new_chat_photo, *ncp = ncp_next;
        while(ncp){
            ncp_next = ncp->next;
            photo_size_free(ncp); //FREE THE PHOTO
            ncp = ncp_next;
        }
    }

    if(message->pinned_message)
        message_free(message->pinned_message);

    if(message->invoice)
        invoice_free(message->invoice);

    if(message->video_note)
        video_note_free(message->video_note);

    if(message->successful_payment)
        successful_payment_free(message->successful_payment);

    if(message->text)
        ffree(message->text);

    if(message->caption)
        ffree(message->caption);

    if(message->new_chat_title)
        ffree(message->new_chat_title);

    if(message->forward_signature)
        ffree(message->forward_signature);

    if(message->author_signature)
        ffree(message->author_signature);
    
    if(message->media_group_id)
        ffree(message->media_group_id);

    ffree(message);
    message = NULL;
}


void update_free(Update *oupdate){
    if(oupdate->message)
        message_free(oupdate->message);

    if(oupdate->edited_message)
        message_free(oupdate->edited_message);

    if(oupdate->channel_post)
        message_free(oupdate->channel_post);

    if(oupdate->edited_channel_post)
        message_free(oupdate->edited_channel_post);

    if(oupdate->inline_query)
        inline_query_free(oupdate->inline_query);

    if(oupdate->chosen_inline_result)
        chosen_inline_result_free(oupdate->chosen_inline_result);

    if(oupdate->callback_query)
        callback_query_free(oupdate->callback_query);

    if(oupdate->shipping_query)
        shipping_query_free(oupdate->shipping_query);

    if(oupdate->pre_checkout_query)
        pre_checkout_query_free(oupdate->pre_checkout_query);



    ffree(oupdate);
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


void chat_member_free(ChatMember *chatMember) {
    if(chatMember->user)
        user_free(chatMember->user);

    if(chatMember->status)
        ffree(chatMember->status);

    ffree(chatMember);
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


/**
 ** functions choosen_inline_result
 ** https://core.telegram.org/bots/api#choseninlineresult
 **/

void chosen_inline_result_free(ChosenInlineResult *cir){
    if(cir->result_id){
        ffree(cir->result_id);
    }

    if(cir->from){
        user_free(cir->from);
        ffree(cir->from);
    }

    if(cir->location) {
        location_free(cir->location);
        ffree(cir->location);
    }

    if(cir->inline_message_id){
        ffree(cir->inline_message_id);
    }

    if(cir->query){
        ffree(cir->query);
    }

    ffree(cir);
}


/**
 ** functions inline_query
 ** https://core.telegram.org/bots/api#inlinequery
 **/

void inline_query_free(InlineQuery *inline_query){
    if(inline_query->id)
        ffree(inline_query->id);

    if(inline_query->from)
        user_free(inline_query->from);

    if(inline_query->location)
        location_free(inline_query->location);

    if(inline_query->query)
        ffree(inline_query->query);

    if(inline_query->offset)
        ffree(inline_query->offset);

    ffree(inline_query);
}

/**
 ** functions callback_query
 ** https://core.telegram.org/bots/api#callbackquery
 **/

void callback_query_free(CallbackQuery *callback_query){
    if(callback_query->id)
        ffree(callback_query->id);

    if(callback_query->from)
        user_free(callback_query->from);

    if(callback_query->message)
        message_free(callback_query->message);

    if(callback_query->chat_instance)
        ffree(callback_query->chat_instance);

    if(callback_query->inline_message_id)
        ffree(callback_query->inline_message_id);

    if(callback_query->data)
        ffree(callback_query->data);

    if(callback_query->game_short_name)
        ffree(callback_query->game_short_name);

    ffree(callback_query);
    callback_query = NULL;
}

/**
 ** functions video_note
 ** https://core.telegram.org/bots/api#videonote
 **/

void video_note_free(VideoNote *video_note){
    if(video_note->file_id)
        ffree(video_note->file_id);

    if(video_note->thumb)
        photo_size_free(video_note->thumb);

    ffree(video_note);
    video_note = NULL;
}

/**
 ** functions invoice
 ** https://core.telegram.org/bots/api#invoice
 **/
void invoice_free(Invoice *invoice){
    if(invoice->title)
        ffree(invoice->title);

    if(invoice->description)
        ffree(invoice->description);

    if(invoice->start_parameter)
        ffree(invoice->start_parameter);

    if(invoice->currency)
        ffree(invoice->currency);

    ffree(invoice);
    invoice = NULL;
}

/**
 ** functions shipping_query
 ** https://core.telegram.org/bots/api#shippingquery
 **/
void shipping_query_free(ShippingQuery *shipping_query){
    if(shipping_query->id)
        ffree(shipping_query->id);

    if(shipping_query->from)
        user_free(shipping_query->from);

    if(shipping_query->invoice_payload)
        ffree(shipping_query->invoice_payload);

    if(shipping_query->shipping_address)
        shipping_address_free(shipping_query->shipping_address);

    ffree(shipping_query);
}

/**
 ** functions shipping_address
 ** https://core.telegram.org/bots/api#shippingaddress
 **/
void shipping_address_free(ShippingAddress *shipping_address){
    if(shipping_address->country_code)
        ffree(shipping_address->country_code);

    if(shipping_address->state)
        ffree(shipping_address->state);

    if(shipping_address->city)
        ffree(shipping_address->city);

    if(shipping_address->street_line1)
        ffree(shipping_address->street_line1);

    if(shipping_address->street_line2)
        ffree(shipping_address->street_line2);

    if(shipping_address->post_code)
        ffree(shipping_address->post_code);

    ffree(shipping_address);
    shipping_address = NULL;
}

/**
 ** functions pre_checkout_query
 ** https://core.telegram.org/bots/api#precheckoutquery
 **/
void pre_checkout_query_free(PreCheckoutQuery *pcq){

    if(pcq->id)
        ffree(pcq->id);

    if(pcq->from)
        user_free(pcq->from);

    if(pcq->currency)
        ffree(pcq->currency);

    if(pcq->invoice_payload)
        ffree(pcq->invoice_payload);

    if(pcq->shipping_option_id)
        ffree(pcq->shipping_option_id);

    if(pcq->order_info)
        order_info_free(pcq->order_info);

    ffree(pcq);
    pcq = NULL;
}

/**
 ** functions order_info
 ** https://core.telegram.org/bots/api#orderinfo
 **/
void order_info_free(OrderInfo *order_info){
    if(order_info->name)
        ffree(order_info->name);

    if(order_info->phone_number)
        ffree(order_info->phone_number);

    if(order_info->email)
        ffree(order_info->email);

    if(order_info->shipping_address)
        shipping_address_free(order_info->shipping_address);

    ffree(order_info);
    order_info = NULL;
}

/**
 ** functions successful_payment
 ** https://core.telegram.org/bots/api#successfulpayment
 **/
void successful_payment_free(SuccessfulPayment *spayment){
    if(spayment->currency)
        ffree(spayment->currency);

    if(spayment->invoice_payload)
        ffree(spayment->invoice_payload);

    if(spayment->shipping_option_id)
        ffree(spayment->shipping_option_id);

    if(spayment->order_info)
        order_info_free(spayment->order_info);

    if(spayment->telegram_payment_charge_id)
        ffree(spayment->telegram_payment_charge_id);

    if(spayment->provider_payment_charge_id)
        ffree(spayment->provider_payment_charge_id);

    ffree(spayment);
    spayment = NULL;
}

/**
 ** functions file
 ** https://core.telegram.org/bots/api#file
 **/
void file_free(File *ofile){
    if(ofile->file_id)
        ffree(ofile->file_id);

    if(ofile->file_path)
        ffree(ofile->file_path);

    ffree(ofile);
    ofile = NULL;
}


/**
 ** functions user_profile_photos
 ** https://core.telegram.org/bots/api#userprofilephotos
 **/

void user_profile_photos_free(UserProfilePhotos *oupp){
    size_t i;

    PhotoSize *photo, *upp_n;

    if(oupp->photos){
        for(i = 0; i < oupp->total_count; i++){
            photo = oupp->photos[i];
  
            while(photo){
                upp_n = photo->next;
                photo_size_free(photo);
                photo = upp_n;
            }
        }
        ffree(oupp->photos);
    }

    ffree(oupp);
    oupp = NULL;
}

/**
 ** functions chat_photo
 ** https://core.telegram.org/bots/api#chatphoto
 **/
void chat_photo_free(ChatPhoto *ochat_photo){
    if(ochat_photo->small_file_id)
        ffree(ochat_photo->small_file_id);

    if(ochat_photo->big_file_id)
        ffree(ochat_photo->big_file_id);

    ffree(ochat_photo);
    ochat_photo = NULL;
}

void framebot_add( Framebot *framebot, Update *update ){
    
    if( update->message ) {
        if(!framebot->up_message)
            framebot->up_message = update;
        else
            update_add(framebot->up_message, update);
    }


    else if( update->edited_message ) {
        if(!framebot->up_edited_message)
            framebot->up_edited_message = update;
        else
            update_add(framebot->up_edited_message, update);
    }


    else if( update->channel_post ) {
        if(!framebot->up_channel_post)
            framebot->up_channel_post = update;
        else
            update_add(framebot->up_channel_post, update);
    }


    else if( update->edited_channel_post ) {
        if(!framebot->up_edited_channel_post)
            framebot->up_edited_channel_post = update;
        else
            update_add(framebot->up_edited_channel_post, update);
    }


    else if( update->inline_query ) {
        if(!framebot->up_inline_query)
            framebot->up_inline_query = update;
        else
            update_add(framebot->up_inline_query, update);
    }


    else if( update->chosen_inline_result ) {
        if(!framebot->up_chosen_inline_result)
            framebot->up_chosen_inline_result = update;
        else
            update_add(framebot->up_chosen_inline_result, update);
    }


    else if( update->callback_query ) {
        if(!framebot->up_callback_query)
            framebot->up_callback_query = update;
        else
            update_add(framebot->up_callback_query, update);
    }


    else if( update->shipping_query ) {
        if(!framebot->up_shipping_query)
            framebot->up_shipping_query = update;
        else
            update_add(framebot->up_shipping_query, update);
    }


    else if( update->pre_checkout_query ) {
        if(!framebot->up_pre_checkout_query)
            framebot->up_pre_checkout_query = update;
        else
            update_add(framebot->up_pre_checkout_query, update);
    }

    framebot->update_id = UPDATE_ID_LAST(framebot, update);

}


void framebot_free(Framebot *framebot) {

    if(framebot->up_message) {
        update_free(framebot->up_message);
    }
    else if(framebot->up_edited_message) {
        update_free(framebot->up_edited_message);
    }
    else if(framebot->up_channel_post) {
        update_free(framebot->up_channel_post);
    }
    else if(framebot->up_edited_channel_post) {
        update_free(framebot->up_edited_channel_post);
    }
    else if(framebot->up_inline_query) {
        update_free(framebot->up_inline_query);
    }
    else if(framebot->up_chosen_inline_result) {
        update_free(framebot->up_chosen_inline_result);
    }
    else if(framebot->up_callback_query) {
        update_free(framebot->up_callback_query);
    }
    else if(framebot->up_shipping_query) {
        update_free(framebot->up_shipping_query);
    }
    else if(framebot->up_pre_checkout_query) {
        update_free(framebot->up_pre_checkout_query);
    }

    ffree(framebot);
}
