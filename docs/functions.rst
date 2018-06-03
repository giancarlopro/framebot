Funções
=======

Aqui você encontra as funções implementadas pela biblioteca.

Todas as funções disponíveis na API do Telegram, estão disponíveis na biblíoteca
usando o formato lower case separando os nomes com underscore.

Referencia completa
-------------------

.. c:function:: User *user( long int id, bool is_bot, const char *first_name, const char *last_name, const char *username, const char *language_code)

.. c:function:: void user_add(User *origin, User *next)

.. c:function:: void user_free(User *usr)

.. c:function:: void chat_free(Chat *cht)

.. c:function:: void message_entity_free(MessageEntity *msgett)

.. c:function:: void message_entity_add(MessageEntity *dest, MessageEntity *src)

.. c:function:: size_t message_entity_len(MessageEntity *message_entity)

.. c:function:: MessageEntity *message_entity_get(MessageEntity *message_entity, int index)

.. c:function:: Audio *audio( const char *file_id, long int duration, const char *performer, const char *title, const char *mime_type, long int file_size)

.. c:function:: void audio_free(Audio *audio)

.. c:function:: void photo_size_free(PhotoSize *photoSize)

.. c:function:: void photo_size_add(PhotoSize *root,PhotoSize *newps)

.. c:function:: PhotoSize *photo_size_get(PhotoSize *root, int i)

.. c:function:: size_t photo_size_len(PhotoSize *ophoto_sise)

.. c:function:: Document *document( const char *file_id, PhotoSize *thumb, const char *file_name, const char *mime_type, long int file_size)

.. c:function:: void document_free(Document *document)

.. c:function:: Animation *animation( const char *file_id, PhotoSize *thumb, const char *file_name, const char *mime_type,long int file_size)

.. c:function:: void animation_free(Animation *animation)

.. c:function:: Game *game( const char *title, const char *description, PhotoSize *photo, const char *text, MessageEntity *text_entities, Animation *animation)

.. c:function:: void game_free(Game *game)

.. c:function:: Sticker *sticker( const char *file_id, int width, int height,PhotoSize *thumb, const char *emoji, long int file_size)

.. c:function:: void sticker_free(Sticker *_sticker)

.. c:function:: Video *video( const char *file_id, int width, int height, long int duration, PhotoSize *thumb, const char *mime_type,long int file_size)

.. c:function:: void video_free(Video *_video)

.. c:function:: Voice *voice(const char *file_id, long int duration,const char *mime_type, long int file_size)

.. c:function:: void voice_free(Voice *_voice)

.. c:function:: Contact *contact(const char *phone_number,const char *first_name, const char *last_name,long int user_id)

.. c:function:: void contact_free(Contact *_contact)

.. c:function:: Location *location(float latitude,float longitude)

.. c:function:: void location_free(Location *_location)

.. c:function:: Venue *venue(Location *location, const char *title, const char *address, const char *foursquare_id)

.. c:function:: void venue_free(Venue *_venue)

.. c:function:: void message_free(Message *message)

.. c:function:: Bot *bot(const char *token, User *user)

.. c:function:: void bot_free(Bot *bot)

.. c:function:: ChosenInlineResult *chosen_inline_result (const char *result_id, User *from, Location *location, const char *inline_message_id, const char *query)

.. c:function:: void chosen_inline_result_free(ChosenInlineResult *cir)

.. c:function:: Update *update(long int update_id, Message *message, Message *edited_message, Message *channel_post, Message *edited_channel_post, InlineQuery *inline_query, ChosenInlineResult *chosen_inline_result, CallbackQuery *callback_query, ShippingQuery *shipping_query, PreCheckoutQuery *pre_checkout_query)

.. c:function:: void update_free(Update *oupdate)

.. c:function:: void update_add(Update *dest, Update *src)

.. c:function:: Update *update_get(Update *u, int index)

.. c:function:: size_t update_len(Update *u)

.. c:function:: ChatMember *chat_member(User *user, const char *status, long int until_date, bool can_be_edited, bool can_change_info, bool can_post_messages, bool can_edit_messages, bool can_delete_messages, bool can_invite_users, bool can_restrict_members, bool can_pin_messages, bool can_promote_members, bool can_send_messages, bool can_send_media_messages, bool can_send_other_messages, bool can_add_web_page_previews)

