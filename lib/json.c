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

static long int valid_update_id;

json_t * start_json(char * json){
    json_t *root, *ok;

    root = load (json);

    if(json_is_object(root)){
        ok = json_object_get(root, "ok");
        if(json_is_true(ok)){
            error_free();
            return json_object_get(root, "result");
        }
        else{
            json_decref(root);
            error_parse(root);
        }
    }

    return NULL;
}

json_t * load(char *json){
    json_t *pload;
    json_error_t error;

    pload = json_loads(json, 0, &error);

    if(pload)
        return pload;

    return NULL;
}

void error_parse(json_t * json){
    if(json_is_object(json)){
        json_t * error_code, *description;

        printf("123456789");

        error_code = json_object_get(json, "error_code");
        description = json_object_get(json, "description");

        error(json_integer_value(error_code), json_string_value(description));
    }
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

        User * o_u = user(
            json_integer_value(id),
            json_is_true(is_bot),
            json_string_value(first_name),
            json_string_value(last_name),
            json_string_value(username),
            json_string_value(language_code)
        );

        return o_u;
    }

    return NULL;
}

Chat * chat_parse(json_t *json){
    json_t * pchat = json;

    if(json_is_object(pchat)){
        json_t *id, *type, *title, *username, *first_name,
        *last_name, *all_members_are_administrators, *photo,
        *description, *invite_link, *pinned_message,
        *sticker_set_name, *can_set_sticker_set;

        id = json_object_get(pchat,"id");
        type = json_object_get(pchat,"type");
        title = json_object_get(pchat,"title");
        username = json_object_get(pchat,"username");
        first_name = json_object_get(pchat,"first_name");
        last_name = json_object_get(pchat,"last_name");
        all_members_are_administrators = json_object_get(pchat,"all_members_are_administrators");
    
        photo = json_object_get(json, "photo");
        ChatPhoto * ochat_photo = chat_photo_parse(photo);

        description = json_object_get(json, "description");
        invite_link = json_object_get(json, "invite_link");
        
        pinned_message = json_object_get(json, "pinned_message");
        Message * opinned_message = message_parse(pinned_message);

        sticker_set_name = json_object_get(json, "sticker_set_name");
        can_set_sticker_set = json_object_get(json, "can_set_sticker_set");

        Chat * o_c = chat(
            json_integer_value(id),
            json_string_value(type),
            json_string_value(title),
            json_string_value(username),
            json_string_value(first_name),
            json_string_value(last_name),
            json_boolean_value(all_members_are_administrators),
            ochat_photo,
            json_string_value(description),
            json_string_value(invite_link),
            opinned_message,
            json_string_value(sticker_set_name),
            json_boolean_value(can_set_sticker_set)
        );

        return o_c;
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

        MessageEntity * o_me = message_entity(
            json_string_value(type),
            json_integer_value(offset),
            json_integer_value(length),
            json_string_value(url),
            puser
        );

        return o_me;
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

        Audio * o_a = audio(
            json_string_value(file_id),
            json_integer_value(duration),
            json_string_value(performer),
            json_string_value(title),
            json_string_value(mime_type),
            json_integer_value(file_size)
        );

        return o_a;
    }
    return NULL;
}

