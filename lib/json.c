#include <telebot.h>

static long int valid_update_id;

json_t * load(char *json){
    json_t *pload;
    json_error_t error;

    pload = json_loads(json, 0, &error);

    if(pload)
        return pload;

    return NULL;
}

User * user_parse(json_t *json){

    json_t *puser = json;

    if(json_is_object(puser)){
        json_t *id, *is_bot, *first_name, *last_name, *username, *language_code;

        id = json_object_get(puser, "id");
        is_bot = json_object_get(puser, "is_bot");
        first_name = json_object_get(puser, "first_name");
        last_name = json_object_get(puser, "last_name");
        username = json_object_get(puser, "username");
        language_code = json_object_get(puser, "language_code");

        User * ouser = user(json_integer_value(id), json_is_true(is_bot),
                            json_string_value(first_name), json_string_value(last_name),
                            json_string_value(username), json_string_value(language_code));

        return ouser;
    }

    return NULL;
}

Chat * chat_parse(json_t *json){
    json_t * pchat = json;

    if(json_is_object(pchat)){
        json_t *id, *type, *title, *username, *first_name,
        *last_name, *all_members_are_administrators;

        id = json_object_get(pchat,"id");
        type = json_object_get(pchat,"type");
        title = json_object_get(pchat,"title");
        username = json_object_get(pchat,"username");
        first_name = json_object_get(pchat,"first_name");
        last_name = json_object_get(pchat,"last_name");
        all_members_are_administrators = json_object_get(pchat,"all_members_are_administrators");

        Chat * ochat = chat(json_integer_value(id), json_string_value(type),
                            json_string_value(title), json_string_value(username),
                            json_string_value(first_name), json_string_value(last_name),
                            json_boolean_value(all_members_are_administrators));

        return ochat;
    }
    return NULL;
}

MessageEntity * message_entity_parse(json_t *json){
    json_t * pmessage_entity = json;

    if(json_is_object(pmessage_entity)){
        json_t *type, *offset, *length, *url, *user;

        type = json_object_get(pmessage_entity,"type");
        offset = json_object_get(pmessage_entity,"offset");
        length = json_object_get(pmessage_entity,"length");
        url = json_object_get(pmessage_entity,"url");

        user = json_object_get(pmessage_entity,"user");

        User * puser = user_parse(user);
        MessageEntity * omessage_entity = message_entity(json_string_value(type), json_integer_value(offset),
                                                         json_integer_value(length), json_string_value(url), puser);

        return omessage_entity;
    }

    return NULL;
}

Audio * audio_parse(json_t *json){
    json_t * paudio = json;

    if(json_is_object(paudio)){
        json_t *file_id, *duration, *performer, *title, *mime_type, *file_size;

        file_id = json_object_get(paudio,"file_id");
        duration = json_object_get(paudio,"duration");
        performer = json_object_get(paudio,"performer");
        title = json_object_get(paudio,"title");
        mime_type = json_object_get(paudio,"mime_type");
        file_size = json_object_get(paudio,"file_size");

        Audio * oaudio = audio(json_string_value(file_id), json_integer_value(duration),
                               json_string_value(performer), json_string_value(title),
                               json_string_value(mime_type), json_integer_value(file_size));

        return oaudio;
    }
    return NULL;
}

PhotoSize * photo_size_parse(json_t *json) {
    json_t * pphoto_size = json;

    if(json_is_object(pphoto_size) && image_is_activated()) {
        json_t *file_id, *width, *height, *file_size;

        file_id = json_object_get(pphoto_size,"file_id");
        width = json_object_get(pphoto_size,"width");
        height = json_object_get(pphoto_size,"height");
        
        file_size = json_object_get(pphoto_size,"file_size");
        if(!image_size(json_integer_value(file_size)))
            return NULL;

        PhotoSize * ophoto_size = photo_size(json_string_value(file_id), json_integer_value(width),
                                             json_integer_value(height), json_integer_value(file_size));

        return ophoto_size;
    }

    return NULL;
}

Document * document_parse(json_t *json){
    json_t * pdocument = json;

    if(json_is_object(pdocument)){
        json_t *file_id, *thumb, *file_name, *mime_type, *file_size;

        file_id = json_object_get(pdocument,"file_id");
        thumb = json_object_get(pdocument,"thumb");
        file_name = json_object_get(pdocument,"file_name");

        mime_type = json_object_get(pdocument,"mime_type");
        if(!format_type(json_string_value(mime_type)))
            return NULL;

        file_size = json_object_get(pdocument,"file_size");

        PhotoSize * othumb = photo_size_parse(thumb);
        Document * odocument = document(json_string_value(file_id), othumb, json_string_value(file_name),
                                            json_string_value(mime_type), json_integer_value(file_size));

            return odocument;
    }

    return NULL;
}

