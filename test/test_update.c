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

const char *token;
const char *type_struct[] = {"update", "message", "messageentity", "photosize",
"document", "game", "sticker", "video", "voice", "contact", "location",
"venue", "animation", "inlinequery", "choseninlineresult", "callbackquery",
"chatmember", "file", "userprofilephotos", "precheckoutquery", "shippingquery",
"successfulpayment", "orderinfo", "shippingaddress", "invoice", "contact",
"videonote", "photosize", "user", "chat", "audio"};

const char * variable_update[] = {"message", "edited_message", "channel_post", "edited_channel_post",
"inline_query", "chosen_inline_result", "callback_query", "shipping_query"};

void read_message(Update * update){
	Message * message[] = {update->message, update->edited_message,
		update->channel_post, update->edited_channel_post};
	size_t i = 0;

	while(i < 4){
		if(message[i]){
			printf(GREEN"\n type Message\n", i);
			if(i == 0)
				printf(" update->message\n" COLOR_RESET);
			else if(i == 1)
				printf(" update->edited_message\n" COLOR_RESET);
			else if(i == 2)
				printf(" update->channel_post\n" COLOR_RESET);
			else if(i == 3)
				printf(" update->edited_channel_post\n" COLOR_RESET);

			printf(BLUE"\tmessage_id = %lu\n"COLOR_RESET, message[i]->message_id);
			if(message[i]->from){
				printf(BLUE"\ttfrom = (type User)\n"COLOR_RESET);
				printf(BLUE"\ttfrom->id = %ld\n"COLOR_RESET, message[i]->from->id);
			}
			else{
				printf("\ttfrom = NULL\n"COLOR_RESET);
			}

			if(message[i]->date)
				printf(BLUE"\ttdate = %ld\n"COLOR_RESET, message[i]->date);
			else
				printf("\ttdate = NULL\n"COLOR_RESET);

			if(message[i]->chat)
				printf(BLUE"\ttchat = (type Chat)\n"COLOR_RESET);
			else
				printf("\ttchat = NULL\n"COLOR_RESET);

			if(message[i]->forward_from)
				printf(BLUE"\ttforward_from = (type User)\n"COLOR_RESET);
			else
				printf("\ttforward_from = NULL\n"COLOR_RESET);

			if(message[i]->forward_from_chat)
				printf(BLUE"\ttforward_from_chat = (type Chat)\n"COLOR_RESET);
			else
				printf("\ttforward_from_chat = NULL\n"COLOR_RESET);

			if(message[i]->forward_from_message_id)
				printf(BLUE"\tforward_from_message_id = %ld\n"COLOR_RESET, message[i]->forward_from_message_id);
			else
				printf("\tforward_from_message_id = NULL\n"COLOR_RESET);

			if(message[i]->forward_signature)
				printf(BLUE"\tforward_signature = %s\n"COLOR_RESET, message[i]->forward_signature);
			else
				printf("\tforward_signature = NULL\n"COLOR_RESET);

			if(message[i]->forward_date)
				printf(BLUE"\tforward_date = %ld\n"COLOR_RESET, message[i]->forward_date);
			else
				printf("\tforward_date = NULL\n"COLOR_RESET);

			if(message[i]->reply_to_message)
				printf(BLUE"\treply_to_message = (type Message)\n"COLOR_RESET);
			else
				printf("\treply_to_message = NULL\n"COLOR_RESET);
		
			if(message[i]->edit_date)
				printf(BLUE"\tedit_date = %ld\n"COLOR_RESET, message[i]->edit_date);
			else
				printf("\tedit_date = NULL\n"COLOR_RESET);

			if(message[i]->author_signature)
				printf(BLUE"\tauthor_signature = %s\n"COLOR_RESET, message[i]->author_signature);
			else
				printf("\tauthor_signature = NULL\n"COLOR_RESET);

			if(message[i]->text)
				printf(BLUE"\ttext = %s\n"COLOR_RESET, message[i]->text);
			else
				printf("\ttext = NULL\n"COLOR_RESET);

			if(message[i]->entities)
				printf(BLUE"\tentities = (type MessageEntities)\n"COLOR_RESET);
			else
				printf("\tentities = NULL\n"COLOR_RESET);

			if(message[i]->caption_entities)
				printf(BLUE"\tcaption_entities = (type MessageEntities)\n"COLOR_RESET);
			else
				printf("\tcaption_entities = NULL\n"COLOR_RESET);

			if(message[i]->audio)
				printf(BLUE"\taudio = (type Audio)\n"COLOR_RESET);
			else
				printf("\taudio = NULL\n"COLOR_RESET);

			if(message[i]->document)
				printf(BLUE"\tdocument = (type Document)\n"COLOR_RESET);
			else
				printf("\tdocument = NULL\n"COLOR_RESET);

			if(message[i]->game)
				printf(BLUE"\tgame = (type Game)\n"COLOR_RESET);
			else
				printf("\tgame = NULL\n"COLOR_RESET);

			if(message[i]->photo)
				printf(BLUE"\tphoto = (type PhotoSize)\n"COLOR_RESET);
			else
				printf("\tphoto = NULL\n"COLOR_RESET);

			if(message[i]->sticker)
				printf(BLUE"\tsticker = (type Sticker)\n"COLOR_RESET);
			else
				printf("\tsticker = NULL\n"COLOR_RESET);

			if(message[i]->video)
				printf(BLUE"\tvideo = (type Video)\n"COLOR_RESET);
			else
				printf("\tvideo = NULL\n"COLOR_RESET);

			if(message[i]->voice)
				printf(BLUE"\tvoice = (type Voice)\n"COLOR_RESET);
			else
				printf("\tvoice = NULL\n"COLOR_RESET);

			if(message[i]->video_note)
				printf(BLUE"\tvideo_note = (type VideoNote)\n"COLOR_RESET);
			else
				printf("\tvideo_note = NULL\n"COLOR_RESET);

			if(message[i]->caption)
				printf(BLUE"\tcaption = %s\n"COLOR_RESET, message[i]->caption);
			else
				printf("\tcaption = NULL\n"COLOR_RESET);

			if(message[i]->contact)
				printf(BLUE"\tcontact = (type Contact)\n"COLOR_RESET);
			else
				printf("\tcontact = NULL\n"COLOR_RESET);

			if(message[i]->location)
				printf(BLUE"\tlocation = (type Location)\n"COLOR_RESET);
			else
				printf("\tlocation = NULL\n"COLOR_RESET);

			if(message[i]->venue)
				printf(BLUE"\tvenue = (type Venue)\n"COLOR_RESET);
			else
				printf("\tvenue = NULL\n"COLOR_RESET);

			if(message[i]->new_chat_member)
				printf(BLUE"\tnew_chat_member = (type User)\n"COLOR_RESET);
			else
				printf("\tnew_chat_member = NULL\n"COLOR_RESET);

			if(message[i]->left_chat_member)
				printf(BLUE"\tleft_chat_member = (type User)\n"COLOR_RESET);
			else
				printf("\tleft_chat_member = NULL\n"COLOR_RESET);

			if(message[i]->new_chat_title)
				printf(BLUE"\tnew_chat_title = %s\n"COLOR_RESET, message[i]->new_chat_title);
			else
				printf("\tnew_chat_title = NULL\n"COLOR_RESET);

			if(message[i]->new_chat_photo)
				printf(BLUE"\tnew_chat_photo = (type PhotoSize)\n"COLOR_RESET);
			else
				printf("\tnew_chat_photo = NULL\n"COLOR_RESET);

			if(message[i]->delete_chat_photo)
				printf(BLUE"\tdelete_chat_photo = %d\n"COLOR_RESET, message[i]->delete_chat_photo);
			else
				printf("\tdelete_chat_photo = NULL\n"COLOR_RESET);

			if(message[i]->group_chat_created)
				printf(BLUE"\tgroup_chat_created = %d\n"COLOR_RESET, message[i]->group_chat_created);
			else
				printf("\tgroup_chat_created = NULL\n"COLOR_RESET);

			if(message[i]->supergroup_chat_created)
				printf(BLUE"\tsupergroup_chat_created = %d\n"COLOR_RESET, message[i]->supergroup_chat_created);
			else
				printf("\tsupergroup_chat_created = NULL\n"COLOR_RESET);

			if(message[i]->channel_chat_created)
				printf(BLUE"\tchannel_chat_created = %d\n"COLOR_RESET, message[i]->channel_chat_created);
			else
				printf("\tchannel_chat_created = NULL\n"COLOR_RESET);

			if(message[i]->migrate_to_chat_id)
				printf(BLUE"\tmigrate_to_chat_id = %ld\n"COLOR_RESET, message[i]->migrate_to_chat_id);
			else
				printf("\tmigrate_to_chat_id = NULL\n"COLOR_RESET);

			if(message[i]->migrate_from_chat_id)
				printf(BLUE"\tmigrate_from_chat_id = %ld\n"COLOR_RESET);
			else
				printf("\tmigrate_from_chat_id = NULL\n"COLOR_RESET);

			if(message[i]->pinned_message)
				printf(BLUE"\tpinned_message = (type Message)\n"COLOR_RESET);
			else
				printf("\tpinned_message = NULL\n"COLOR_RESET);

			if(message[i]->invoice)
				printf(BLUE"\tinvoice = (type Invoice)\n"COLOR_RESET);
			else
				printf("\tinvoice = NULL\n"COLOR_RESET);

			if(message[i]->successful_payment)
				printf(BLUE"\tsuccessful_payment = (type SuccessfulPayment)\n"COLOR_RESET);
			else
				printf("\tsuccessful_payment = NULL\n"COLOR_RESET);
		}

		i++;
	}
}

