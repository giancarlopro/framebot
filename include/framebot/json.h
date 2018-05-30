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

#ifndef JSON_H
#define JSON_H

#include <framebot/framebot.h>

typedef struct _struct_json {
	json_t *root;
	json_t *content;
} refjson;

refjson * start_json(char * json);
void close_json( refjson *s_json );
void error_parse(refjson * error);
refjson * load(char * json);
User * user_parse(json_t * json);
Chat * chat_parse(json_t *json);
MessageEntity * message_entity_parse(json_t *json);
Audio * audio_parse(json_t *json);
PhotoSize * photo_size_parse(json_t *json);
Document * document_parse(json_t *json);
Animation * animation_parse(json_t *json);
Game * game_parse(json_t *json);
Sticker * sticker_parse(json_t *json);
Video * video_parse(json_t *json);
Voice * voice_parse(json_t *json);
Contact * contact_parse(json_t *json);
Location * location_parse(json_t *json);
Venue * venue_parse(json_t *json);
Message * message_parse(json_t *json);
Update * update_parse(json_t *json);
User * get_me_parse(char * json);
ChatMember *chat_member_parse (json_t *json);
ChatMember *chat_member_array_parse (json_t *cm_array);
ChosenInlineResult * choosen_inline_result_parse(json_t * json);
InlineQuery * inline_query_parse(json_t * json);
CallbackQuery * callback_query_parse(json_t * json);
VideoNote * video_note_parse(json_t * json);
Invoice * invoice_parse(json_t * json);
ShippingQuery * shipping_query_parse(json_t * json);
ShippingAddress * shipping_address_parse(json_t * json);
PreCheckoutQuery * pre_checkout_query_parse(json_t * json);
OrderInfo * order_info_parse(json_t * json);
SuccessfulPayment * successful_payment_parse(json_t * json);
File * file_parse(json_t * json);
UserProfilePhotos * user_profile_photos_parse(json_t * json);
ChatPhoto * chat_photo_parse(json_t * json);

#endif
