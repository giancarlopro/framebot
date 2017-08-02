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
				size_t i = 1;
				for (; i < size; i++) {
					update_add(up, update_parse(json_array_get(result, i)));
				}

				json_decref(root);

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
		if (json_is_true(ok)){
			json_decref(root);

			return 1;
		}
	}
	return 0;
}

void telebot_polling(Bot *bot) {

	receives	= malloc(sizeof(Receives));
	gives 		= malloc(sizeof(Gives));

	receives->update 	= NULL;
	receives->error 	= NULL;
	gives->send 		= NULL;

	pthread_t thread;
	pthread_mutex_init(&cthread.lock_receives, NULL);
	pthread_mutex_init(&cthread.lock_gives, NULL);

	pthread_create(&thread, NULL, handle_network, (void *) bot);
	handle_data(bot);
}

void handle_data(Bot *bot){
	
	gives->bot = bot;
	Update 	*update, *next;
	Message *message;
	Send 	*send = NULL, *last_send;
	size_t size_updates, i;

	while(1){

		pthread_mutex_lock(&cthread.lock_receives);
		{
			update = receives->update;
			size_updates = update_len(update);
		}
		pthread_mutex_unlock(&cthread.lock_receives);

		/* test */
		if(size_updates){
			if(!send)
				send = (Send *) malloc (sizeof (Send));
			last_send = send;

			for(i = 0; i < size_updates; i++){
				if(i){
					last_send = (Send *) malloc(sizeof(Send));
				}

				last_send->message_id = update->message->message_id;
				last_send->id_chat = update->message->chat->id;
				last_send->text = alloc_string(update->message->text);
				last_send->extra = NULL;
				last_send->next= NULL;

				printf("\n%s\n", last_send->text);

				if(i){
					send_add(send, last_send);
					last_send = last_send->next;
				}
				else{
					last_send = last_send->next;
				}

				pthread_mutex_lock(&cthread.lock_receives);
				{
					next = update->next;
					update_free(update);
					update = next;
					receives->update = update;
				}
				pthread_mutex_unlock(&cthread.lock_receives);
			}


			pthread_mutex_lock(&cthread.lock_gives);
			{
				if(!gives->send)
					gives->send = send;
				else
					send_add(gives->send, send);
			}
			pthread_mutex_unlock(&cthread.lock_gives);
		}

		sleep(1);
	}
}
