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


refjson * start_json(char * json){
    refjson *s_json = NULL;
    json_t *root, *ok;

    s_json = load (json);
    root = s_json->root;

    if(json_is_object( root )){
        
        ok = json_object_get(root, "ok");
        
        if(json_is_true(ok)){
            error_free();
            s_json->content = json_object_get(root, "result");
            return s_json;
        }
        else{
            error_parse(s_json);
        }
    }

    close_json(s_json);

    return NULL;
}

refjson * load(char *json){
    json_error_t error;
    refjson * s_json;

    s_json = (refjson *)calloc(1, sizeof(refjson));

    s_json->root = json_loads(json, 0, &error);

    return s_json;
}

void close_json( refjson *s_json ) {
    
    if(s_json){
        if(s_json->root)
            json_decref(s_json->root);

        free(s_json);
    }
}

void error_parse(refjson * json){


    if(json_is_object(json->root)){
        json_t * error_code, *description;

        error_code = json_object_get(json->root, "error_code");
        description = json_object_get(json->root, "description");

        error(json_integer_value(error_code), json_string_value(description));

    }
}

User * user_parse(json_t *json){
    User *object = NULL;
    json_t *puser = json;

    if(json_is_object(puser)){
        object = (User *) calloc(1, sizeof(User));
        if(!object)
            return NULL;

        json_t *id, *is_bot, *first_name, *last_name, *username, *language_code;

        id = json_object_get(puser, "id");
        object->id = json_integer_value(id);

        is_bot = json_object_get(puser, "is_bot");
        object->is_bot = json_boolean_value(is_bot);

        first_name = json_object_get(puser, "first_name");
        object->first_name = alloc_string(json_string_value(first_name));

        last_name = json_object_get(puser, "last_name");
        object->last_name = alloc_string(json_string_value(last_name));

        username = json_object_get(puser, "username");
        object->username = alloc_string(json_string_value(username));

        language_code = json_object_get(puser, "language_code");
        object->language_code =alloc_string(json_string_value(language_code));

        object->next = NULL;

        return object;
    }

    return NULL;
}

Chat * chat_parse(json_t *json){
    Chat *object = NULL;
    json_t * pchat = json;

    if(json_is_object(pchat)){
        object = (Chat *) calloc(1, sizeof(Chat));
        if(!object)
            return NULL;

        json_t *id, *type, *title, *username, *first_name,
        *last_name, *all_members_are_administrators, *photo,
        *description, *invite_link, *pinned_message,
        *sticker_set_name, *can_set_sticker_set;

        id = json_object_get(pchat,"id");
        object->id = json_integer_value(id);

        type = json_object_get(pchat,"type");
        object->type = alloc_string(json_string_value(type));

        title = json_object_get(pchat,"title");
        object->title = alloc_string(json_string_value(title));

        username = json_object_get(pchat,"username");
        object->username = alloc_string(json_string_value(username));

        first_name = json_object_get(pchat,"first_name");
        object->first_name = alloc_string(json_string_value(first_name));

        last_name = json_object_get(pchat,"last_name");
        object->last_name = alloc_string(json_string_value(last_name));

        all_members_are_administrators = json_object_get(pchat,"all_members_are_administrators");
        object->all_members_are_administrators =
                json_boolean_value(all_members_are_administrators);

        photo = json_object_get(json, "photo");
        object->photo = chat_photo_parse(photo);

        description = json_object_get(json, "description");
        object->description = alloc_string(json_string_value(description));

        invite_link = json_object_get(json, "invite_link");
        object->invite_link = alloc_string(json_string_value(invite_link));
        
        pinned_message = json_object_get(json, "pinned_message");
        object->pinned_message = message_parse(pinned_message);

        sticker_set_name = json_object_get(json, "sticker_set_name");
        object->sticker_set_name = alloc_string(json_string_value(sticker_set_name));

        can_set_sticker_set = json_object_get(json, "can_set_sticker_set");
        object->can_set_sticker_set = json_boolean_value(can_set_sticker_set);

        return object;
    }
    return NULL;
}

MessageEntity * message_entity_parse(json_t *json){
    MessageEntity *object = NULL;
    json_t * pmessage_entity = json;

    if(json_is_object(pmessage_entity)){
        object = (MessageEntity *) calloc(1, sizeof(MessageEntity));
        if(!object)
            return NULL;

        json_t *type, *offset, *length, *url, *user;

        type = json_object_get(pmessage_entity,"type");
        object->type = alloc_string(json_string_value(type));

        offset = json_object_get(pmessage_entity,"offset");
        object->offset = json_integer_value(offset);

        length = json_object_get(pmessage_entity,"length");
        object->length = json_integer_value(length);

        url = json_object_get(pmessage_entity,"url");
        object->url = alloc_string(json_string_value(url));

        user = json_object_get(pmessage_entity,"user");
        object->user = user_parse(user);

        object->next = NULL;

        return object;
    }

    return NULL;
}

