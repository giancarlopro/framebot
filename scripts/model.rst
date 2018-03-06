
.. c:type:: Error

	.. c:member:: long int error_code

	.. c:member:: char *description

.. c:type:: User

	.. c:member:: long int id

	.. c:member:: bool is_bot

	.. c:member:: char *first_name

	.. c:member:: char *last_name

	.. c:member:: char *username

	.. c:member:: char *language_code

	.. c:member:: struct _user *next

.. c:type:: Bot

	.. c:member:: char *token

	.. c:member:: User *user

.. c:type:: ChatPhoto

	.. c:member:: char *small_file_id

	.. c:member:: char *big_file_id

.. c:type:: Chat

	.. c:member:: long int id

	.. c:member:: char *type

	.. c:member:: char *title

	.. c:member:: char *username

	.. c:member:: char *first_name

	.. c:member:: char *last_name

	.. c:member:: bool all_members_are_administrators

	.. c:member:: ChatPhoto *photo

	.. c:member:: char *description

	.. c:member:: char *invite_link

	.. c:member:: struct _message *pinned_message

	.. c:member:: char *sticker_set_name

	.. c:member:: bool can_set_sticker_set

.. c:type:: MessageEntity

	.. c:member:: char *type

	.. c:member:: long int offset

	.. c:member:: long int length

	.. c:member:: char *url

	.. c:member:: User *user

	.. c:member:: struct _message_entity *next

.. c:type:: Audio

	.. c:member:: char *file_id

	.. c:member:: long int duration

	.. c:member:: char *performer

	.. c:member:: char *title

	.. c:member:: char *mime_type

	.. c:member:: long int file_size

.. c:type:: PhotoSize

	.. c:member:: char *file_id

	.. c:member:: int width

	.. c:member:: int height

	.. c:member:: long int file_size

	.. c:member:: struct _photo_size *next

.. c:type:: Game

	.. c:member:: char *file_id

	.. c:member:: PhotoSize *thumb

	.. c:member:: char *file_name

	.. c:member:: char *mime_type

	.. c:member:: long int file_size

	.. c:member:: char *title

	.. c:member:: char *description

	.. c:member:: char *text

	.. c:member:: Animation *animation

.. c:type:: Sticker

	.. c:member:: char *file_id

	.. c:member:: int width

	.. c:member:: int height

	.. c:member:: PhotoSize *thumb

	.. c:member:: char *emoji

	.. c:member:: long int file_size

.. c:type:: Video

	.. c:member:: char *file_id

	.. c:member:: int width

	.. c:member:: int height

	.. c:member:: long int duration

	.. c:member:: PhotoSize *thumb

	.. c:member:: char *mime_type

	.. c:member:: long int file_size

.. c:type:: VideoNote

	.. c:member:: char *file_id

	.. c:member:: long length

	.. c:member:: long duration

	.. c:member:: PhotoSize *thumb

	.. c:member:: long file_size

.. c:type:: Voice

	.. c:member:: char *file_id

	.. c:member:: long int duration

	.. c:member:: char *mime_type

	.. c:member:: long int file_size

.. c:type:: Contact

	.. c:member:: char *phone_number

	.. c:member:: char *first_name

	.. c:member:: char *last_name

	.. c:member:: long int user_id

.. c:type:: Location

	.. c:member:: float latitude

	.. c:member:: float longitude

.. c:type:: Venue

	.. c:member:: Location *location

	.. c:member:: char *title

	.. c:member:: char *address

	.. c:member:: char *foursquare_id

.. c:type:: Invoice

	.. c:member:: char *title

	.. c:member:: char *description

	.. c:member:: char *start_parameter

	.. c:member:: char *currency

	.. c:member:: long total_amount

.. c:type:: ShippingAddress

	.. c:member:: char *country_code

	.. c:member:: char *state

	.. c:member:: char *city

	.. c:member:: char *street_line1

	.. c:member:: char *street_line2

	.. c:member:: char *post_code

.. c:type:: OrderInfo

	.. c:member:: char *name

	.. c:member:: char *phone_number

	.. c:member:: char *email

	.. c:member:: ShippingAddress *shipping_address

.. c:type:: SuccessfulPayment

	.. c:member:: char *currency

	.. c:member:: long total_amount

	.. c:member:: char *invoice_payload

	.. c:member:: char *shipping_option_id

	.. c:member:: OrderInfo *order_info

	.. c:member:: char *telegram_payment_charge_id

	.. c:member:: char *provider_payment_charge_id

.. c:type:: ShippingQuery

	.. c:member:: char *id

	.. c:member:: User *from

	.. c:member:: char *invoice_payload

	.. c:member:: ShippingAddress *shipping_address

.. c:type:: PreCheckoutQuery

	.. c:member:: char *id

	.. c:member:: User *from

	.. c:member:: char *currency

	.. c:member:: long total_amount

	.. c:member:: char *invoice_payload

	.. c:member:: char *shipping_option_id

	.. c:member:: OrderInfo *order_info