PhotoSize * photo_size_parse(json_t *json) {
    json_t * pphoto_size = json;

    if(json_is_object(pphoto_size) /*&& image_is_activated()*/) {
        json_t *file_id, *width, *height, *file_size;

        file_id = json_object_get(pphoto_size,"file_id");
        width = json_object_get(pphoto_size,"width");
        height = json_object_get(pphoto_size,"height");
        
        file_size = json_object_get(pphoto_size,"file_size");

        /*if(!image_size(json_integer_value(file_size)))
            return NULL;*/

        PhotoSize * o_ps = photo_size(
            json_string_value(file_id),
            json_integer_value(width),
            json_integer_value(height),
            json_integer_value(file_size)
        );

        return o_ps;
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
        /*if(!format_type(json_string_value(mime_type)))
            return NULL;*/

        file_size = json_object_get(pdocument,"file_size");

        PhotoSize * othumb = photo_size_parse(thumb);
        
        Document * o_d = document(
            json_string_value(file_id),
            othumb,
            json_string_value(file_name),
            json_string_value(mime_type),
            json_integer_value(file_size)
        );

            return o_d;
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
        
        Animation *o_a = (Animation *)document(
            json_string_value(file_id),
            othumb,
            json_string_value(file_name),
            json_string_value(mime_type),
            json_integer_value(file_size)
        );

        return o_a;
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

        Game * o_g = game(
            json_string_value(title),
            json_string_value(description),
            ophoto, json_string_value(text),
            otext_entities, oanimation
        );

        return o_g;
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

        Sticker * o_s = sticker(
            json_string_value(file_id),
            json_integer_value(width),
            json_integer_value(height),
            othumb,
            json_string_value(emoji),
            json_integer_value(file_size)
        );

        return o_s;
    }

    return NULL;
}

Video * video_parse(json_t *json){
    json_t * pvideo = json;

    if(json_is_object(pvideo) /*&& video_is_activated() && video_count()*/){
        json_t *file_id, *width, *height, *duration, *thumb, *mime_type, *file_size;

        file_id = json_object_get(pvideo,"file_id");
        width = json_object_get(pvideo,"width");
        height = json_object_get(pvideo,"height");
        duration = json_object_get(pvideo,"duration");
        thumb = json_object_get(pvideo,"thumb");
        mime_type = json_object_get(pvideo,"mime_type");
        
        file_size = json_object_get(pvideo,"file_size");
        /*if(video_size(json_integer_value(file_size)))
            return NULL;*/

        PhotoSize * othumb = photo_size_parse(thumb);

        Video * o_v = video(
            json_string_value(file_id),
            json_integer_value(width),
            json_integer_value(height),
            json_integer_value(duration),
            othumb,
            json_string_value(mime_type),
            json_integer_value(file_size)
        );

        return o_v;
    }

    return NULL;
}

Voice * voice_parse(json_t *json){
    json_t * pvoice = json;

    if(json_is_object(pvoice) /*&& voice_is_activated() && voice_count()*/){
        json_t *file_id, *duration, *mime_type, *file_size;

        file_id = json_object_get(pvoice,"file_id");
        duration = json_object_get(pvoice,"duration");
        mime_type = json_object_get(pvoice,"mime_type");
        file_size = json_object_get(pvoice,"file_size");
        /*if(!voice_size(json_integer_value(file_size)))
            return NULL;*/

        Voice * o_v = voice(
            json_string_value(file_id),
            json_integer_value(duration),
            json_string_value(mime_type),
            json_integer_value(file_size)
        );

        return o_v;
    }

    return NULL;
}

Contact * contact_parse(json_t *json){
    json_t * pcontact = json;

    if(json_is_object(pcontact) /*&& contact_is_activated() && contact_count()*/){
        json_t *phone_number, *first_name, *last_name, *user_id;

        phone_number = json_object_get(pcontact,"phone_number");
        first_name = json_object_get(pcontact,"first_name");
        last_name = json_object_get(pcontact,"last_name");
        user_id = json_object_get(pcontact,"user_id");

        Contact * o_c = contact(
            json_string_value(phone_number),
            json_string_value(first_name),
            json_string_value(last_name),
            json_integer_value(user_id)
        );

        return o_c;
    }
    return NULL;
}

Location * location_parse(json_t *json){
    json_t * plocation = json;

    if(json_is_object(plocation)){
        json_t *latitude, *longitude;

        latitude = json_object_get(plocation,"latitude");
        longitude = json_object_get(plocation,"longitude");

        Location * o_l = location(
            json_real_value(latitude),
            json_real_value(longitude)
        );

        return o_l;
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

        Venue * o_v = venue(
            olocation,
            json_string_value(title),
            json_string_value(address),
            json_string_value(foursquare_id)
        );

        return o_v;
    }

    return NULL;
}

