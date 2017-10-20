#include <telebot.h>

const char *token;

void read_message(Update * update){
	Message * message[] = {update->message, update->edited_message,
		update->channel_post, update->edited_channel_post};
	size_t i = 0;

	while(i < 4){
		if(message[i]){
			printf("\ntype Message\n");
			printf("\tmessage_id=%lu\n");
			if(message[i]->from)
				printf("\ttfrom=(type User)\n");
			else
				printf("\ttfrom=NULL\n");

			if(message[i]->date)
				printf("\ttdate=%ld\n", message[i]->date);
			else
				printf("\ttdate=NULL\n");

			if(message[i]->chat)
				printf("\ttchat=(type Chat)\n");
			else
				printf("\ttchat=NULL\n");

			if(message[i]->forward_from)
				printf("\ttforward_from=(type User)\n");
			else
				printf("\ttforward_from=NULL\n");

			if(message[i]->forward_from_chat)
				printf("\ttforward_from_chat=(type Chat)\n");
			else
				printf("\ttforward_from_chat=NULL\n");

			if(message[i]->forward_from_message_id)
				printf("\tforward_from_message_id=%ld\n", message[i]->forward_from_message_id);
			else
				printf("\tforward_from_message_id=NULL\n");

			if(message[i]->forward_signature)
				printf("\tforward_signature=%s\n", message[i]->forward_signature);
			else
				printf("\tforward_signature=NULL\n");

			if(message[i]->forward_date)
				printf("\tforward_date=%ld\n", message[i]->forward_date);
			else
				printf("\tforward_date=NULL\n");

			if(message[i]->reply_to_message)
				printf("\treply_to_message=(type Message)\n");
			else
				printf("\treply_to_message=NULL\n");
		
			if(message[i]->edit_date)
				printf("\tedit_date=%ld\n", message[i]->edit_date);
			else
				printf("\tedit_date=NULL\n");

			if(message[i]->author_signature)
				printf("\tauthor_signature=%s\n", message[i]->author_signature);
			else
				printf("\tauthor_signature=NULL\n");

			if(message[i]->text)
				printf("\ttext=%s\n", message[i]->text);
			else
				printf("\ttext=NULL\n");

			if(message[i]->entities)
				printf("\tentities=(type MessageEntities)\n");
			else
				printf("\tentities=NULL\n");

			if(message[i]->caption_entities)
				printf("\tcaption_entities=(type MessageEntities)\n");
			else
				printf("\tcaption_entities=NULL\n");

			if(message[i]->audio)
				printf("\taudio=(type Audio)\n");
			else
				printf("\taudio=NULL\n");

			if(message[i]->document)
				printf("\tdocument=(type Document)\n");
			else
				printf("\tdocument=NULL\n");

			if(message[i]->game)
				printf("\tgame=(type Game)\n");
			else
				printf("\tgame=NULL\n");

			if(message[i]->photo)
				printf("\tphoto=(type PhotoSize)\n");
			else
				printf("\tphoto=NULL\n");

			if(message[i]->sticker)
				printf("\tsticker=(type Sticker)\n");
			else
				printf("\tsticker=NULL\n");

			if(message[i]->video)
				printf("\tvideo=(type Video)\n");
			else
				printf("\tvideo=NULL\n");

			if(message[i]->voice)
				printf("\tvoice=(type Voice)\n");
			else
				printf("\tvoice=NULL\n");

			if(message[i]->video_note)
				printf("\tvideo_note=(type VideoNote)\n");
			else
				printf("\tvideo_note=NULL\n");

			if(message[i]->caption)
				printf("\tcaption=%s\n", message[i]->caption);
			else
				printf("\tcaption=NULL\n");

			if(message[i]->contact)
				printf("\tcontact=(type Contact)\n");
			else
				printf("\tcontact=NULL\n");

			if(message[i]->location)
				printf("\tlocation=(type Location)\n");
			else
				printf("\tlocation=NULL\n");

			if(message[i]->venue)
				printf("\tvenue=(type Venue)\n");
			else
				printf("\tvenue=NULL\n");

			if(message[i]->new_chat_member)
				printf("\tnew_chat_member=(type User)\n");
			else
				printf("\tnew_chat_member=NULL\n");

			if(message[i]->left_chat_member)
				printf("\tleft_chat_member=(type User)\n");
			else
				printf("\tleft_chat_member=NULL\n");

			if(message[i]->new_chat_title)
				printf("\tnew_chat_title=%s\n", message[i]->new_chat_title);
			else
				printf("\tnew_chat_title=NULL\n");

			if(message[i]->new_chat_photo)
				printf("\tnew_chat_photo=(type PhotoSize)\n");
			else
				printf("\tnew_chat_photo=NULL\n");

			if(message[i]->delete_chat_photo)
				printf("\tdelete_chat_photo=%d\n", message[i]->delete_chat_photo);
			else
				printf("\tdelete_chat_photo=NULL\n");

			if(message[i]->group_chat_created)
				printf("\tgroup_chat_created=%d\n", message[i]->group_chat_created);
			else
				printf("\tgroup_chat_created=NULL\n");

			if(message[i]->supergroup_chat_created)
				printf("\tsupergroup_chat_created=%d\n", message[i]->supergroup_chat_created);
			else
				printf("\tsupergroup_chat_created=NULL\n");

			if(message[i]->channel_chat_created)
				printf("\tchannel_chat_created=%d\n", message[i]->channel_chat_created);
			else
				printf("\tchannel_chat_created=NULL\n");

			if(message[i]->migrate_to_chat_id)
				printf("\tmigrate_to_chat_id=%ld\n", message[i]->migrate_to_chat_id);
			else
				printf("\tmigrate_to_chat_id=NULL\n");

			if(message[i]->migrate_from_chat_id)
				printf("\tmigrate_from_chat_id=%ld\n");
			else
				printf("\tmigrate_from_chat_id=NULL\n");

			if(message[i]->pinned_message)
				printf("\tpinned_message=(type Message)\n");
			else
				printf("\tpinned_message=NULL\n");

			if(message[i]->invoice)
				printf("\tinvoice=(type Invoice)\n");
			else
				printf("\tinvoice=NULL\n");

			if(message[i]->successful_payment)
				printf("\tsuccessful_payment=(type SuccessfulPayment)\n");
			else
				printf("\tsuccessful_payment=NULL\n");
		}

		i++;
	}
}