Animation * animation_parse(json_t *json){
    json_t * panimation = json;

    if(json_is_object(panimation)){
        json_t *file_id, *thumb, *file_name, *mime_type, *file_size;

        file_id = json_object_get(panimation,"file_id");
        thumb = json_object_get(panimation,"thumb");
        file_name = json_object_get(panimation,"file_name");
        mime_type = json_object_get(panimation,"mime_type");
        file_size = json_object_get(panimation,"file_size");

        PhotoSize *othumb = photo_size_parse(thumb);
        Animation *oanimation = (Animation *)document(json_string_value(file_id), othumb, json_string_value(file_name),
                                                      json_string_value(mime_type), json_integer_value(file_size));

        return oanimation;
    }

    return NULL;
}

Game * game_parse(json_t *json){
    json_t * pgame = json;

    if(json_is_object(pgame)){
        json_t *title, *description, *photo, *text, *text_entities, *animation;

        title = json_object_get(pgame,"title");
        description = json_object_get(pgame,"description");
        photo = json_object_get(pgame,"photo");
        text = json_object_get(pgame,"text");
        text_entities = json_object_get(pgame,"text_entities");
        animation = json_object_get(pgame,"animation");

        PhotoSize * ophoto = photo_size_parse(photo);
        MessageEntity * otext_entities = message_entity_parse(text_entities);
        Animation * oanimation = animation_parse(animation);

        Game * ogame = game(json_string_value(title), json_string_value(description), 
                            ophoto, json_string_value(text), otext_entities, oanimation);

        return ogame;
    }
    return NULL;
}

Sticker * sticker_parse(json_t *json){
    json_t * psticker = json;

    if(json_is_object(psticker)){
        json_t *file_id, *width, *height, *thumb, *emoji, *file_size;

        file_id = json_object_get(psticker,"file_id");
        width = json_object_get(psticker,"width");
        height = json_object_get(psticker,"height");
        thumb = json_object_get(psticker,"thumb");
        emoji = json_object_get(psticker,"emoji");
        file_size = json_object_get(psticker,"file_size");

        PhotoSize * othumb = photo_size_parse(thumb);

        Sticker * osticker = sticker(json_string_value(file_id), json_integer_value(width),
                                     json_integer_value(height), othumb, json_string_value(emoji), 
                                     json_integer_value(file_size));

        return osticker;
    }

    return NULL;
}

Video * video_parse(json_t *json){
    json_t * pvideo = json;

    if(json_is_object(pvideo) && video_is_activated() && video_count()){
        json_t *file_id, *width, *height, *duration, *thumb, *mime_type, *file_size;

        file_id = json_object_get(pvideo,"file_id");
        width = json_object_get(pvideo,"width");
        height = json_object_get(pvideo,"height");
        duration = json_object_get(pvideo,"duration");
        thumb = json_object_get(pvideo,"thumb");
        mime_type = json_object_get(pvideo,"mime_type");
        
        file_size = json_object_get(pvideo,"file_size");
        if(video_size(json_integer_value(file_size)))
            return NULL;

        PhotoSize * othumb = photo_size_parse(thumb);

        Video * ovideo = video(json_string_value(file_id), json_integer_value(width),
                               json_integer_value(height), json_integer_value(duration),
                               othumb, json_string_value(mime_type), json_integer_value(file_size));

        return ovideo;
    }

    return NULL;
}

Voice * voice_parse(json_t *json){
    json_t * pvoice = json;

    if(json_is_object(pvoice) && voice_is_activated() && voice_count()){
        json_t *file_id, *duration, *mime_type, *file_size;

        file_id = json_object_get(pvoice,"file_id");
        duration = json_object_get(pvoice,"duration");
        mime_type = json_object_get(pvoice,"mime_type");
        file_size = json_object_get(pvoice,"file_size");
        if(!voice_size(json_integer_value(file_size)))
            return NULL;

        Voice * ovoice = voice(json_string_value(file_id), json_integer_value(duration),
                               json_string_value(mime_type),json_integer_value(file_size));

        return ovoice;
    }

    return NULL;
}

Contact * contact_parse(json_t *json){
    json_t * pcontact = json;

    if(json_is_object(pcontact) && contact_is_activated() && contact_count()){
        json_t *phone_number, *first_name, *last_name, *user_id;

        phone_number = json_object_get(pcontact,"phone_number");
        first_name = json_object_get(pcontact,"first_name");
        last_name = json_object_get(pcontact,"last_name");
        user_id = json_object_get(pcontact,"user_id");

        Contact * ocontact = contact(json_string_value(phone_number),json_string_value(first_name),
                                     json_string_value(last_name),json_integer_value(user_id));

        return ocontact;
    }
    return NULL;
}

