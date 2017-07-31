#include <telebot.h>

void telebot_init() {
	printf("%s", CSCREEN);

	network_init();
	log_init();
}

/* Authentic bot token */
Bot * telebot(char *token) {
	User *bot_user = get_me(token);
	if (bot_user) {
		Bot *obot = bot(token, bot_user);
		return obot;
	}
	//fprintf(stdout, "ERROR: Couldn't allocate memory.");
	return NULL;
}

/* A simple method for testing your bot's auth token */
User *get_me(char *token) {

	char *message_log;
	MemStore *data = call_method(token, "getMe");

	if (data) {
		User *ouser = get_me_parse(data->content);
		mem_store_free(data);
		if (ouser){
			get_me_log(ouser);
			return ouser;
		}
	}

	get_me_log(NULL);

	return NULL;
}

/* Pull new message 'bot'*/
Update *get_updates(Bot *bot, char *extra) {
	MemStore *json;
	if(extra){
		char *base = format("getUpdates?%s", extra);
		json = call_method(bot->token, base);
		free(base);
	}else{
		json = call_method(bot->token,"getUpdates");
	}

	//printf("%s", json->content);
	json_t *root = load(json->content);
	if(root){
		json_t *ok, *result;
		ok = json_object_get(root,"ok");
		if(json_is_true(ok)){
			result = json_object_get(root,"result");
			size_t size = json_array_size(result);

			if(size > 0){
				Update *up = update_parse(json_array_get(result, 0));
				int i = 1;
				for (; i < size; i++) {
					update_add(up, update_parse(json_array_get(result, i)));
				}
				return up;
			}
		}
	}
	return NULL;
}

/* send message to telegram */
int send_message(Bot *bot, long int chat_id, char *text, char *extra) {
	if (!chat_id || !text)
		return -1;

	MemStore *json;

	char *method_base = NULL;
	if (extra) {
		method_base = format("sendMessage?chat_id=%ld&text=%s&%s", chat_id, text, extra);

		free(extra);
	} else {
		method_base = format("sendMessage?chat_id=%ld&text=%s", chat_id, text);
	}
	
	//printf("\n\n%s\n\n", method_base);

	json = call_method(bot->token, method_base);

	free(method_base);

	if (!json)
		return -1;
	json_t *root = load(json->content);

	if (root) {
		json_t *ok;
		ok = json_object_get(root, "ok");
		if (json_is_true(ok))
			return 1;
	}
	return 0;
}

void telebot_polling(Bot *bot) {

	receives	= malloc(sizeof(Receives));
	gives 		= malloc(sizeof(Gives));

	receives->update 	= NULL;
	receives->error 	= NULL;
	gives->send 		= NULL;

	pthread_t *thread;

	pthread_create(thread, NULL, handle_network, (void *) bot);
	handle_data(bot);
}

void handle_data(Bot *bot){
	
	gives->bot = bot;
	Update 	*update;
	Message *message;
	Send 	*send;

	while(1){
		if(receives->update){
			update = receives->update;
			send = (Send *) malloc (sizeof (Send));
			send->message_id = update->message->message_id;
			send->id_chat = update->message->chat->id;
			send->text = alloc_string(update->message->text);
			send->extra = NULL;
			send->next= NULL;

			gives->send = send;
		}
		else{
			sleep(2);
		}
	}
}