void read_update(Update * update){

	/*update*/
	printf("\n\ntype Update\n");
	printf("\tupdate_id=%ld\n", update->update_id);
	if(update->message){
		printf("\tmessage=(type Message)\n");
	}
	else{
		printf("\tmessage=NULL\n");
	}

	fflush(stdout);
	if(update->edited_message){
		printf("\tedited_message=(type Message)\n");
	}
	else{
		printf("\tedited_message=NULL\n");
	}


	if(update->channel_post){
		printf("\tchannel_post=(type Message)\n");
	}
	else{
		printf("\tchannel_post=NULL\n");
	}


	if(update->edited_channel_post){
		printf("\tedited_channel_post=(type Message)\n");
	}
	else{
		printf("\tedited_channel_post=NULL\n");
	}


	if(update->inline_query){
		printf("\tinline_query=(type InlineQuery)\n");
	}
	else{
		printf("\tinline_query=NULL\n");
	}


	if(update->chosen_inline_result){
		printf("\tchosen_inline_result=(type ChosenInlineResult)\n");
	}
	else{
		printf("\tchosen_inline_result=NULL\n");
	}


	if(update->callback_query)
		printf("\tcallback_query=(type CallbackQuery)\n");
	else{
		printf("\tcallback_query=NULL\n");
	}

	if(update->shipping_query){
		printf("\tcallback_query=(without type shipping_query)\n");
	}
	else{
		printf("\tcallback_query=NULL\n");
	}

	read_message(update);
}


int main(int argc, char **argv){
	telebot_init();

	if(argc != 2)
		fprintf(stderr, "update <token>");

    Bot *bot = telebot(argv[1]);

	Update * update = get_updates(bot, NULL);

	printf("%ld\n-\n", update->update_id);

	read_update(update);

	return 0;
}