ChosenInlineResult * chosen_inline_result_parse(json_t * json){
    json_t * pcir = json;

    if(json_is_object(pcir)){
        json_t *result_id, *from, *location, *inline_message_id, *query;

        result_id = json_object_get(pcir, "result_id");
        from = json_object_get(pcir, "from");
        location = json_object_get(pcir, "location");
        inline_message_id = json_object_get(pcir, "inline_message_id");
        query = json_object_get(pcir, "query");

        User * ouser = user_parse(from);
        Location * olocation = location_parse(location);

        ChosenInlineResult * o_cir = chosen_inline_result(
            json_string_value(result_id),
            ouser,
            olocation,
            json_string_value(inline_message_id),
            json_string_value(query)
        );

        return o_cir;
    }

    return NULL;
}

Message * message_parse(json_t *json){
    json_t * pmessage = json;
    size_t length, i;

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
        json_t *text, *caption, *new_chat_title, *forward_signature, *author_signature;

        text = json_object_get(pmessage,"text");
        caption = json_object_get(pmessage,"caption");
        new_chat_title = json_object_get(pmessage,"new_chat_title");
        forward_signature = json_object_get(pmessage, "forward_signature");
        author_signature = json_object_get(pmessage, "author_signature");

        //Arrays
        json_t *entities, *photo, *new_chat_photo, *caption_entities;

        entities = json_object_get(pmessage, "entities");
        length = json_array_size(entities);
        MessageEntity * oentities = NULL, *_temp_e = NULL;
        oentities = message_entity_parse(json_array_get(entities, 0));
        if (length > 0) {
            for (i = 1; i < length; i++) {
                _temp_e = message_entity_parse(json_array_get(entities, i));
                if (_temp_e)
                    message_entity_add(oentities, _temp_e);
            }
        }

        photo = json_object_get(pmessage, "photo");
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

        new_chat_photo = json_object_get(pmessage, "new_chat_photo");
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

        caption_entities = json_object_get(pmessage, "caption_entities");
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

        //Objects
        json_t *from, *chat, *forward_from, *forward_from_chat, *reply_to_message, 
        *audio, *document, *game, *sticker, *video, *voice, *video_note, *contact, 
        *location, *venue, *new_chat_member, *left_chat_member, *pinned_message, 
        *invoice, *successful_payment;

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

        video_note = json_object_get(pmessage, "video_note");
        VideoNote * ovideo_note = video_note_parse(video_note);

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

        invoice = json_object_get(pmessage, "invoice");
        Invoice * oinvoice = invoice_parse(invoice);

        successful_payment = json_object_get(pmessage, "successful_payment");
        SuccessfulPayment * osuccessful_payment = successful_payment_parse(successful_payment);

        Message * o_m = message(
            json_integer_value(message_id),
            ofrom,
            json_integer_value(date),
            ochat,
            oforward_from,
            oforward_from_chat,
            json_integer_value(forward_from_message_id),
            json_string_value(forward_signature),
            json_integer_value(forward_date),
            oreply_to_message,
            json_integer_value(edit_date),
            json_string_value(author_signature),
            json_string_value(text),
            oentities,
            ocaption_entities,
            oaudio,
            odocument,
            ogame,
            ophoto,
            osticker,
            ovideo,
            ovoice,
            ovideo_note,
            json_string_value(caption),
            ocontact,
            olocation,
            ovenue,
            onew_chat_member, 
            oleft_chat_member,
            json_string_value(new_chat_title),
            onew_chat_photo, 
            json_integer_value(delete_chat_photo),
            json_integer_value(group_chat_created), 
            json_integer_value(supergroup_chat_created),
            json_integer_value(channel_chat_created), 
            json_integer_value(migrate_to_chat_id),
            json_integer_value(migrate_from_chat_id),
            opinned_message,
            oinvoice,
            osuccessful_payment
        );

        return o_m;
    }
    return NULL;
}