.. c:type:: Message

	.. c:member:: long int message_id

	.. c:member:: User *from

	.. c:member:: long int date

	.. c:member:: Chat *chat

	.. c:member:: User *forward_from

	.. c:member:: Chat *forward_from_chat

	.. c:member:: long int forward_from_message_id

	.. c:member:: char *forward_signature

	.. c:member:: long int forward_date

	.. c:member:: struct _message *reply_to_message

	.. c:member:: long int edit_date

	.. c:member:: char *media_group_id

	.. c:member:: char *author_signature

	.. c:member:: char *text

	.. c:member:: MessageEntity *caption_entities

	.. c:member:: Audio *audio

	.. c:member:: Document *document

	.. c:member:: Game *game

	.. c:member:: Sticker *sticker

	.. c:member:: Video *video

	.. c:member:: Voice *voice

	.. c:member:: VideoNote *video_note

	.. c:member:: char *caption

	.. c:member:: Contact *contact

	.. c:member:: Location *location

	.. c:member:: Venue *venue

	.. c:member:: User *new_chat_members

	.. c:member:: User *left_chat_member

	.. c:member:: char *new_chat_title

	.. c:member:: bool delete_chat_photo

	.. c:member:: bool group_chat_created

	.. c:member:: bool supergroup_chat_created

	.. c:member:: bool channel_chat_created

	.. c:member:: long int migrate_to_chat_id

	.. c:member:: long int migrate_from_chat_id

	.. c:member:: struct _message *pinned_message

	.. c:member:: Invoice *invoice

	.. c:member:: SuccessfulPayment *successful_payment

	.. c:member:: char *connected_website

.. c:type:: InlineQuery

	.. c:member:: char *id

	.. c:member:: User *from

	.. c:member:: Location *location

	.. c:member:: char *query

	.. c:member:: char *offset

.. c:type:: ChosenInlineResult

	.. c:member:: char *result_id

	.. c:member:: User *from

	.. c:member:: Location *location

	.. c:member:: char *inline_message_id

	.. c:member:: char *query

.. c:type:: CallbackQuery

	.. c:member:: char *id

	.. c:member:: User *from

	.. c:member:: Message *message

	.. c:member:: char *inline_message_id

	.. c:member:: char *chat_instance

	.. c:member:: char *data

	.. c:member:: char *game_short_name

.. c:type:: Framebot

	.. c:member:: long int update_id

	.. c:member:: Message *message

	.. c:member:: Message *edited_message

	.. c:member:: Message *channel_post

	.. c:member:: Message *edited_channel_post

	.. c:member:: InlineQuery *inline_query

	.. c:member:: ChosenInlineResult *chosen_inline_result

	.. c:member:: CallbackQuery *callback_query

	.. c:member:: ShippingQuery *shipping_query

	.. c:member:: PreCheckoutQuery *pre_checkout_query

	.. c:member:: struct _update *next

	.. c:member:: long int update_id

	.. c:member:: UPMessage *message

	.. c:member:: UPMessage *edited_message

	.. c:member:: UPMessage *channel_post

	.. c:member:: UPMessage *edited_channel_post

	.. c:member:: UPIResult *chosen_inline_result

	.. c:member:: UPPCQuery *pre_checkout_query

.. c:type:: ChatMember

	.. c:member:: User *user

	.. c:member:: char *status

	.. c:member:: long int until_date

	.. c:member:: bool can_be_edited

	.. c:member:: bool can_change_info

	.. c:member:: bool can_post_messages

	.. c:member:: bool can_edit_messages

	.. c:member:: bool can_delete_messages

	.. c:member:: bool can_invite_users

	.. c:member:: bool can_restrict_members

	.. c:member:: bool can_pin_messages

	.. c:member:: bool can_promote_members

	.. c:member:: bool can_send_messages

	.. c:member:: bool can_send_media_messages

	.. c:member:: bool can_send_other_messages

	.. c:member:: bool can_add_web_page_previews

	.. c:member:: struct _chat_member *next

.. c:type:: File

	.. c:member:: char *file_id

	.. c:member:: long file_size

	.. c:member:: char *file_path

.. c:type:: UserProfilePhotos

	.. c:member:: long total_count

.. c:type:: CallbackGame

	.. c:member:: long int user_id

	.. c:member:: long int score

	.. c:member:: bool force

	.. c:member:: bool disable_edit_message

	.. c:member:: long int chat_id

	.. c:member:: long int message_id

	.. c:member:: char *inline_message_id

.. c:type:: KeyboardButton

	.. c:member:: char *text

	.. c:member:: bool request_contact

	.. c:member:: bool request_location

	.. c:member:: struct _keyboard_button *next

.. c:type:: InlineKeyboardButton

	.. c:member:: char *text

	.. c:member:: char *url

	.. c:member:: char *callback_data

	.. c:member:: char *switch_nline_query

	.. c:member:: char *switch_inline_query_current_chat

	.. c:member:: CallbackGame *callback_game

	.. c:member:: bool pay

.. c:type:: InlineKeyboardMarkup

	.. c:member:: int type

.. c:type:: ReplyKeyboardMarkup

	.. c:member:: int type

	.. c:member:: bool resize_keyboard

	.. c:member:: bool one_time_keyboard

	.. c:member:: bool selective

.. c:type:: ReplyKeyboardRemove

	.. c:member:: int type

	.. c:member:: bool remove_keyboard

	.. c:member:: bool selective

.. c:type:: ForceReply

	.. c:member:: int type

	.. c:member:: bool force_reply

	.. c:member:: bool selective

.. c:type:: Keyboard

	.. c:member:: int type

	.. c:member:: InlineKeyboardButton *inline_keyboard_markup

	.. c:member:: ReplyKeyboardMarkup *reply_keyboard_markup

	.. c:member:: ReplyKeyboardRemove *reply_keyboard_remove

	.. c:member:: ForceReply *_force_reply