.. c:function:: void chat_member_free(ChatMember *chatMember)

.. c:function:: void chat_member_add (ChatMember *dest, ChatMember *src)

.. c:function:: ChatMember *chat_member_get (ChatMember *chatMember, int index)

.. c:function:: size_t chat_member_len (ChatMember *chatMember)

.. c:function:: InlineQuery *inline_query(const char *id, User *user, Location *location, const char *query, const char *offset)

.. c:function:: void inline_query_free(InlineQuery *inline_query)

.. c:function:: CallbackQuery *callback_query(const char *id, User *user, Message *message, const char *inline_message_id, const char *chat_instance, const char *data, const char *game_short_name)

.. c:function:: void callback_query_free(CallbackQuery *callback_query)

.. c:function:: VideoNote *video_note(const char *file_id, long length, long duration, PhotoSize *photo_size, long file_size)

.. c:function:: void video_note_free(VideoNote *video_note)

.. c:function:: Invoice *invoice(const char *title, const char *description, const char *start_parameter, const char *currency, long total_amount)

.. c:function:: void invoice_free(Invoice *invoice)

.. c:function:: ShippingQuery *shipping_query(const char *id, User *from, const char *invoice_payload, ShippingAddress *shipping_address)

.. c:function:: void shipping_query_free(ShippingQuery *shipping_query)

.. c:function:: ShippingAddress *shipping_address(const char *country_code, const char *state, const char *city, const char *street_line1, const char *street_line2, const char *post_code)

.. c:function:: void shipping_address_free(ShippingAddress *shipping_address)

.. c:function:: OrderInfo *order_info(const char *name, const char *phone_number, const char *email, ShippingAddress *shipping_address)

.. c:function:: void order_info_free(OrderInfo *order_info)

.. c:function:: void pre_checkout_query_free(PreCheckoutQuery *pcq)

.. c:function:: SuccessfulPayment *successful_payment(const char *currency, long total_amount, const char *invoice_payload, const char *shipping_option_id, OrderInfo *oorder_info, const char *telegram_payment_charge_id, const char *provider_payment_charge_id)

.. c:function:: void successful_payment_free(SuccessfulPayment *spayment)

.. c:function:: File *file(const char *file_id, long int file_size, const char *file_path)

.. c:function:: void file_free(File *ofile)

.. c:function:: UserProfilePhotos *user_profile_photos(long int total_count, PhotoSize ** photo_size)

.. c:function:: void user_profile_photos_free(UserProfilePhotos *oupp)

.. c:function:: ChatPhoto *chat_photo(const char *small_file_id, const char *big_file_id)

.. c:function:: void chat_photo_free(ChatPhoto *ochat_photo)

.. c:function:: void error(long int error_code, const char *description)

.. c:function:: void error_free()

.. c:function:: Error *get_error()

.. c:function:: void framebot_add( Framebot *framebot, Update *update )

.. c:function:: void framebot_free(Framebot *framebot)

.. c:function:: void framebot_init()

.. c:function:: Bot * framebot(const char *token)

.. c:function:: refjson *generic_method_call (const char *token, char *formats, ...)

.. c:function:: Error * show_error()

.. c:function:: User * get_me(const char *token)

.. c:function:: Framebot *get_updates (Bot *bot, Framebot *framebot, long int offset, long int limit, long int timeout, char *allowed_updates)