Audio * audio_parse(json_t *json){
    Audio *object = NULL;
    json_t * paudio = json;

    if(json_is_object(paudio)){
        object = (Audio *) calloc(1, sizeof(Audio));
        if(!object)
            return NULL;

        json_t *file_id, *duration, *performer, *title, *mime_type, *file_size;

        file_id = json_object_get(paudio,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        duration = json_object_get(paudio,"duration");
        object->duration = json_integer_value(duration);

        performer = json_object_get(paudio,"performer");
        object->performer = alloc_string(json_string_value(performer));

        title = json_object_get(paudio,"title");
        object->title = alloc_string(json_string_value(title));

        mime_type = json_object_get(paudio,"mime_type");
        object->mime_type = alloc_string(json_string_value(mime_type));

        file_size = json_object_get(paudio,"file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }
    return NULL;
}

PhotoSize * photo_size_parse(json_t *json) {
    PhotoSize *object = NULL;
    json_t * pphoto_size = json;

    if(json_is_object(pphoto_size)){
        object = (PhotoSize *) calloc(1, sizeof(PhotoSize));
        if(!object)
            return NULL;

        json_t *file_id, *width, *height, *file_size;

        file_id = json_object_get(pphoto_size,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        width = json_object_get(pphoto_size,"width");
        object->width = (int)json_integer_value(width);

        height = json_object_get(pphoto_size,"height");
        object->height = (int)json_integer_value(height);

        file_size = json_object_get(pphoto_size,"file_size");
        object->file_size = json_integer_value(file_size);

        object->next = NULL;

        return object;
    }

    return NULL;
}

Document * document_parse(json_t *json){
    Document *object = NULL;
    json_t * pdocument = json;

    if(json_is_object(pdocument)){
        object = (Document *) calloc(1, sizeof(Document));
        if(!object)
            return NULL;

        json_t *file_id, *thumb, *file_name, *mime_type, *file_size;

        file_id = json_object_get(pdocument,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        thumb = json_object_get(pdocument,"thumb");
        object->thumb = photo_size_parse(thumb);

        file_name = json_object_get(pdocument,"file_name");
        object->file_name = alloc_string(json_string_value(file_name));

        mime_type = json_object_get(pdocument,"mime_type");
        object->mime_type = alloc_string(json_string_value(mime_type));

        file_size = json_object_get(pdocument,"file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }

    return NULL;
}

Animation * animation_parse(json_t *json){
    Animation *object = NULL;
    json_t * panimation = json;

    if(json_is_object(panimation)){
        object = (Animation *) calloc(1, sizeof(Animation));
        if(!object)
            return NULL;

        json_t *file_id, *thumb, *file_name, *mime_type, *file_size;

        file_id = json_object_get(panimation,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        thumb = json_object_get(panimation,"thumb");
        object->thumb = photo_size_parse(thumb);

        file_name = json_object_get(panimation,"file_name");
        object->file_name = alloc_string(json_string_value(file_name));

        mime_type = json_object_get(panimation,"mime_type");
        object->mime_type = alloc_string(json_string_value(mime_type));

        file_size = json_object_get(panimation,"file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }

    return NULL;
}

Game * game_parse(json_t *json){
    Game *object = NULL;
    json_t * pgame = json;

    if(json_is_object(pgame)){
        object = (Game *) calloc(1, sizeof(Game));
        if(!object)
            return NULL;

        json_t *title, *description, *photo, *text, *text_entities, *animation;

        title = json_object_get(pgame,"title");
        object->title = alloc_string(json_string_value(title));

        description = json_object_get(pgame,"description");
        object->description = alloc_string(json_string_value(description));

        photo = json_object_get(pgame,"photo");
        object->photo = photo_size_parse(photo);

        text = json_object_get(pgame,"text");
        object->text = alloc_string(json_string_value(text));

        text_entities = json_object_get(pgame,"text_entities");
        object->text_entities = message_entity_parse(text_entities);

        animation = json_object_get(pgame,"animation");
        object->animation = animation_parse(animation);

        return object;
    }

    return NULL;
}

Sticker * sticker_parse(json_t *json){
    Sticker *object = NULL;
    json_t * psticker = json;

    if(json_is_object(psticker)){
        object = (Sticker *) calloc(1, sizeof(Sticker));
        if(!object)
            return NULL;

        json_t *file_id, *width, *height, *thumb, *emoji, *file_size;

        file_id = json_object_get(psticker,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        width = json_object_get(psticker,"width");
        object->width = (int)json_integer_value(width);

        height = json_object_get(psticker,"height");
        object->height = (int)json_integer_value(height);

        thumb = json_object_get(psticker,"thumb");
        object->thumb = photo_size_parse(thumb);

        emoji = json_object_get(psticker,"emoji");
        object->emoji = alloc_string(json_string_value(emoji));

        file_size = json_object_get(psticker,"file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }

    return NULL;
}

Video * video_parse(json_t *json){
    Video *object = NULL;
    json_t * pvideo = json;

    if(json_is_object(pvideo)){
        object = (Video *) calloc(1, sizeof(Video));
        if(!object)
            return NULL;

        json_t *file_id, *width, *height, *duration, *thumb, *mime_type, *file_size;

        file_id = json_object_get(pvideo,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        width = json_object_get(pvideo,"width");
        object->width = (int)json_integer_value(width);

        height = json_object_get(pvideo,"height");
        object->height = (int)json_integer_value(height);

        duration = json_object_get(pvideo,"duration");
        object->duration = json_integer_value(duration);

        thumb = json_object_get(pvideo,"thumb");
        object->thumb = photo_size_parse(thumb);

        mime_type = json_object_get(pvideo,"mime_type");
        object->mime_type = alloc_string(json_string_value(mime_type));

        file_size = json_object_get(pvideo,"file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }

    return NULL;
}

Voice * voice_parse(json_t *json){
    Voice *object = NULL;
    json_t * pvoice = json;

    if(json_is_object(pvoice)){
        object = (Voice *) calloc(1, sizeof(Voice));
        if(!object)
            return NULL;

        json_t *file_id, *duration, *mime_type, *file_size;

        file_id = json_object_get(pvoice,"file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        duration = json_object_get(pvoice,"duration");
        object->duration = json_integer_value(duration);

        mime_type = json_object_get(pvoice,"mime_type");
        object->mime_type = alloc_string(json_string_value(mime_type));

        file_size = json_object_get(pvoice,"file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }

    return NULL;
}

Contact * contact_parse(json_t *json){
    Contact *object = NULL;
    json_t * pcontact = json;

    if(json_is_object(pcontact)){
        object = (Contact *) calloc(1, sizeof(Contact));
        if(!object)
            return NULL;

        json_t *phone_number, *first_name, *last_name, *user_id;

        phone_number = json_object_get(pcontact,"phone_number");
        object->phone_number = alloc_string(json_string_value(phone_number));

        first_name = json_object_get(pcontact,"first_name");
        object->first_name = alloc_string(json_string_value(first_name));

        last_name = json_object_get(pcontact,"last_name");
        object->last_name = alloc_string(json_string_value(last_name));

        user_id = json_object_get(pcontact,"user_id");
        object->user_id = json_integer_value(user_id);

        return object;
    }

    return NULL;
}

Location * location_parse(json_t *json){
    Location *object = NULL;
    json_t * plocation = json;

    if(json_is_object(plocation)){
        object = (Location *) calloc(1, sizeof(Location));
        if(!object)
            return NULL;

        json_t *latitude, *longitude;

        latitude = json_object_get(plocation,"latitude");
        object->latitude = json_real_value(latitude);

        longitude = json_object_get(plocation,"longitude");
        object->longitude = json_real_value(longitude);

        return object;
    }

    return NULL;
}

Venue * venue_parse(json_t *json){
    Venue *object = NULL;
    json_t * pvenue = json;

    if(json_is_object(pvenue)){
        object = (Venue *) calloc(1, sizeof(Venue));
        if(!object)
            return NULL;

        json_t *location, *title, *address, *foursquare_id;

        location = json_object_get(pvenue,"location");
        object->location = location_parse(location);

        title = json_object_get(pvenue,"title");
        object->title = alloc_string(json_string_value(title));

        address = json_object_get(pvenue,"address");
        object->address = alloc_string(json_string_value(address));

        foursquare_id = json_object_get(pvenue,"foursquare_id");
        object->foursquare_id = alloc_string(json_string_value(foursquare_id));

        return object;
    }

    return NULL;
}

ChosenInlineResult * chosen_inline_result_parse(json_t * json){
    ChosenInlineResult *object = NULL;
    json_t * pcir = json;

    if(json_is_object(pcir)){
        object = (ChosenInlineResult *) calloc(1, sizeof(ChosenInlineResult));
        if(!object)
            return NULL;

        json_t *result_id, *from, *location, *inline_message_id, *query;

        result_id = json_object_get(pcir, "result_id");
        object->result_id = alloc_string(json_string_value(result_id));

        from = json_object_get(pcir, "from");
        object->from = user_parse(from);

        location = json_object_get(pcir, "location");
        object->location = location_parse(location);

        inline_message_id = json_object_get(pcir, "inline_message_id");
        object->inline_message_id = alloc_string(json_string_value(inline_message_id));

        query = json_object_get(pcir, "query");
        object->query = alloc_string(json_string_value(query));

        return object;
    }

    return NULL;
}

Message * message_parse(json_t *json){
    Message *message = NULL;
    json_t * pmessage = json;
    size_t length, i;

    if(json_is_object(pmessage)){
        message = (Message *) calloc(1,  sizeof( Message ));
        if(!message)
            return NULL;

        //Numbers
        json_t *message_id, *date, *forward_from_message_id, *forward_date,
        *edit_date, *delete_chat_photo, *group_chat_created, *supergroup_chat_created,
        *channel_chat_created, *migrate_to_chat_id, *migrate_from_chat_id;

        message_id = json_object_get( pmessage, "message_id" );
        message->message_id = json_integer_value( message_id );

        date = json_object_get( pmessage, "date" );
        message->date = json_integer_value( date );

        forward_from_message_id = json_object_get( pmessage, "forward_from_message_id" );
        message->forward_from_message_id = json_integer_value( forward_from_message_id );

        forward_date = json_object_get( pmessage, "forward_date" );
        message->forward_date = json_integer_value( forward_date );

        edit_date = json_object_get( pmessage, "edit_date" );
        message->edit_date = json_integer_value( edit_date );

        delete_chat_photo = json_object_get( pmessage, "delete_chat_photo" );
        message->delete_chat_photo = json_boolean_value( delete_chat_photo );

        group_chat_created = json_object_get( pmessage, "group_chat_created" );
        message->group_chat_created = json_boolean_value( group_chat_created );

        supergroup_chat_created = json_object_get( pmessage, "supergroup_chat_created" );
        message->supergroup_chat_created = json_boolean_value( supergroup_chat_created );

        channel_chat_created = json_object_get( pmessage, "channel_chat_created" );
        message->channel_chat_created = json_boolean_value( channel_chat_created );

        migrate_to_chat_id = json_object_get( pmessage, "migrate_to_chat_id" );
        message->migrate_to_chat_id = json_integer_value( migrate_to_chat_id );

        migrate_from_chat_id = json_object_get( pmessage, "migrate_from_chat_id" );
        message->migrate_from_chat_id = json_integer_value( migrate_from_chat_id );

        //Strings
        json_t *text, *caption, *new_chat_title, *forward_signature,
        *media_group_id, *author_signature, *connected_website;

        text = json_object_get( pmessage, "text" );
        message->text = alloc_string( json_string_value( text ));

        caption = json_object_get( pmessage, "caption" );
        message->caption = alloc_string( json_string_value( caption ));

        new_chat_title = json_object_get( pmessage, "new_chat_title" );
        message->new_chat_title = alloc_string( json_string_value( new_chat_title ));

        forward_signature = json_object_get( pmessage, "forward_signature" );
        message->forward_signature = alloc_string( json_string_value( forward_signature));

        media_group_id = json_object_get( pmessage, "media_group_id" );
        message->media_group_id = alloc_string( json_string_value( media_group_id ));

        author_signature = json_object_get( pmessage, "author_signature" );
        message->author_signature = alloc_string( json_string_value( author_signature ));

        connected_website = json_object_get( pmessage, "connected_website" );
        message->connected_website = alloc_string( json_string_value( connected_website ));

        //Arrays
        json_t *entities, *photo, *new_chat_photo, *caption_entities,
        *new_chat_members;

        entities = json_object_get( pmessage, "entities" );
        length = json_array_size( entities );
        MessageEntity * oentities = NULL, *_temp_e = NULL;
        oentities = message_entity_parse( json_array_get(entities, 0));
        if (length > 0) {
            for (i = 1; i < length; i++) {
                _temp_e = message_entity_parse(json_array_get(entities, i));
                if (_temp_e)
                    message_entity_add(oentities, _temp_e);
            }
        }
        message->entities = oentities;

        photo = json_object_get( pmessage, "photo" );
        length = json_array_size(photo);
        PhotoSize * ophoto = NULL, *_temp_p = NULL;
        ophoto = photo_size_parse(json_array_get(photo, 0));
        if (length > 0) {
            for (i = 1; i < length; i++) {
                _temp_p = photo_size_parse(json_array_get(photo, i));
                if (_temp_p)
                    photo_size_add(ophoto, _temp_p);
            }
        }
        message->photo = ophoto;

        new_chat_photo = json_object_get( pmessage, "new_chat_photo" );
        length = json_array_size(new_chat_photo);
        PhotoSize * onew_chat_photo = NULL, *_temp_ncp = NULL;
        onew_chat_photo = photo_size_parse(json_array_get(new_chat_photo, 0));
        if (length > 0) {
            for (i = 1; i < length; i++) {
                _temp_ncp = photo_size_parse(json_array_get(new_chat_photo, i));
                if (_temp_ncp)
                    photo_size_add(onew_chat_photo, _temp_ncp);
            }
        }
        message->new_chat_photo= onew_chat_photo;

        caption_entities = json_object_get( pmessage, "caption_entities" );
        length = json_array_size(caption_entities);
        MessageEntity * ocaption_entities = NULL, *_temp_ce = NULL;
        ocaption_entities = message_entity_parse(json_array_get(caption_entities, 0));
        if (length > 0) {
            for (i = 1; i < length; i++) {
                _temp_ce = message_entity_parse(json_array_get(caption_entities, i));
                if (_temp_ce)
                    message_entity_add(ocaption_entities, _temp_ce);
            }
        }
        message->caption_entities = ocaption_entities;

        new_chat_members = json_object_get( pmessage, "new_chat_members" );
        length = json_array_size(new_chat_members);
        User * onew_chat_members = NULL, *_temp_u = NULL;
        onew_chat_members = user_parse(json_array_get(new_chat_members, 0));
        if (length > 0) {
            for (i = 1; i < length; i++) {
                _temp_u = user_parse(json_array_get(new_chat_members, i));
                if (_temp_u)
                    user_add(onew_chat_members, _temp_u);
            }
        }
        message->new_chat_members = onew_chat_members;

        //Objects
        json_t *from, *chat, *forward_from, *forward_from_chat, *reply_to_message, 
        *audio, *document, *game, *sticker, *video, *voice, *video_note, *contact, 
        *location, *venue, *left_chat_member, *pinned_message, 
        *invoice, *successful_payment;

        from = json_object_get( pmessage, "from" );
        message->from = user_parse(from);

        chat = json_object_get( pmessage, "chat" );
        message->chat = chat_parse(chat);

        forward_from = json_object_get( pmessage, "forward_from" );
        message->forward_from = user_parse(forward_from);

        forward_from_chat = json_object_get( pmessage, "forward_from_chat" );
        message->forward_from_chat = chat_parse(forward_from_chat);

        reply_to_message = json_object_get( pmessage, "reply_to_message" );
        message->reply_to_message = message_parse(reply_to_message);

        audio = json_object_get( pmessage, "audio" );
        message->audio = audio_parse(audio);

        document = json_object_get( pmessage, "document" );
        message->document = document_parse(document);

        game = json_object_get( pmessage, "game" );
        message->game = game_parse(game);

        sticker = json_object_get( pmessage, "sticker" );
        message->sticker = sticker_parse(sticker);

        video = json_object_get( pmessage, "video" );
        message->video = video_parse(video);

        voice = json_object_get( pmessage, "voice" );
        message->voice = voice_parse(voice);

        video_note = json_object_get( pmessage, "video_note" );
        message->video_note = video_note_parse(video_note);

        contact = json_object_get( pmessage, "contact" );
        message->contact = contact_parse(contact);

        location = json_object_get( pmessage, "location" );
        message->location = location_parse(location);

        venue = json_object_get( pmessage, "venue" );
        message->venue = venue_parse(venue);

        left_chat_member = json_object_get( pmessage, "left_chat_member" );
        message->left_chat_member = user_parse(left_chat_member);

        pinned_message = json_object_get( pmessage, "pinned_message" );
        message->pinned_message = message_parse(pinned_message);

        invoice = json_object_get( pmessage, "invoice" );
        message->invoice = invoice_parse(invoice);

        successful_payment = json_object_get( pmessage, "successful_payment" );
        message->successful_payment = successful_payment_parse(successful_payment);

        return message;
    }
    return NULL;
}

Update * update_parse(json_t *json){
    Update *object = NULL;
    json_t * pupdate = json;

    if(json_is_object(pupdate)){
        object = (Update *)  calloc(1, sizeof(Update));
        if(!object)
            return NULL;

        json_t *update_id, *message, *edited_message, *channel_post,
        *edited_channel_post, *inline_query, *chosen_inline_result,
        *callback_query, *shipping_query, *pre_checkout_query;

        update_id = json_object_get(pupdate,"update_id");
        object->update_id = json_integer_value(update_id);

        message = json_object_get(pupdate,"message");
        object->message = message_parse(message);

        edited_message = json_object_get(pupdate,"edited_message");
        object->edited_message = message_parse(edited_message);

        channel_post = json_object_get(pupdate,"channel_post");
        object->channel_post = message_parse(channel_post);

        edited_channel_post = json_object_get(pupdate,"edited_channel_post");
        object->edited_channel_post = message_parse(edited_channel_post);

        inline_query = json_object_get(pupdate,"inline_query");
        object->inline_query = inline_query_parse(inline_query);

        chosen_inline_result = json_object_get(pupdate,"choosen_inline_result");
        object->chosen_inline_result = chosen_inline_result_parse(chosen_inline_result);

        callback_query = json_object_get(pupdate,"callback_query");
        object->callback_query = callback_query_parse(callback_query);

        shipping_query = json_object_get(pupdate, "shipping_query");
        object->shipping_query = shipping_query_parse(shipping_query);

        pre_checkout_query = json_object_get(pupdate, "pre_checkout_query");
        object->pre_checkout_query = pre_checkout_query_parse(pre_checkout_query);

        object->next = NULL;

        return object;
    }

    return NULL;
}

ChatMember *chat_member_parse (json_t *json) {
    ChatMember *object = NULL;

    if (json_is_object(json)) {
        object = (ChatMember *) calloc(1, sizeof(ChatMember));
        if(!object)
            return NULL;

        json_t *user, *status, *until_date, *can_be_edited,
               *can_change_info, *can_post_messages, *can_edit_messages,
               *can_delete_messages, *can_invite_users, *can_restrict_members,
               *can_pin_messages, *can_promote_members, *can_send_messages,
               *can_send_media_messages, *can_send_other_messages, *can_add_web_page_previews;
               
        user         = json_object_get(json, "user");
        object->user = user_parse(user);

        status         = json_object_get(json, "status");
        object->status = alloc_string(json_string_value(status));

        until_date = json_object_get(json, "until_date");
        object->until_date = json_integer_value(until_date);

        can_be_edited         = json_object_get(json, "can_be_edited");
        object->can_be_edited = json_boolean_value(can_be_edited);

        can_change_info         = json_object_get(json, "can_change_info");
        object->can_change_info = json_boolean_value(can_change_info);

        can_post_messages         = json_object_get(json, "can_post_messages");
        object->can_post_messages = json_boolean_value(can_post_messages);

        can_edit_messages         = json_object_get(json, "can_edit_messages");
        object->can_edit_messages = json_boolean_value(can_edit_messages);

        can_delete_messages         = json_object_get(json, "can_delete_messages");
        object->can_delete_messages = json_boolean_value(can_delete_messages);

        can_invite_users         = json_object_get(json, "can_invite_users");
        object->can_invite_users = json_boolean_value(can_invite_users);

        can_restrict_members         = json_object_get(json, "can_restrict_members");
        object->can_restrict_members = json_boolean_value(can_restrict_members);

        can_pin_messages         = json_object_get(json, "can_pin_messages");
        object->can_pin_messages = json_boolean_value(can_pin_messages);

        can_promote_members         = json_object_get(json, "can_promote_members");
        object->can_promote_members = json_boolean_value(can_promote_members);

        can_send_messages         = json_object_get(json, "can_send_messages");
        object->can_send_messages = json_boolean_value(can_send_messages);

        can_send_media_messages =
                        json_object_get(json, "can_send_media_messages");
        object->can_send_media_messages = json_boolean_value(can_send_media_messages);

        can_send_other_messages =
                        json_object_get(json, "can_send_other_messages");
        object->can_send_other_messages = json_boolean_value(can_send_other_messages);

        can_add_web_page_previews =
                        json_object_get(json, "can_add_web_page_previews");
        object->can_add_web_page_previews = json_boolean_value(can_add_web_page_previews);
        
        object->next = NULL;

        return object;
    }

    return NULL;
}

ChatMember *chat_member_array_parse (json_t *cm_array) {
    ChatMember *object = NULL;   

    size_t i, sz = json_array_size(cm_array);

    if(sz > 0){
        object = chat_member_parse(json_array_get(cm_array, 0));
        for (i = 1; i < sz; i++) {
            chat_member_add(object, chat_member_parse(json_array_get(cm_array, i)));
        }

        return object;
    }
    
    return NULL;
}

InlineQuery * inline_query_parse(json_t * json){
    InlineQuery *object = NULL;

    if (json_is_object(json)) {
        object = (InlineQuery *) calloc(1, sizeof(InlineQuery));
        if(!object)
            return NULL;

        json_t *id, *from, *location, *query, *offset;

        id = json_object_get(json, "id");
        object->id = alloc_string(json_string_value(id));

        from = json_object_get(json, "from");
        object->from = user_parse(from);

        location = json_object_get(json, "location");
        object->location = location_parse(location);

        query = json_object_get(json, "query");
        object->query = alloc_string(json_string_value(query));

        offset = json_object_get(json, "offset");
        object->offset = alloc_string(json_string_value(offset));

        return object;
    }

    return NULL;
}

CallbackQuery * callback_query_parse(json_t * json){
    CallbackQuery *object = NULL;

    if(json_is_object(json)){
        object = (CallbackQuery *) calloc(1, sizeof(CallbackQuery));
        if(!object)
            return NULL;

        json_t *id, *from, *message, *inline_message_id, *chat_instance, *data, *game_short_name;

        id = json_object_get(json , "id");
        object->id = alloc_string(json_string_value(id));

        from = json_object_get(json , "from");
        object->from = user_parse(from);

        message = json_object_get(json, "message");
        object->message = message_parse(message);

        inline_message_id = json_object_get(json, "inline_message_id");
        object->inline_message_id = alloc_string(json_string_value(inline_message_id));

        chat_instance = json_object_get(json, "chat_instance");
        object->chat_instance = alloc_string(json_string_value(chat_instance));

        data = json_object_get(json, "data");
        object->data = alloc_string(json_string_value(data));

        game_short_name = json_object_get(json, "game_short_name");
        object->game_short_name = alloc_string(json_string_value(game_short_name));

        return object;
    }

    return NULL;
}

VideoNote * video_note_parse(json_t * json){
    VideoNote *object = NULL;

    if(json_is_object(json)){
        object = (VideoNote *) calloc(1, sizeof(VideoNote));
        if(!object)
            return NULL;

        json_t *file_id, *length, *duration, *thumb, *file_size;

        file_id = json_object_get(json, "file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        length = json_object_get(json, "length");
        object->length = json_integer_value(length);

        duration = json_object_get(json, "duration");
        object->duration = json_integer_value(duration);

        thumb = json_object_get(json, "thumb");
        object->thumb = photo_size_parse(thumb);

        file_size = json_object_get(json, "file_size");
        object->file_size = json_integer_value(file_size);

        return object;
    }

    return NULL;
}

ShippingQuery * shipping_query_parse(json_t * json){
    ShippingQuery *object = NULL;

    if(json_is_object(json)){
        object = (ShippingQuery *) calloc(1, sizeof(ShippingQuery));
        if(!object)
            return NULL;

        json_t *id, *from, *invoice_payload, *shipping_address;

        id = json_object_get(json, "id");
        object->id = alloc_string(json_string_value(id));

        from = json_object_get(json, "from");
        object->from = user_parse(from);

        invoice_payload = json_object_get(json, "invoice_payload");
        object->invoice_payload = alloc_string(json_string_value(invoice_payload));

        shipping_address = json_object_get(json, "shipping_address");
        object->shipping_address = shipping_address_parse(shipping_address);

        return object;
    }

    return NULL;
}

Invoice * invoice_parse(json_t * json){
    Invoice *object = NULL;

    if(json_is_object(json)){
        object = (Invoice *) calloc(1, sizeof(Invoice));
        if(!object)
            return NULL;

        json_t *title, *description, * start_parameter, *currency, *total_amount;

        title = json_object_get(json, "invoice");
        object->title = alloc_string(json_string_value(title));

        description = json_object_get(json, "description");
        object->description = alloc_string(json_string_value(description));

        start_parameter = json_object_get(json, "start_parameter");
        object->start_parameter = alloc_string(json_string_value(start_parameter));

        currency = json_object_get(json, "currency");
        object->currency = alloc_string(json_string_value(currency));

        total_amount = json_object_get(json, "total_amount");
        object->total_amount = json_integer_value(total_amount);

        return object;
    }

    return NULL;
}

ShippingAddress * shipping_address_parse(json_t * json){
    ShippingAddress *object = NULL;

    if(json_is_object(json)){
        object = (ShippingAddress *) calloc(1, sizeof(ShippingAddress));
        if(!object)
            return NULL;

        json_t *country_code, *state, *city, *street_line1, *street_line2, *post_code;

        country_code = json_object_get(json, "country_code");
        object->country_code = alloc_string(json_string_value(country_code));

        state = json_object_get(json, "state");
        object->state = alloc_string(json_string_value(state));

        city = json_object_get(json, "city");
        object->city = alloc_string(json_string_value(city));

        street_line1 = json_object_get(json, "street_line1");
        object->street_line1 = alloc_string(json_string_value(street_line1));

        street_line2 = json_object_get(json, "street_line2");
        object->street_line2 = alloc_string(json_string_value(street_line2));

        post_code = json_object_get(json, "post_code");
        object->post_code = alloc_string(json_string_value(post_code));

        return object;
    }

    return NULL;
}

PreCheckoutQuery * pre_checkout_query_parse(json_t * json){
    PreCheckoutQuery *object = NULL;

    if(json_is_object(json)){
        object = (PreCheckoutQuery *) calloc(1, sizeof(PreCheckoutQuery));
        if(!object)
            return NULL;

        json_t *id, *from, *currency, *total_amount, *invoice_payload,
        *shipping_option_id, *order_info;

        id = json_object_get(json, "id");
        object->id = alloc_string(json_string_value(id));

        from = json_object_get(json, "from");
        object->from = user_parse(from);

        currency = json_object_get(json, "currency");
        object->currency = alloc_string(json_string_value(currency));

        total_amount = json_object_get(json, "total_amount");
        object->total_amount = json_integer_value(total_amount);

        invoice_payload = json_object_get(json, "invoice_payload");
        object->invoice_payload = alloc_string(json_string_value(invoice_payload));

        shipping_option_id = json_object_get(json, "shipping_option_id");
        object->shipping_option_id = alloc_string(json_string_value(shipping_option_id));

        order_info = json_object_get(json, "order_info");
        object->order_info = order_info_parse(order_info);

        return object;
    }

    return NULL;
}

OrderInfo * order_info_parse(json_t * json){
    OrderInfo *object = NULL;

    if(json_is_object(json)){
        object = (OrderInfo *) calloc(1, sizeof(OrderInfo));
        if(!object)
            return NULL;
        
        json_t *name, *phone_number, *email, *shipping_address;

        name = json_object_get(json, "name");
        object->name = alloc_string(json_string_value(name));

        phone_number = json_object_get(json, "phone_number");
        object->phone_number = alloc_string(json_string_value(phone_number));

        email = json_object_get(json, "email");
        object->email = alloc_string(json_string_value(email));

        shipping_address = json_object_get(json, "shipping_address");
        object->shipping_address = shipping_address_parse(shipping_address);

        return object;
    }

    return NULL;
}

SuccessfulPayment * successful_payment_parse(json_t * json){
    SuccessfulPayment *object = NULL;

    if(json_is_object(json)){
        object = (SuccessfulPayment *) calloc(1, sizeof(SuccessfulPayment));
        if(!object)
            return NULL;

        json_t *currency, *total_amount, *invoice_payload, *shipping_option_id,
        *order_info, *telegram_payment_charge_id, *provider_payment_charge_id;

        currency = json_object_get(json, "currency");
        object->currency = alloc_string(json_string_value(currency));

        total_amount = json_object_get(json, "total_amount");
        object->total_amount = json_integer_value(total_amount);

        invoice_payload = json_object_get(json, "invoice_payload");
        object->invoice_payload = alloc_string(json_string_value(invoice_payload));

        shipping_option_id = json_object_get(json, "shipping_option_id");
        object->shipping_option_id = alloc_string(json_string_value(shipping_option_id));

        order_info = json_object_get(json, "order_info");
        object->order_info = order_info_parse(order_info);

        telegram_payment_charge_id = json_object_get(json, "telegram_payment_charge_id");
        object->telegram_payment_charge_id = alloc_string(json_string_value(telegram_payment_charge_id));

        provider_payment_charge_id = json_object_get(json, "provider_payment_charge_id");
        object->provider_payment_charge_id = alloc_string(json_string_value(provider_payment_charge_id));

        return object;
    }

    return NULL;
}

File * file_parse(json_t * json){
    File *object = NULL;

    if(json_is_object(json)){
        object = (File *) calloc(1, sizeof(File));
        if(!object)
            return NULL;

        json_t *file_id, *file_size, *file_path;

        file_id = json_object_get(json, "file_id");
        object->file_id = alloc_string(json_string_value(file_id));

        file_size = json_object_get(json, "file_size");
        object->file_size = json_integer_value(file_size);

        file_path = json_object_get(json, "file_path");
        object->file_path = alloc_string(json_string_value(file_path));

        return object;
    }

    return NULL;
}

UserProfilePhotos * user_profile_photos_parse(json_t * json){
    UserProfilePhotos *object = NULL;

    if(json_is_object(json)){
        object = (UserProfilePhotos *) calloc(1, sizeof(UserProfilePhotos));
        if(!object)
            return NULL;

        json_t *total_count, *photos, *array_photos;
        size_t length_i, i, length_x, x;

        total_count = json_object_get(json, "total_count");

        PhotoSize ** ophotos = NULL, *_temp = NULL;
        photos = json_object_get(json, "photos");
        length_i = json_array_size(photos);

        /* Array of Array PhotoSize */
        if (length_i > 0) {
            ophotos = (PhotoSize **) calloc(length_i, sizeof(PhotoSize));
            for (i = 0; i < length_i; i++) {
                array_photos = json_array_get(photos, i);
                length_x = json_array_size(array_photos);

                if(length_x > 0){
                    ophotos[i] = photo_size_parse(json_array_get(array_photos, 0));

                    for(x = 1; x < length_x; x++){
                        _temp = photo_size_parse(json_array_get(array_photos, x));
                        if(_temp)
                            photo_size_add(ophotos[i], _temp);
                    }

                }

            }
        }

        object->total_count = json_integer_value(total_count);
        object->photos = ophotos;

        return object;
    }

    return NULL;
}


ChatPhoto * chat_photo_parse(json_t * json){
    ChatPhoto *object = NULL;

    if(json_is_object(json)){
        object = (ChatPhoto *) calloc(1, sizeof(ChatPhoto));
        if(!object)
            return NULL;

        json_t *small_file_id, *big_file_id;

        small_file_id = json_object_get(json, "small_file_id");
        object->small_file_id = alloc_string(json_string_value(small_file_id));

        big_file_id   = json_object_get(json, "big_file_id");
        object->big_file_id = alloc_string(json_string_value(big_file_id));

        return object;
    }

    return NULL;
}
