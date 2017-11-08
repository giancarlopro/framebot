#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct _error{
    long int error_code;
    char * description;
} Error;

typedef struct _user{
    long int id;
    bool is_bot:1;
    char *first_name;
    char *last_name;
    char *username;
    char *language_code;
} User;

typedef struct _bot{
    char * token;
    User * user;
} Bot;

typedef struct _chat_photo{
    char * small_file_id;
    char * big_file_id;
} ChatPhoto;

typedef struct _chat{
    long int id;
    char * type;
    char * title;
    char * username;
    char * first_name;
    char * last_name;
    bool all_members_are_administrators:1;
    ChatPhoto * photo;
    char * description;
    char * invite_link;
    struct _message * pinned_message;
    char * sticker_set_name;
    bool can_set_sticker_set:1;
} Chat;

typedef struct _message_entity{
    char * type;
    long int offset;
    long int length;
    char * url;
    User * user;
    struct _message_entity * next;
} MessageEntity;

typedef struct _audio{
    char * file_id;
    long int duration;
    char * performer;
    char * title;
    char * mime_type;
    long int file_size;
} Audio;

typedef struct _photo_size{
    char * file_id;
    int width;
    int height;
    long int file_size;
    struct _photo_size * next;
} PhotoSize;

typedef struct _document{
    char * file_id;
    PhotoSize * thumb;
    char * file_name;
    char * mime_type;
    long int file_size;
} Document;

typedef struct _animation{
    char * file_id;
    PhotoSize * thumb;
    char * file_name;
    char * mime_type;
    long int file_size;
} Animation;

typedef struct _game{
    char * title;
    char * description;
    PhotoSize * photo;//Array
    char * text;
    MessageEntity * text_entities;//Array
    Animation * animation;
} Game;

typedef struct _sticker{
    char * file_id;
    int width;
    int height;
    PhotoSize * thumb;
    char * emoji;
    long int file_size;
} Sticker;

typedef struct _video{
    char * file_id;
    int width;
    int height;
    long int duration;
    PhotoSize * thumb;
    char * mime_type;
    long int file_size;
} Video;

typedef struct video_note{
    char * file_id;
    long length;
    long duration;
    PhotoSize * thumb;
    long file_size;
} VideoNote;

typedef struct _voice{
    char * file_id;
    long int duration;
    char * mime_type;
    long int file_size;
} Voice;

typedef struct _contact{
    char * phone_number;
    char * first_name;
    char * last_name;
    long int user_id;
} Contact;

typedef struct _location{
    float latitude;
    float longitude;
} Location;

typedef struct _venue{
    Location * location;
    char * title;
    char * address;
    char * foursquare_id;
} Venue;

typedef struct _invoice{
    char * title;
    char * description;
    char * start_parameter;
    char * currency;
    long total_amount;
} Invoice;

typedef struct _shipping_address{
    char * country_code;
    char * state;
    char * city;
    char * street_line1;
    char * street_line2;
    char * post_code;
} ShippingAddress;

typedef struct _order_info{
    char * name;
    char * phone_number;
    char * email;
    ShippingAddress * shipping_address;
} OrderInfo;

typedef struct _successful_payment{
    char * currency;
    long total_amount;
    char * invoice_payload;
    char * shipping_option_id;
    OrderInfo * order_info;
    char * telegram_payment_charge_id;
    char * provider_payment_charge_id;
} SuccessfulPayment;

typedef struct _shipping_query{
    char * id;
    User * from;
    char * invoice_payload;
    ShippingAddress * shipping_address;
} ShippingQuery;

typedef struct _pre_checkout_query{
    char * id;
    User * user;
    char * currency;
    long total_amount;
    char * invoice_payload;
    char * shipping_option_id;
    OrderInfo * order_info;
} PreCheckoutQuery;

typedef struct _message{
    long int message_id;
    User * from;
    long int date;
    Chat * chat;
    User * forward_from;
    Chat * forward_from_chat;
    long int forward_from_message_id;
    char * forward_signature;
    long int forward_date;
    struct _message * reply_to_message;
    long int edit_date;
    char * author_signature;
    char * text;
    MessageEntity * entities;//Array
    MessageEntity * caption_entities;
    Audio * audio;
    Document * document;
    Game * game;
    PhotoSize * photo;//Array
    Sticker * sticker;
    Video * video;
    Voice * voice;
    VideoNote * video_note;
    char * caption;
    Contact * contact;
    Location * location;
    Venue * venue;
    User * new_chat_member;
    User * left_chat_member;
    char * new_chat_title;
    PhotoSize * new_chat_photo;//Array
    bool delete_chat_photo:1;
    bool group_chat_created:1;
    bool supergroup_chat_created:1;
    bool channel_chat_created:1;
    long int migrate_to_chat_id;
    long int migrate_from_chat_id;
    struct _message * pinned_message;
    Invoice * invoice;
    SuccessfulPayment * successful_payment;
} Message;

typedef struct _inline_query{
    char * id;
    User * from;
    Location * location;
    char * query;
    char * offset;
} InlineQuery;