Update * update_parse(json_t *json){
    long int current_update_id;
    json_t * pupdate = json;

    if(json_is_object(pupdate)){
        json_t *update_id, *message, *edited_message, *channel_post,
        *edited_channel_post, *inline_query, *chosen_inline_result,
        *callback_query, *shipping_query, *pre_checkout_query;

        update_id = json_object_get(pupdate,"update_id");
        if(valid_update(json_integer_value(update_id)) == -1)
            return NULL;

        message = json_object_get(pupdate,"message");
        edited_message = json_object_get(pupdate,"edited_message");
        channel_post = json_object_get(pupdate,"channel_post");
        edited_channel_post = json_object_get(pupdate,"edited_channel_post");
        inline_query = json_object_get(pupdate,"inline_query");
        chosen_inline_result = json_object_get(pupdate,"choosen_inline_result");
        callback_query = json_object_get(pupdate,"callback_query");
        shipping_query = json_object_get(pupdate, "shipping_query");
        pre_checkout_query = json_object_get(pupdate, "pre_checkout_query");


        Message * omessage = message_parse(message);
        Message * oedited_message = message_parse(edited_message);
        Message * ochannel_post = message_parse(channel_post);
        Message * oedited_channel_post = message_parse(edited_channel_post);

        InlineQuery * oinline_query = inline_query_parse(inline_query);
        ChosenInlineResult * ochosen_inline_result = chosen_inline_result_parse(chosen_inline_result);
        CallbackQuery * ocallback_query = callback_query_parse(callback_query);
        ShippingQuery * oshipping_query = shipping_query_parse(shipping_query);
        PreCheckoutQuery * opre_checkout_query = pre_checkout_query_parse(pre_checkout_query);


        Update * o_u = update(
            json_integer_value(update_id), omessage,
            oedited_message, ochannel_post,
            oedited_channel_post, oinline_query,
            ochosen_inline_result, ocallback_query,
            oshipping_query, opre_checkout_query
        );

        return o_u;
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

        ChatMember *o_c = chat_member(
            user_parse(user),
            json_string_value(status),
            json_integer_value(until_date),
            json_boolean_value(can_be_edited),
            json_boolean_value(can_change_info),
            json_boolean_value(can_post_messages),
            json_boolean_value(can_edit_messages),
            json_boolean_value(can_delete_messages),
            json_boolean_value(can_invite_users),
            json_boolean_value(can_restrict_members),
            json_boolean_value(can_pin_messages),
            json_boolean_value(can_promote_members),
            json_boolean_value(can_send_messages),
            json_boolean_value(can_send_media_messages), 
            json_boolean_value(can_send_other_messages),
            json_boolean_value(can_add_web_page_previews)
        );
        
        return o_c;
    }
}

ChatMember *chat_member_array_parse (json_t *cm_array) {
    if (json_is_array(cm_array)) {
        size_t i, sz = json_array_size(cm_array);

        ChatMember *cm_temp = chat_member_parse(json_array_get(cm_array, 0));

        for (i = 1; i < sz; i++) {
            chat_member_add(cm_temp, chat_member_parse(json_array_get(cm_array, i)));
        }

        return cm_temp;
    }
    return NULL;
}

InlineQuery * inline_query_parse(json_t * json){
    if (json_is_object(json)) {
        json_t *id, *from, *location, *query, *offset;

        id = json_object_get(json, "id");
        from = json_object_get(json, "from");
        location = json_object_get(json, "location");
        query = json_object_get(json, "query");
        offset = json_object_get(json, "offset");

        User * ouser = user_parse(from);
        Location * olocation = location_parse(location);

        InlineQuery * o_iq = inline_query(
            json_string_value(id),
            ouser, olocation,
            json_string_value(query),
            json_string_value(offset)
        );

        return o_iq;
    }

    return NULL;
}

CallbackQuery * callback_query_parse(json_t * json){
    if(json_is_object(json)){
        json_t *id, *from, *message, *inline_message_id, *chat_instance, *date, *game_short_name;

        id = json_object_get(json , "id");
        from = json_object_get(json , "from");
        message = json_object_get(json, "message");
        inline_message_id = json_object_get(json, "inline_message_id");
        chat_instance = json_object_get(json, "chat_instance");
        date = json_object_get(json, "date");
        game_short_name = json_object_get(json, "game_short_name");

        User * ouser = user_parse(from);
        Message * omessage = message_parse(message);

        CallbackQuery * o_cq = callback_query(
            json_string_value(id), ouser, omessage,
            json_string_value(inline_message_id),
            json_string_value(chat_instance),
            json_string_value(date),
            json_string_value(game_short_name)
        );

        return o_cq;
    }

    return NULL;
}