Location * location_parse(json_t *json){
    json_t * plocation = json;

    if(json_is_object(plocation)){
        json_t *latitude, *longitude;

        latitude = json_object_get(plocation,"latitude");
        longitude = json_object_get(plocation,"longitude");

        Location * olocation = location(json_real_value(latitude), json_real_value(longitude));

        return olocation;
    }

    return NULL;
}

Venue * venue_parse(json_t *json){
    json_t * pvenue = json;

    if(json_is_object(pvenue)){
        json_t *location, *title, *address, *foursquare_id;

        location = json_object_get(pvenue,"location");
        title = json_object_get(pvenue,"title");
        address = json_object_get(pvenue,"address");
        foursquare_id = json_object_get(pvenue,"foursquare_id");

        Location * olocation = location_parse(location);

        Venue * ovenue = venue(olocation, json_string_value(title), 
                               json_string_value(address), json_string_value(foursquare_id));

        return ovenue;
    }

    return NULL;
}

Message * message_parse(json_t *json){
    json_t * pmessage = json;

    if(json_is_object(pmessage)){
        //Numbers
        json_t *message_id, *date, *forward_from_message_id, *forward_date,
        *edit_date, *delete_chat_photo, *group_chat_created, *supergroup_chat_created,
        *channel_chat_created, *migrate_to_chat_id, *migrate_from_chat_id;

        message_id = json_object_get(pmessage,"message_id");
        date = json_object_get(pmessage,"date");
        forward_from_message_id = json_object_get(pmessage,"forward_from_message_id");
        forward_date = json_object_get(pmessage,"forward_date");
        edit_date = json_object_get(pmessage,"edit_date");
        delete_chat_photo = json_object_get(pmessage,"delete_chat_photo");
        group_chat_created = json_object_get(pmessage,"group_chat_created");
        supergroup_chat_created = json_object_get(pmessage,"supergroup_chat_created");
        channel_chat_created = json_object_get(pmessage,"channel_chat_created");
        migrate_to_chat_id = json_object_get(pmessage,"migrate_to_chat_id");
        migrate_from_chat_id = json_object_get(pmessage,"migrate_from_chat_id");
        //Strings
        json_t *text, *caption, *new_chat_title;

        text = json_object_get(pmessage,"text");
        caption = json_object_get(pmessage,"caption");
        new_chat_title = json_object_get(pmessage,"new_chat_title");

        //Arrays
        json_t *entities, *photo, *new_chat_photo;

        entities = json_object_get(pmessage,"entities");
        MessageEntity * oentities = message_entity_parse(entities);

        photo = json_object_get(pmessage,"photo");
        PhotoSize * ophoto = photo_size_parse(photo);

        new_chat_photo = json_object_get(pmessage,"new_chat_photo");
        PhotoSize * onew_chat_photo = photo_size_parse(new_chat_photo);

        //Objects
        json_t *from, *chat, *forward_from, *forward_from_chat, *reply_to_message, *audio, *document, *game, *sticker, *video, *voice, *contact, *location, *venue, *new_chat_member, *left_chat_member, *pinned_message;

        from = json_object_get(pmessage,"from");
        User * ofrom = user_parse(from);

        chat = json_object_get(pmessage,"chat");
        Chat * ochat = chat_parse(chat);

        forward_from = json_object_get(pmessage,"forward_from");
        User * oforward_from = user_parse(forward_from);

        forward_from_chat = json_object_get(pmessage,"forward_from_chat");
        Chat * oforward_from_chat = chat_parse(forward_from_chat);

        reply_to_message = json_object_get(pmessage,"reply_to_message");
        Message * oreply_to_message = message_parse(reply_to_message);

        audio = json_object_get(pmessage,"audio");
        Audio * oaudio = audio_parse(audio);

        document = json_object_get(pmessage,"document");
        Document * odocument = document_parse(document);

        game = json_object_get(pmessage,"game");
        Game * ogame = game_parse(game);

        sticker = json_object_get(pmessage,"sticker");
        Sticker * osticker = sticker_parse(sticker);

        video = json_object_get(pmessage,"video");
        Video * ovideo = video_parse(video);

        voice = json_object_get(pmessage,"voice");
        Voice * ovoice = voice_parse(voice);

        contact = json_object_get(pmessage,"contact");
        Contact * ocontact = contact_parse(contact);

        location = json_object_get(pmessage,"location");
        Location * olocation = location_parse(location);

        venue = json_object_get(pmessage,"venue");
        Venue * ovenue = venue_parse(venue);

        new_chat_member = json_object_get(pmessage,"new_chat_member");
        User * onew_chat_member = user_parse(new_chat_member);

        left_chat_member = json_object_get(pmessage,"left_chat_member");
        User * oleft_chat_member = user_parse(left_chat_member);

        pinned_message = json_object_get(pmessage,"pinned_message");
        Message * opinned_message = message_parse(pinned_message);

        Message * omessage = message(json_integer_value(message_id), ofrom, json_integer_value(date), 
                                     ochat, oforward_from, oforward_from_chat, json_integer_value(forward_from_message_id), 
                                     json_integer_value(forward_date), oreply_to_message, json_integer_value(edit_date), 
                                     json_string_value(text), oentities, oaudio, odocument, ogame, ophoto, osticker, ovideo, ovoice, 
                                     json_string_value(caption), ocontact, olocation, ovenue, onew_chat_member, oleft_chat_member, 
                                     json_string_value(new_chat_title), onew_chat_photo, json_integer_value(delete_chat_photo), 
                                     json_integer_value(group_chat_created), json_integer_value(supergroup_chat_created), 
                                     json_integer_value(channel_chat_created), json_integer_value(migrate_to_chat_id), 
                                     json_integer_value(migrate_from_chat_id), opinned_message);

        return omessage;
    }
    return NULL;
}

