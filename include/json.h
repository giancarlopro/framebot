#ifndef JSON_H
#define JSON_H

#include <telebot.h>
json_t * start_json(char * json);
void error_parse(json_t * error);
json_t * load(char * json);
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
bool valid_update(long int update_id);
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