typedef struct _chosen_inline_result{
    char * result_id;
    User * from;
    Location * location;
    char * inline_message_id;
    char * query;
} ChosenInlineResult;

typedef struct _callback_query{
    char * id;
    User * from;
    Message * message;
    char * inline_message_id;
    char * chat_instance;
    char * data;
    char * game_short_name;
} CallbackQuery;

typedef struct _update{
    long int update_id;
    Message * message;
    Message * edited_message;
    Message * channel_post;
    Message * edited_channel_post;
    InlineQuery * inline_query;
    ChosenInlineResult * chosen_inline_result;
    CallbackQuery * callback_query;
    ShippingQuery * shipping_query;
    PreCheckoutQuery * pre_checkout_query;
	struct _update *next;
} Update;

typedef struct _chat_member {
    User *user;
    char *status;
    long int until_date;
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
    char * file_id;
    long file_size;
    char * file_path;
} File;

typedef struct _user_profile_photos{
    long total_count;
    PhotoSize ** photos;
} UserProfilePhotos;

typedef struct _callback_game{
    long int user_id;
    long int score;
    bool force:1;
    bool disable_edit_message:1;
    long int chat_id;
    long int message_id;
    char * inline_message_id;
} CallbackGame;

typedef struct _keyboard_button {
    char * text;
    bool request_contact;
    bool request_location;
    struct _keyboard_button * next;
} KeyboardButton;

typedef struct _inline_keyboard_button{
    char * text;
    char * url;
    char * callback_data;
    char * switch_nline_query;
    char * switch_inline_query_current_chat;
    CallbackGame * callback_game;
    bool pay:1;
} InlineKeyboardButton;

typedef struct _inline_keyboard_markup{
    int type;
    InlineKeyboardButton ** inline_keyboard;
} InlineKeyboardMarkup;

typedef struct _reply_keyboard_markup {
    int type;
    KeyboardButton ** keyboard_button;
    bool resize_keyboard;
    bool one_time_keyboard;
    bool selective:1;
} ReplyKeyboardMarkup;

typedef struct _reply_keyboard_remove{
    int type;
    bool remove_keyboard:1;
    bool selective:1;
} ReplyKeyboardRemove;

typedef struct _force_reply{
    int type;
    bool force_reply:1;
    bool selective:1;
} ForceReply;

typedef union _keyboard{
    int type;
    InlineKeyboardButton * inline_keyboard_markup;
    ReplyKeyboardMarkup * reply_keyboard_markup;
    ReplyKeyboardRemove * reply_keyboard_remove;
    ForceReply * _force_reply;
} Keyboard;

//User functions
User *user(
    long int id, bool is_bot, const char *first_name, const char *last_name,
    const char *username, const char *language_code);
void user_free(User *usr);

//Chat functions
Chat * chat(
    long int id, const char * type, const char * title, const char * username,
    const char * first_name, const char * last_name,
    bool all_members_are_administrators, ChatPhoto * ochat_photo,
    const char * description, const char * invite_link, Message * opinned_message,
    const char * sticker_set_name, bool can_set_sticker_set);
void chat_free(Chat * cht);

//Message entity functions
MessageEntity * message_entity(
    const char * type, long int offset, long int length,
    const char * url, User * user);
void message_entity_free(MessageEntity * msgett);
void message_entity_add(MessageEntity * dest, MessageEntity * src);
size_t message_entity_len(MessageEntity * message_entity);
MessageEntity * message_entity_get(MessageEntity * message_entity, int index);

//Audio functions
Audio * audio(
    const char * file_id, long int duration, const char * performer,
    const char * title, const char * mime_type, long int file_size);
void audio_free(Audio * audio);

PhotoSize * photo_size(const char * file_id, int width, int height, long int file_size);
void photo_size_free(PhotoSize * photoSize);
void photo_size_add(PhotoSize * root,PhotoSize * newps);
PhotoSize * photo_size_get(PhotoSize * root, int i);
size_t photo_size_len(PhotoSize * ophoto_sise);

Document * document(
    const char * file_id, PhotoSize * thumb, const char * file_name,
    const char * mime_type, long int file_size);
void document_free(Document * document);

Animation * animation(
    const char * file_id, PhotoSize * thumb, const char * file_name,
    const char * mime_type,long int file_size);
void animation_free(Animation * animation);

Game * game(
    const char * title, const char * description, PhotoSize * photo,
    const char * text, MessageEntity * text_entities, Animation * animation);
void game_free(Game * game);

Sticker * sticker(
    const char * file_id, int width, int height,PhotoSize * thumb,
    const char * emoji, long int file_size);
void sticker_free(Sticker * _sticker);

Video * video(
    const char * file_id, int width, int height, long int duration,
    PhotoSize * thumb, const char * mime_type,long int file_size);
void video_free(Video * _video);

Voice * voice(const char * file_id, long int duration,const char * mime_type,
    long int file_size);
void voice_free(Voice * _voice);