VideoNote * video_note_parse(json_t * json){
    if(json_is_object(json)){
        json_t *file_id, *length, *duration, *thumb, *file_size;

        file_id = json_object_get(json, "file_id");
        length = json_object_get(json, "length");
        duration = json_object_get(json, "duration");
        thumb = json_object_get(json, "thumb");
        file_size = json_object_get(json, "file_size");

        PhotoSize * othumb = photo_size_parse(thumb);
        VideoNote * o_vn = video_note(
            json_string_value(file_id),
            json_integer_value(length),
            json_integer_value(duration),
            othumb,
            json_integer_value(file_size)
        );

        return o_vn;
    }

    return NULL;
}

bool valid_update(long int update_id){
    static long int update_last_valid = 0;

    if(update_last_valid < update_id){
        update_last_valid = update_id;

        return true;
    }

    return false;
}

ShippingQuery * shipping_query_parse(json_t * json){
    if(json_is_object(json)){
        json_t *id, *from, *invoice_payload, *shipping_address;

        id = json_object_get(json, "id");
        from = json_object_get(json, "from");
        invoice_payload = json_object_get(json, "invoice_payload");
        shipping_address = json_object_get(json, "shipping_address");

        User * ofrom = user_parse(from);
        ShippingAddress * oshipping_address = shipping_address_parse(shipping_address);

        ShippingQuery * o_sq = shipping_query(
            json_string_value(id), ofrom,
            json_string_value(invoice_payload),
            oshipping_address
        );

        return o_sq;
    }

    return NULL;
}

Invoice * invoice_parse(json_t * json){
    if(json_is_object(json)){
        json_t *title, *description, * start_parameter, *currency, *total_amount;

        title = json_object_get(json, "invoice");
        description = json_object_get(json, "description");
        start_parameter = json_object_get(json, "start_parameter");
        currency = json_object_get(json, "currency");
        total_amount = json_object_get(json, "total_amount");

        Invoice * o_i = invoice(
            json_string_value(title),
            json_string_value(description),
            json_string_value(start_parameter),
            json_string_value(currency),
            json_integer_value(total_amount)
        );

        return o_i;
    }

    return NULL;
}

ShippingAddress * shipping_address_parse(json_t * json){
    if(json_is_object(json)){
        json_t *country_code, *state, *city, *street_line1, *street_line2, *post_code;

        country_code = json_object_get(json, "country_code");
        state = json_object_get(json, "state");
        city = json_object_get(json, "city");
        street_line1 = json_object_get(json, "street_line1");
        street_line2 = json_object_get(json, "street_line2");
        post_code = json_object_get(json, "post_code");

        ShippingAddress * o_sa = shipping_address(
            json_string_value(country_code),
            json_string_value(state),
            json_string_value(city),
            json_string_value(street_line1),
            json_string_value(street_line2),
            json_string_value(post_code)
        );

        return o_sa;
    }

    return NULL;
}

PreCheckoutQuery * pre_checkout_query_parse(json_t * json){
    if(json_is_object(json)){
        json_t *id, *from, *currency, *total_amount, *invoice_payload, *shipping_option_id, *order_info;

        id = json_object_get(json, "id");
        from = json_object_get(json, "from");
        currency = json_object_get(json, "currency");
        total_amount = json_object_get(json, "total_amount");
        invoice_payload = json_object_get(json, "invoice_payload");
        shipping_option_id = json_object_get(json, "shipping_option_id");
        order_info = json_object_get(json, "order_info");

        User * ofrom = user_parse(from);
        OrderInfo * oorder_info = order_info_parse(order_info);

        PreCheckoutQuery * o_pcq = pre_checkout_query(
            json_string_value(id),
            ofrom,
            json_string_value(currency),
            json_integer_value(total_amount),
            json_string_value(invoice_payload),
            json_string_value(shipping_option_id),
            oorder_info
        );

        return o_pcq;
    }

    return NULL;
}