.. c:function:: Message * send_message (Bot *bot, char * chat_id, char *text, char * parse_mode,   bool disable_web_page_preview, long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * send_message_chat (Bot *bot, long int chat_id, char *text, char * parse_mode,   bool disable_web_page_preview, long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * forward_message_from (Bot * bot, long int chat_id, char * from_chat_id,  long int message_id)

.. c:function:: Message * forward_message_from_chat (Bot * bot, char * chat_id, long int from_chat_id,  long int message_id)

.. c:function:: Message * forward_message (Bot * bot, char * chat_id, char * from_chat_id,  long int message_id)

.. c:function:: Message * forward_message_chat (Bot * bot, long int chat_id, long int from_chat_id,  long int message_id)

.. c:function:: Message * send_photo(Bot * bot, char * chat_id, char * filename, char * caption,  long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * send_photo_chat(Bot * bot, long int chat_id, char * filename, char * caption, long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * send_audio(Bot *bot, char * chat_id, char * filename, char * caption, long int duration,  char * performer, char * title, long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_audio_chat(Bot * bot, long int chat_id, char * filename, char * caption, long int duration,  char * performer, char * title, long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_document(Bot * bot, char * chat_id, char * filename, char * caption,  long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_document_chat(Bot * bot, long int chat_id, char * filename, char * caption,  long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_video(Bot * bot, char * chat_id, char * video, long int duration, long int width,  long int height, char * caption, long int reply_to_message_id,   char * reply_markup)

.. c:function:: Message * send_video_chat(Bot * bot, long int chat_id, char * video, long int duration, long int width,  long int height, char * caption, long int reply_to_message_id,   char * reply_markup)

.. c:function:: Message * send_voice(Bot *bot, char * chat_id, char * filename, char * caption, long int duration,  long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_voice_chat(Bot *bot, long int chat_id, char * filename, char * caption, long int duration,  long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_video_note(Bot * bot, char * chat_id, char * filename, long int duration,  long int length, long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_video_note_chat(Bot * bot, long int chat_id, char * filename,  long int duration, long int length, long int reply_to_message_id,  char * reply_markup)

.. c:function:: Message * send_location (Bot * bot, char * chat_id, float latitude,   float longitude, long int live_period, long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * send_location_chat (Bot * bot, long int chat_id, float latitude, float logitude, long int live_period, long int reply_to_message_id,   char * reply_markup)

.. c:function:: Message * edit_message_live_location(Bot * bot, char * chat_id, long int message_id,  char * inline_message_id, float latitude, float longitude, char * reply_markup)

.. c:function:: Message * edit_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,  char * inline_message_id, float latitude, float longitude, char * reply_markup)

.. c:function:: Message * stop_message_live_location(Bot * bot, char * chat_id, long int message_id,   char * inline_message_id, char * reply_markup)

.. c:function:: Message * stop_message_live_location_chat(Bot * bot, long int chat_id, long int message_id,   char * inline_message_id, char * reply_markup)

.. c:function:: Message * send_venue(Bot * bot, char * chat_id, float latitude, float longitude,   char * title, char * address, char * foursquare_id, long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * send_venue_chat(Bot * bot, long int chat_id, float latitude, float longitude,   char * title, char * address, char * foursquare_id, long int reply_to_message_id, char * reply_markup)

.. c:function:: Message * send_contact(Bot * bot, char * chat_id, char * phone_number, char * first_name,   char * last_name, long int reply_to_message_id,   char * reply_markup)

.. c:function:: Message * send_contact_chat(Bot * bot, long int chat_id, char * phone_number, char * first_name,   char * last_name, long int reply_to_message_id,   char * reply_markup)

.. c:function:: int send_chat_action(Bot * bot, char * chat_id, char * action)

.. c:function:: int send_chat_action_chat(Bot * bot, long int chat_id, char * action)

.. c:function:: UserProfilePhotos * get_user_profile_photos(Bot * bot, char * dir, char *user_id, long offset, long limit)

.. c:function:: UserProfilePhotos * get_user_profile_photos_chat(Bot * bot, char * dir, long user_id, long offset, long limit)

.. c:function:: char * get_file(Bot * bot, char * dir, const char * file_id)

.. c:function:: bool kick_chat_member (Bot *bot, char *chat_id, long int user_id, char *until_date)

.. c:function:: bool kick_chat_member_chat (Bot *bot, long int chat_id, long int user_id, char *until_date)

.. c:function:: bool unban_chat_member (Bot *bot, char *chat_id, long int user_id)

.. c:function:: bool unban_chat_member_chat (Bot *bot, long int chat_id, long int user_id)

.. c:function:: bool restrict_chat_member (Bot *bot, char *chat_id, long int user_id,  long int until_date, bool can_send_messages,  bool can_send_media_messages, bool can_send_other_messages,  bool can_add_web_page_previews)

.. c:function:: bool restrict_chat_member_chat (Bot *bot, long int chat_id, long int user_id,  long int until_date, bool can_send_messages,  bool can_send_media_messages, bool can_send_other_messages,  bool can_add_web_page_previews)

.. c:function:: bool promote_chat_member (Bot *bot, char *chat_id, long int user_id, bool can_change_info,  bool can_post_messages, bool can_edit_messages, bool can_delete_messages,  bool can_invite_users, bool can_restrict_members, bool can_pin_messages,  bool can_promote_members)

.. c:function:: bool promote_chat_member_chat (Bot *bot, long int chat_id, long int user_id, bool can_change_info,  bool can_post_messages, bool can_edit_messages, bool can_delete_messages,  bool can_invite_users, bool can_restrict_members, bool can_pin_messages,  bool can_promote_members)

.. c:function:: char *export_chat_invite_link (Bot *bot, char *chat_id)

.. c:function:: char *export_chat_invite_link_chat (Bot *bot, long int chat_id)

.. c:function:: int set_chat_photo(Bot *bot, char * chat_id, char *filename)

.. c:function:: int set_chat_photo_chat(Bot *bot, long int chat_id, char *filename)

.. c:function:: int delete_chat_photo(Bot *bot, char *chat_id)

.. c:function:: int delete_chat_photo_chat(Bot *bot, long int chat_id)

.. c:function:: int set_chat_title (Bot *bot, char *chat_id, char *title)

.. c:function:: int set_chat_title_chat (Bot *bot, long int chat_id, char *title)

.. c:function:: bool set_chat_description (Bot *bot, char *chat_id, char *description)

.. c:function:: bool set_chat_description_chat (Bot *bot, long int chat_id, char *description)

.. c:function:: bool pin_chat_message (Bot *bot, char *chat_id, long int message_id, bool disable_notification)

.. c:function:: bool pin_chat_message_chat(Bot *bot, long int chat_id, long int message_id, bool disable_notification)

.. c:function:: bool unpin_chat_message(Bot *bot, char *chat_id)

.. c:function:: bool unpin_chat_message_chat(Bot *bot, long int chat_id)

.. c:function:: bool leave_chat (Bot *bot, char *chat_id)

.. c:function:: bool leave_chat_chat (Bot *bot, long int chat_id)

.. c:function:: Chat *get_chat(Bot *bot, char *chat_id)

.. c:function:: Chat *get_chat_chat(Bot *bot, long int chat_id)

.. c:function:: ChatMember *get_chat_administrators (Bot *bot, char *chat_id)

.. c:function:: ChatMember *get_chat_administrators_chat(Bot *bot, long int chat_id)

.. c:function:: int get_chat_members_count (Bot *bot, char *chat_id)

.. c:function:: int get_chat_members_count_chat (Bot *bot, long int chat_id)

.. c:function:: ChatMember *get_chat_member(Bot *bot, char *chat_id, long int user_id)

.. c:function:: ChatMember *get_chat_member_chat(Bot *bot, long int chat_id, long int user_id)

.. c:function:: Message *edit_message_text(Bot *bot, char *chat_id, long int message_id, char *inline_message_id, char *text, char *parse_mode, bool disable_web_page_preview, char *reply_markup)

.. c:function:: Message *edit_message_text_chat(Bot *bot, long int chat_id, long int message_id, char *inline_message_id, char *text, char *parse_mode, bool disable_web_page_preview, char *reply_markup)

.. c:function:: Message *edit_message_caption(Bot *bot, char *chat_id, long int message_id, char *inline_message_id, char *caption, char *reply_markup)

.. c:function:: Message *edit_message_caption_chat(Bot *bot, long int chat_id, long int message_id, char *inline_message_id, char *caption, char *reply_markup)

.. c:function:: Message *edit_message_reply_markup(Bot *bot, char *chat_id, long int message_id,  char *inline_message_id, char *reply_markup)

.. c:function:: Message *edit_message_reply_markup_chat(Bot *bot, long int chat_id, long int message_id,  char *inline_message_id, char *reply_markup)

.. c:function:: bool answerInlineQuery( Bot *bot, char *inline_query_id, char *results, long int cache_time, bool is_personal, char *next_offset, char *switch_pm_text, char *switch_pm_parameter)

.. c:function:: void set_notification(bool disable_notification)

.. c:function:: bool get_notification()

.. c:function:: void set_parse_mode(int32_t mode)

.. c:function:: int32_t get_parse_mode()

