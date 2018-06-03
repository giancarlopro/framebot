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

#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct _error{
    int64_t error_code;
    char *description;
} Error;

typedef struct _user{
    int64_t id;
    bool is_bot:1;
    char *first_name;
    char *last_name;
    char *username;
    char *language_code;
    struct _user *next;
} User;

typedef struct _bot{
    char *token;
    User *user;
} Bot;

typedef struct _chat_photo{
    char *small_file_id;
    char *big_file_id;
} ChatPhoto;

typedef struct _chat{
    int64_t id;
    char *type;
    char *title;
    char *username;
    char *first_name;
    char *last_name;
    bool all_members_are_administrators:1;
    ChatPhoto *photo;
    char *description;
    char *invite_link;
    struct _message *pinned_message;
    char *sticker_set_name;
    bool can_set_sticker_set:1;
} Chat;

typedef struct _message_entity{
    char *type;
    int64_t offset;
    int64_t length;
    char *url;
    User *user;
    struct _message_entity *next;
} MessageEntity;

typedef struct _audio{
    char *file_id;
    int64_t duration;
    char *performer;
    char *title;
    char *mime_type;
    int64_t file_size;
} Audio;

typedef struct _photo_size{
    char *file_id;
    int width;
    int height;
    int64_t file_size;
    struct _photo_size *next;
} PhotoSize;

typedef struct _document{
    char *file_id;
    PhotoSize *thumb;
    char *file_name;
    char *mime_type;
    int64_t file_size;
} Document, Animation;

typedef struct _game{
    char *title;
    char *description;
    PhotoSize *photo;//Array
    char *text;
    MessageEntity *text_entities;//Array
    Animation *animation;
} Game;

typedef struct _sticker{
    char *file_id;
    int width;
    int height;
    PhotoSize *thumb;
    char *emoji;
    int64_t file_size;
} Sticker;

typedef struct _video{
    char *file_id;
    int width;
    int height;
    int64_t duration;
    PhotoSize *thumb;
    char *mime_type;
    int64_t file_size;
} Video;

typedef struct video_note{
    char *file_id;
    int64_t length;
    int64_t duration;
    PhotoSize *thumb;
    int64_t file_size;
} VideoNote;

typedef struct _voice{
    char *file_id;
    int64_t duration;
    char *mime_type;
    int64_t file_size;
} Voice;

typedef struct _contact{
    char *phone_number;
    char *first_name;
    char *last_name;
    int64_t user_id;
} Contact;

typedef struct _location{
    double latitude;
    double longitude;
} Location;

typedef struct _venue{
    Location *location;
    char *title;
    char *address;
    char *foursquare_id;
} Venue;

typedef struct _invoice{
    char *title;
    char *description;
    char *start_parameter;
    char *currency;
    int64_t total_amount;
} Invoice;

typedef struct _shipping_address{
    char *country_code;
    char *state;
    char *city;
    char *street_line1;
    char *street_line2;
    char *post_code;
} ShippingAddress;

typedef struct _order_info{
    char *name;
    char *phone_number;
    char *email;
    ShippingAddress *shipping_address;
} OrderInfo;

typedef struct _successful_payment{
    char *currency;
    int64_t total_amount;
    char *invoice_payload;
    char *shipping_option_id;
    OrderInfo *order_info;
    char *telegram_payment_charge_id;
    char *provider_payment_charge_id;
} SuccessfulPayment;

typedef struct _shipping_query{
    char *id;
    User *from;
    char *invoice_payload;
    ShippingAddress *shipping_address;
} ShippingQuery;

typedef struct _pre_checkout_query{
    char *id;
    User *from;
    char *currency;
    int64_t total_amount;
    char *invoice_payload;
    char *shipping_option_id;
    OrderInfo *order_info;
} PreCheckoutQuery;

typedef struct _message{
    int64_t message_id;
    User *from;
    int64_t date;
    Chat *chat;
    User *forward_from;
    Chat *forward_from_chat;
    int64_t forward_from_message_id;
    char *forward_signature;
    int64_t forward_date;
    struct _message *reply_to_message;
    int64_t edit_date;
    char *media_group_id;
    char *author_signature;
    char *text;
    MessageEntity *entities;//Array
    MessageEntity *caption_entities;
    Audio *audio;
    Document *document;
    Game *game;
    PhotoSize *photo;//Array
    Sticker *sticker;
    Video *video;
    Voice *voice;
    VideoNote *video_note;
    char *caption;
    Contact *contact;
    Location *location;
    Venue *venue;
    User *new_chat_members;
    User *left_chat_member;
    char *new_chat_title;
    PhotoSize *new_chat_photo;//Array
    bool delete_chat_photo:1;
    bool group_chat_created:1;
    bool supergroup_chat_created:1;
    bool channel_chat_created:1;
    int64_t migrate_to_chat_id;
    int64_t migrate_from_chat_id;
    struct _message *pinned_message;
    Invoice *invoice;
    SuccessfulPayment *successful_payment;
    char *connected_website;
} Message;

