#include <telebot.h>

void telebot_init() {
	network_init();
}

Bot * telebot(char *token) {
	User *bot_user = get_me(token);//aqui
	if (bot_user) {
		Bot *obot = bot(token, bot_user);
		return obot;
	}
	//fprintf(stdout, "ERROR: Couldn't allocate memory.");
	return NULL;
}

User *get_me(char *token) {
	MemStore *data = call_method(token, "getMe");

	if (data) {
		User *ouser = get_me_parse(data->content);
		mem_store_free(data);
		if (ouser)
			return ouser;
	}
	return NULL;
}
/* Offset: 10 digits
 * Limit:  3 digits
 * timeout: 10 digits
 */
Update *get_updates(Bot *bot, Param *p) {
	MemStore *json;
	if(p){
		json = call_method(bot->token,param_parse(p));
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

int send_message(Bot *bot, char *chat_id, char *text, Param *extra) {
	if (!chat_id || !text)
		return -1;

	MemStore *json;
	if (extra) {
		param_add(extra, "chat_id", chat_id);
		param_add(extra, "text", text);
		json = call_method_wp(bot->token, "sendMessage", param_parse(extra));
	} else {
		Param *tmp = param();
		param_add(tmp, "chat_id", chat_id);
		param_add(tmp, "text", text);
		json = call_method_wp(bot->token, "sendMessage", param_parse(tmp));
	}
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