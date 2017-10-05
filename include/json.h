#ifndef JSON_H
#define JSON_H

#include <telebot.h>

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
int valid_update(long int update_id);
ChatMember *chat_member_parse (json_t *json);

#endif
