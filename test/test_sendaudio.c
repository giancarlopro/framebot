#include <telebot.h>

#define BOLD         "\033[1m"
#define COLOR_RESET  "\033[0m"
#define BLACK  "\033[22;30m"
#define RED    "\033[22;31m"
#define GREEN  "\033[22;32m"
#define BROWN  "\033[22;33m"
#define BLUE   "\033[22;34m"
#define MAGENTA "\033[22;35m"
#define CYAN   "\033[22;36m"
#define GRAY   "\033[22;37m"
#define DARK_GRAY "\033[01;30m"
#define LIGHT_RED "\033[01;31m"
#define LIGHT_GREEN "\033[01;32m"
#define YELLOW "\033[01;33m"
#define LIGHT_BLUE "\033[01;34m"
#define LIGHT_MAGENTA "\033[01;35m"
#define LIGHT_CYAN "\033[01;36m"
#define WHITE "\033[01;37m"


Bot * _bot;

void read_message(Message * message){
	printf(BLUE"\tmessage_id = %lu\n"COLOR_RESET, message->message_id);
	if(message->from){
		printf(BLUE"\ttfrom = (type User)\n"COLOR_RESET);
		printf(BLUE"\ttfrom->id = %ld\n"COLOR_RESET, message->from->id);
	}
	else{
		printf("\ttfrom = NULL\n"COLOR_RESET);
	}

	if(message->date)
		printf(BLUE"\ttdate = %ld\n"COLOR_RESET, message->date);
	else
		printf("\ttdate = NULL\n"COLOR_RESET);

	if(message->chat)
		printf(BLUE"\ttchat = (type Chat)\n"COLOR_RESET);
	else
		printf("\ttchat = NULL\n"COLOR_RESET);

	if(message->forward_from)
		printf(BLUE"\ttforward_from = (type User)\n"COLOR_RESET);
	else
		printf("\ttforward_from = NULL\n"COLOR_RESET);

	if(message->forward_from_chat)
		printf(BLUE"\ttforward_from_chat = (type Chat)\n"COLOR_RESET);
	else
		printf("\ttforward_from_chat = NULL\n"COLOR_RESET);

	if(message->forward_from_message_id)
		printf(BLUE"\tforward_from_message_id = %ld\n"COLOR_RESET, message->forward_from_message_id);
	else
		printf("\tforward_from_message_id = NULL\n"COLOR_RESET);

	if(message->forward_signature)
		printf(BLUE"\tforward_signature = %s\n"COLOR_RESET, message->forward_signature);
	else
		printf("\tforward_signature = NULL\n"COLOR_RESET);

	if(message->forward_date)
		printf(BLUE"\tforward_date = %ld\n"COLOR_RESET, message->forward_date);
	else
		printf("\tforward_date = NULL\n"COLOR_RESET);

	if(message->reply_to_message)
		printf(BLUE"\treply_to_message = (type Message)\n"COLOR_RESET);
	else
		printf("\treply_to_message = NULL\n"COLOR_RESET);
		
	if(message->edit_date)
		printf(BLUE"\tedit_date = %ld\n"COLOR_RESET, message->edit_date);
	else
		printf("\tedit_date = NULL\n"COLOR_RESET);

	if(message->author_signature)
		printf(BLUE"\tauthor_signature = %s\n"COLOR_RESET, message->author_signature);
	else
		printf("\tauthor_signature = NULL\n"COLOR_RESET);

	if(message->text)
		printf(BLUE"\ttext = %s\n"COLOR_RESET, message->text);
	else
		printf("\ttext = NULL\n"COLOR_RESET);

	if(message->entities)
		printf(BLUE"\tentities = (type MessageEntities)\n"COLOR_RESET);
	else
		printf("\tentities = NULL\n"COLOR_RESET);

	if(message->caption_entities)
		printf(BLUE"\tcaption_entities = (type MessageEntities)\n"COLOR_RESET);
	else
		printf("\tcaption_entities = NULL\n"COLOR_RESET);

	if(message->audio)
		printf(BLUE"\taudio = (type Audio)\n"COLOR_RESET);
	else
		printf("\taudio = NULL\n"COLOR_RESET);

	if(message->document)
		printf(BLUE"\tdocument = (type Document)\n"COLOR_RESET);
	else
		printf("\tdocument = NULL\n"COLOR_RESET);

	if(message->game)
		printf(BLUE"\tgame = (type Game)\n"COLOR_RESET);
	else
		printf("\tgame = NULL\n"COLOR_RESET);

	if(message->photo)
		printf(BLUE"\tphoto = (type PhotoSize)\n"COLOR_RESET);
	else
		printf("\tphoto = NULL\n"COLOR_RESET);

	if(message->sticker)
		printf(BLUE"\tsticker = (type Sticker)\n"COLOR_RESET);
	else
		printf("\tsticker = NULL\n"COLOR_RESET);

	if(message->video)
		printf(BLUE"\tvideo = (type Video)\n"COLOR_RESET);
	else
		printf("\tvideo = NULL\n"COLOR_RESET);

	if(message->voice)
		printf(BLUE"\tvoice = (type Voice)\n"COLOR_RESET);
	else
		printf("\tvoice = NULL\n"COLOR_RESET);

	if(message->video_note)
		printf(BLUE"\tvideo_note = (type VideoNote)\n"COLOR_RESET);
	else
		printf("\tvideo_note = NULL\n"COLOR_RESET);

	if(message->caption)
		printf(BLUE"\tcaption = %s\n"COLOR_RESET, message->caption);
	else
		printf("\tcaption = NULL\n"COLOR_RESET);

	if(message->contact)
		printf(BLUE"\tcontact = (type Contact)\n"COLOR_RESET);
	else
		printf("\tcontact = NULL\n"COLOR_RESET);

	if(message->location)
		printf(BLUE"\tlocation = (type Location)\n"COLOR_RESET);
	else
		printf("\tlocation = NULL\n"COLOR_RESET);

	if(message->venue)
		printf(BLUE"\tvenue = (type Venue)\n"COLOR_RESET);
	else
		printf("\tvenue = NULL\n"COLOR_RESET);

	if(message->new_chat_member)
		printf(BLUE"\tnew_chat_member = (type User)\n"COLOR_RESET);
	else
		printf("\tnew_chat_member = NULL\n"COLOR_RESET);

	if(message->left_chat_member)
		printf(BLUE"\tleft_chat_member = (type User)\n"COLOR_RESET);
	else
		printf("\tleft_chat_member = NULL\n"COLOR_RESET);

	if(message->new_chat_title)
		printf(BLUE"\tnew_chat_title = %s\n"COLOR_RESET, message->new_chat_title);
	else
		printf("\tnew_chat_title = NULL\n"COLOR_RESET);

	if(message->new_chat_photo)
		printf(BLUE"\tnew_chat_photo = (type PhotoSize)\n"COLOR_RESET);
	else
		printf("\tnew_chat_photo = NULL\n"COLOR_RESET);

	if(message->delete_chat_photo)
		printf(BLUE"\tdelete_chat_photo = %d\n"COLOR_RESET, message->delete_chat_photo);
	else
		printf("\tdelete_chat_photo = NULL\n"COLOR_RESET);

	if(message->group_chat_created)
		printf(BLUE"\tgroup_chat_created = %d\n"COLOR_RESET, message->group_chat_created);
	else
		printf("\tgroup_chat_created = NULL\n"COLOR_RESET);

	if(message->supergroup_chat_created)
		printf(BLUE"\tsupergroup_chat_created = %d\n"COLOR_RESET, message->supergroup_chat_created);
	else
		printf("\tsupergroup_chat_created = NULL\n"COLOR_RESET);

	if(message->channel_chat_created)
		printf(BLUE"\tchannel_chat_created = %d\n"COLOR_RESET, message->channel_chat_created);
	else
		printf("\tchannel_chat_created = NULL\n"COLOR_RESET);

	if(message->migrate_to_chat_id)
		printf(BLUE"\tmigrate_to_chat_id = %ld\n"COLOR_RESET, message->migrate_to_chat_id);
	else
		printf("\tmigrate_to_chat_id = NULL\n"COLOR_RESET);

	if(message->migrate_from_chat_id)
		printf(BLUE"\tmigrate_from_chat_id = %ld\n"COLOR_RESET);
	else
		printf("\tmigrate_from_chat_id = NULL\n"COLOR_RESET);

	if(message->pinned_message)
		printf(BLUE"\tpinned_message = (type Message)\n"COLOR_RESET);
	else
		printf("\tpinned_message = NULL\n"COLOR_RESET);

	if(message->invoice)
		printf(BLUE"\tinvoice = (type Invoice)\n"COLOR_RESET);
	else
		printf("\tinvoice = NULL\n"COLOR_RESET);

	if(message->successful_payment)
		printf(BLUE"\tsuccessful_payment = (type SuccessfulPayment)\n"COLOR_RESET);
	else
		printf("\tsuccessful_payment = NULL\n"COLOR_RESET);
}


int main(int argc, char *argv[]){
	telebot_init();

	if(argc != 2)
		fprintf(stderr, "sendphoto <token>");

    _bot = telebot(argv[1]);

/* Message * send_photo_chat(Bot * bot, long int chat_id, char * filename,
			  char * caption, bool disable_notification,
			  long int reply_to_message_id){
*/
	Message * message = send_audio_chat(_bot, 100856717, "mp3.mp3", "descrição", 0, NULL, NULL, 0, 0, NULL);

	if(message){
		read_message(message);
	}
	else{
		Error * error = show_error();
		if(error)
			printf("ec=%ld d=%s", error->error_code, error->description);
	}

	return 0;
}