OrderInfo * order_info_parse(json_t * json){
    if(json_is_object(json)){
        json_t *name, *phone_number, *email, *shipping_address;

        name = json_object_get(json, "name");
        phone_number = json_object_get(json, "phone_number");
        email = json_object_get(json, "email");
        shipping_address = json_object_get(json, "shipping_address");

        ShippingAddress * oshipping_address = shipping_address_parse(shipping_address);

        OrderInfo * o_oi = order_info(
            json_string_value(name),
            json_string_value(phone_number),
            json_string_value(email),
             oshipping_address
        );

        return o_oi;
    }

    return NULL;
}

SuccessfulPayment * successful_payment_parse(json_t * json){
    if(json_is_object(json)){
        json_t *currency, *total_amount, *invoice_payload, *shipping_option_id,
        *order_info, *telegram_payment_charge_id, *provider_payment_charge_id;

        currency = json_object_get(json, "currency");
        total_amount = json_object_get(json, "total_amount");
        invoice_payload = json_object_get(json, "invoice_payload");
        shipping_option_id = json_object_get(json, "shipping_option_id");
        order_info = json_object_get(json, "order_info");
        telegram_payment_charge_id = json_object_get(json, "telegram_payment_charge_id");
        provider_payment_charge_id = json_object_get(json, "provider_payment_charge_id");

        OrderInfo * oorder_info = order_info_parse(order_info);

        SuccessfulPayment * o_sp = successful_payment(
            json_string_value(currency),
            json_integer_value(total_amount),
            json_string_value(invoice_payload), 
            json_string_value(shipping_option_id),
            oorder_info,
            json_string_value(telegram_payment_charge_id),
            json_string_value(provider_payment_charge_id)
        );

        return o_sp;
    }

    return NULL;
}

File * file_parse(json_t * json){
    if(json_is_object(json)){
        json_t *file_id, *file_size, *file_path;

        file_id = json_object_get(json, "file_id");
        file_size = json_object_get(json, "file_size");
        file_path = json_object_get(json, "file_path");

        File * o_f = file(
            json_string_value(file_id),
            json_integer_value(file_size),
            json_string_value(file_path)
        );

        return o_f;
    }

    return NULL;
}

UserProfilePhotos * user_profile_photos_parse(json_t * json){
    if(json_is_object(json)){
        json_t *total_count, *photos, *array_photos;
        size_t _length, i, length_, x;

        total_count = json_object_get(json, "total_count");

        PhotoSize ** ophotos = NULL, *_temp = NULL;
        photos = json_object_get(json, "photos");
        _length = json_array_size(photos);

        /* Array of Array PhotoSize */
        ophotos = (PhotoSize **) malloc(_length * sizeof(PhotoSize));
        if (_length > 0) {
            for (i = 0; i < _length; i++) {
                array_photos = json_array_get(photos, i);
                length_ = json_array_size(array_photos);

                if(length_ > 0){
                    ophotos[i] = photo_size_parse(json_array_get(array_photos, 0));

                    for(x = 1; x < length_; x++){
                        _temp = photo_size_parse(json_array_get(array_photos, x));
                        if(_temp)
                            photo_size_add(ophotos[i], _temp);
                    }

                }

            }
        }

        UserProfilePhotos * oupp = user_profile_photos(
            json_integer_value(total_count),
            ophotos
        );

        return oupp;
    }

    return NULL;
}


ChatPhoto * chat_photo_parse(json_t * json){
    if(json_is_object(json)){
        json_t *small_file_id, *big_file_id;

        small_file_id = json_object_get(json, "small_file_id");
        big_file_id   = json_object_get(json, "big_file_id");

        ChatPhoto * o_cp = chat_photo(
            json_string_value(small_file_id),
            json_string_value(big_file_id)
        );

        return o_cp;
    }
}