void read_update(Update * update){

	/*update*/
	printf(GREEN"\n\n type Update\n");
	printf(" update\n"COLOR_RESET);
	printf(BLUE"\tupdate_id = %ld\n"COLOR_RESET, update->update_id);
	if(update->message){
		printf(BLUE"\tmessage = (type Message)\n"COLOR_RESET);
	}
	else{
		printf("\tmessage = NULL\n"COLOR_RESET);
	}

	fflush(stdout);
	if(update->edited_message){
		printf(BLUE"\tedited_message = (type Message)\n"COLOR_RESET);
	}
	else{
		printf("\tedited_message = NULL\n"COLOR_RESET);
	}


	if(update->channel_post){
		printf(BLUE"\tchannel_post = (type Message)\n"COLOR_RESET);
	}
	else{
		printf("\tchannel_post = NULL\n"COLOR_RESET);
	}


	if(update->edited_channel_post){
		printf(BLUE"\tedited_channel_post = (type Message)\n"COLOR_RESET);
	}
	else{
		printf("\tedited_channel_post = NULL\n"COLOR_RESET);
	}


	if(update->inline_query){
		printf(BLUE"\tinline_query = (type InlineQuery)\n"COLOR_RESET);
	}
	else{
		printf("\tinline_query = NULL\n"COLOR_RESET);
	}


	if(update->chosen_inline_result){
		printf(BLUE"\tchosen_inline_result = (type ChosenInlineResult)\n"COLOR_RESET);
	}
	else{
		printf("\tchosen_inline_result = NULL\n"COLOR_RESET);
	}


	if(update->callback_query)
		printf(BLUE"\tcallback_query = (type CallbackQuery)\n"COLOR_RESET);
	else{
		printf("\tcallback_query = NULL\n"COLOR_RESET);
	}

	if(update->shipping_query){
		printf(BLUE"\tshipping_query = (type shipping_query)\n"COLOR_RESET);
	}
	else{
		printf("\tshipping_query = NULL\n"COLOR_RESET);
	}

	if(update->pre_checkout_query)
		printf(BLUE"\tpre_checkout_query = (type pre_checkout_query)\n"COLOR_RESET);
	else
		printf("\tpre_checkout_query = NULL\n"COLOR_RESET);

	read_message(update);
}

void read_struct(char * name_struct){

}

void update_init(Update * update){

}

int main(int argc, char **argv){
	size_t update_length, i;
	telebot_init();

	if(argc != 2)
		fprintf(stderr, "update <token>");


    Bot *bot = telebot(argv[1]);

	Update * update = get_updates(bot, NULL);

	update_length = update_len(update);
	printf(BLUE"length = %lu"COLOR_RESET, update_length);

	for(i = 0; update; i++){
		printf("\npress enter for the show update");
		getchar();
		read_update(update);
		if(update->next)
			printf("next . . .\n");
		update = update->next;

	}

	return 0;
}