Contact * contact(const char * phone_number,const char * first_name,
    const char * last_name,long int user_id);
void contact_free(Contact * _contact);

Location * location(float latitude,float longitude);
void location_free(Location * _location);

Venue * venue(Location * location, const char * title, const char * address,
    const char * foursquare_id);
void venue_free(Venue * _venue);

Message * message(
    long int message_id, User * from, long int date, Chat * chat,
    User * forward_from, Chat * forward_from_chat, long int forward_from_message_id,
    const char * forward_signature, long int forward_date, Message * reply_to_message,
    long int edit_date, const char * author_signature, const char * text,
    MessageEntity * entities, MessageEntity * ocaption_entiities, Audio * audio,
    Document * document, Game * game, PhotoSize * photo, Sticker * sticker,
    Video * video, Voice * voice, VideoNote * video_note, const char * caption,
    Contact * contact, Location * location, Venue * venue, User * new_chat_member,
    User * left_chat_member, const char * new_chat_title, PhotoSize * new_chat_photo,
    int delete_chat_photo, int group_chat_created, int supergroup_chat_created,
    int channel_chat_created, long int migrate_to_chat_id, long int migrate_from_chat_id,
    Message * pinned_message, Invoice * oinvoice,SuccessfulPayment * successful_payment
);
void message_free(Message * message);

Bot * bot(const char * token, User * user);
void bot_free(Bot * bot);

ChosenInlineResult * chosen_inline_result (const char *result_id, User *from,
    Location *location, const char *inline_message_id, const char * query);
void chosen_inline_result_free(ChosenInlineResult * cir);

Update * update(long int update_id, Message * message, Message * edited_message,
    Message * channel_post, Message * edited_channel_post,
    InlineQuery * inline_query, ChosenInlineResult * chosen_inline_result,
    CallbackQuery * callback_query, ShippingQuery * shipping_query,
    PreCheckoutQuery * pre_checkout_query);
void update_free(Update * oupdate);
void update_add(Update *dest, Update *src);
Update *update_get(Update *u, int index);
size_t update_len(Update *u);

ChatMember *chat_member(User *user, const char *status, long int until_date,
    bool can_be_edited, bool can_change_info, bool can_post_messages,
    bool can_edit_messages, bool can_delete_messages, bool can_invite_users,
    bool can_restrict_members, bool can_pin_messages, bool can_promote_members,
    bool can_send_messages, bool can_send_media_messages,
    bool can_send_other_messages, bool can_add_web_page_previews);
void chat_member_free(ChatMember *chatMember);
void chat_member_add (ChatMember *dest, ChatMember *src);
ChatMember *chat_member_get (ChatMember *chatMember, int index);
size_t chat_member_len (ChatMember *chatMember);

InlineQuery * inline_query(const char * id, User * user, Location * location,
    const char *query, const char * offset);
void inline_query_free(InlineQuery * inline_query);

CallbackQuery * callback_query(const char * id, User * user, Message * message,
    const char * inline_message_id, const char * chat_instance,
    const char * data, const char * game_short_name);
void callback_query_free(CallbackQuery * callback_query);

VideoNote * video_note(const char * file_id, long length, long duration,
    PhotoSize * photo_size, long file_size);
void video_note_free(VideoNote * video_note);

Invoice * invoice(const char * title, const char * description,
    const char * start_parameter, const char * currency, long total_amount);
void invoice_free(Invoice * invoice);

ShippingQuery * shipping_query(const char *id, User * from,
    const char * invoice_payload, ShippingAddress * shipping_address);
void shipping_query_free(ShippingQuery * shipping_query);

ShippingAddress * shipping_address(const char * country_code,
    const char * state, const char * city, const char * street_line1,
    const char * street_line2, const char * post_code);
void shipping_address_free(ShippingAddress * shipping_address);

OrderInfo * order_info(const char * name, const char * phone_number,
    const char * email, ShippingAddress * shipping_address);
void order_info_free(OrderInfo * order_info);

PreCheckoutQuery * pre_checkout_query(const char * id, User * from,
    const char * currency, long total_amount, const char * invoice_payload,
    const char * shipping_option_id, OrderInfo * order_info);
void pre_checkout_query_free(PreCheckoutQuery * pcq);

SuccessfulPayment * successful_payment(const char * currency, long total_amount,
    const char * invoice_payload, const char * shipping_option_id,
    OrderInfo * oorder_info, const char * telegram_payment_charge_id,
    const char * provider_payment_charge_id);
void successful_payment_free(SuccessfulPayment * spayment);

File * file(const char * file_id, long int file_size, const char * file_path);
void file_free(File * ofile);

UserProfilePhotos * user_profile_photos(long int total_count, PhotoSize ** photo_size);
void user_profile_photos_free(UserProfilePhotos * oupp);

ChatPhoto * chat_photo(const char * small_file_id, const char * big_file_id);
void chat_photo_free(ChatPhoto * ochat_photo);

void error(long int error_code, const char * description);
void error_free();
Error * get_error();

#endif // OBJECTS_H_