Update * update_parse(json_t *json){
    long int current_update_id;
    json_t * pupdate = json;

    if(json_is_object(pupdate)){
        json_t *update_id, *message, *edited_message, *channel_post, *edited_channel_post, *inline_query, *choosen_inline_result, *callback_query;

        update_id = json_object_get(pupdate,"update_id");
        if(valid_update(json_integer_value(update_id)) == -1)
            return NULL;

        message = json_object_get(pupdate,"message");
        edited_message = json_object_get(pupdate,"edited_message");
        channel_post = json_object_get(pupdate,"channel_post");
        edited_channel_post = json_object_get(pupdate,"edited_channel_post");
        inline_query = json_object_get(pupdate,"inline_query");
        choosen_inline_result = json_object_get(pupdate,"choosen_inline_result");
        callback_query = json_object_get(pupdate,"callback_query");

        Message * omessage = message_parse(message);
        Message * oedited_message = message_parse(edited_message);
        Message * ochannel_post = message_parse(channel_post);
        Message * oedited_channel_post = message_parse(edited_channel_post);

        Update * oupdate = update(  json_integer_value(update_id),
                                  omessage, oedited_message, ochannel_post, 
                                  oedited_channel_post, NULL, NULL, NULL);

        return oupdate;
    }

    return NULL;
}

ChatMember *chat_member_parse (json_t *json) {
    if (json_is_object(json)) {
        json_t *user, *status, *until_date, *can_be_edited,
               *can_change_info, *can_post_messages, *can_edit_messages,
               *can_delete_messages, *can_invite_users, *can_restrict_members,
               *can_pin_messages, *can_promote_members, *can_send_messages,
               *can_send_media_messages, *can_send_other_messages, *can_add_web_page_previews;
               
        user                        = json_object_get(json, "user");
        status                      = json_object_get(json, "status");
        until_date                  = json_object_get(json, "until_date");
        can_be_edited               = json_object_get(json, "can_be_edited");
        can_change_info             = json_object_get(json, "can_change_info");
        can_post_messages           = json_object_get(json, "can_post_messages");
        can_edit_messages           = json_object_get(json, "can_edit_messages");
        can_delete_messages         = json_object_get(json, "can_delete_messages");
        can_invite_users            = json_object_get(json, "can_invite_users");
        can_restrict_members        = json_object_get(json, "can_restrict_members");
        can_pin_messages            = json_object_get(json, "can_pin_messages");
        can_promote_members         = json_object_get(json, "can_promote_members");
        can_send_messages           = json_object_get(json, "can_send_messages");
        can_send_media_messages     = json_object_get(json, "can_send_media_messages");
        can_send_other_messages     = json_object_get(json, "can_send_other_messages");
        can_add_web_page_previews   = json_object_get(json, "can_add_web_page_previews");

        ChatMember *ochatmember = chat_member(user_parse(user), json_string_value(status), json_integer_value(until_date),
            json_boolean_value(can_be_edited), json_boolean_value(can_change_info), json_boolean_value(can_post_messages),
            json_boolean_value(can_edit_messages), json_boolean_value(can_delete_messages), json_boolean_value(can_invite_users),
            json_boolean_value(can_restrict_members), json_boolean_value(can_pin_messages), json_boolean_value(can_promote_members),
            json_boolean_value(can_send_messages), json_boolean_value(can_send_media_messages), json_boolean_value(can_send_other_messages),
            json_boolean_value(can_add_web_page_previews));
        
        return ochatmember;
    }
}

int valid_update(long int update_id){
    static long int update_last_valid = 0;

    if(update_last_valid < update_id){
        update_last_valid = update_id;

        return 1;
    }

    return -1;
}