typedef struct _inline_query{
    char *id;
    User *from;
    Location *location;
    char *query;
    char *offset;
} InlineQuery;

typedef struct _chosen_inline_result{
    char *result_id;
    User *from;
    Location *location;
    char *inline_message_id;
    char *query;
} ChosenInlineResult;

typedef struct _callback_query{
    char *id;
    User *from;
    Message *message;
    char *inline_message_id;
    char *chat_instance;
    char *data;
    char *game_short_name;
} CallbackQuery;

typedef struct _update{
    int64_t update_id;
    Message *message;
    Message *edited_message;
    Message *channel_post;
    Message *edited_channel_post;
    InlineQuery *inline_query;
    ChosenInlineResult *chosen_inline_result;
    CallbackQuery *callback_query;
    ShippingQuery *shipping_query;
    PreCheckoutQuery *pre_checkout_query;
	struct _update *next;
} Update;

typedef struct {
    int64_t update_id;
    Update *up_message;
    Update *up_edited_message;
    Update *up_channel_post;
    Update *up_edited_channel_post;
    Update *up_inline_query;
    Update *up_chosen_inline_result;
    Update *up_callback_query;
    Update *up_shipping_query;
    Update *up_pre_checkout_query;
} Framebot;

typedef struct _chat_member {
    User *user;
    char *status;
    int64_t until_date;
    bool can_be_edited:1;
    bool can_change_info:1;
    bool can_post_messages:1;
    bool can_edit_messages:1;
    bool can_delete_messages:1;
    bool can_invite_users:1;
    bool can_restrict_members:1;
    bool can_pin_messages:1;
    bool can_promote_members:1;
    bool can_send_messages:1;
    bool can_send_media_messages:1;
    bool can_send_other_messages:1;
    bool can_add_web_page_previews:1;

    struct _chat_member *next;
} ChatMember;

typedef struct _file{
    char *file_id;
    int64_t file_size;
    char *file_path;
} File;

typedef struct _user_profile_photos{
    int64_t total_count;
    PhotoSize ** photos;
} UserProfilePhotos;

typedef struct _callback_game{
    int64_t user_id;
    int64_t score;
    bool force:1;
    bool disable_edit_message:1;
    int64_t chat_id;
    int64_t message_id;
    char *inline_message_id;
} CallbackGame;


 
//User functions
void user_add(User *origin, User *next);
void user_free(User *usr);

//Chat functions
void chat_free(Chat *cht);

//Message entity functions
void message_entity_free(MessageEntity *msgett);
void message_entity_add(MessageEntity *dest, MessageEntity *src);
size_t message_entity_len(MessageEntity *message_entity);
MessageEntity *message_entity_get(MessageEntity *message_entity, int index);

//Audio functions
void audio_free(Audio *audio);

void photo_size_free(PhotoSize *photoSize);
void photo_size_add(PhotoSize *root,PhotoSize *newps);
PhotoSize *photo_size_get(PhotoSize *root, int i);
size_t photo_size_len(PhotoSize *ophoto_sise);

void document_free(Document *document);

void animation_free(Animation *animation);

void game_free(Game *game);

void sticker_free(Sticker *_sticker);

void video_free(Video *_video);

void voice_free(Voice *_voice);

void contact_free(Contact *_contact);

void location_free(Location *_location);

void venue_free(Venue *_venue);

void message_free(Message *message);

Bot *bot(const char *token, User *user);
void bot_free(Bot *bot);

void chosen_inline_result_free(ChosenInlineResult *cir);

void update_free(Update *oupdate);
void update_add(Update *dest, Update *src);
Update *update_get(Update *u, int index);
size_t update_len(Update *u);

void chat_member_free(ChatMember *chatMember);
void chat_member_add (ChatMember *dest, ChatMember *src);
ChatMember *chat_member_get (ChatMember *chatMember, int index);
size_t chat_member_len (ChatMember *chatMember);

void inline_query_free(InlineQuery *inline_query);

void callback_query_free(CallbackQuery *callback_query);

void video_note_free(VideoNote *video_note);

void invoice_free(Invoice *invoice);

void shipping_query_free(ShippingQuery *shipping_query);

void shipping_address_free(ShippingAddress *shipping_address);

void order_info_free(OrderInfo *order_info);

void pre_checkout_query_free(PreCheckoutQuery *pcq);

void successful_payment_free(SuccessfulPayment *spayment);

void file_free(File *ofile);

void user_profile_photos_free(UserProfilePhotos *oupp);

void chat_photo_free(ChatPhoto *ochat_photo);

void error(int64_t error_code, const char *description);
void error_free();
Error *get_error();

void framebot_add( Framebot *framebot, Update *update );
void framebot_free(Framebot *framebot);

#endif // OBJECTS_H_
