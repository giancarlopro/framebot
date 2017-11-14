#include <telebot.h>

typedef struct _function {
	char * function;
	char * parameter;
	char * _return;
	int count_parameter;
} Functions;

Functions * function;

void set_function();
void verify_function();

int main(int argc, char * argv[]){
	set_function();


	return 0;
}

void set_function(){
	Functions f[] = {
		{"telebot", "token:str", "bot:obj", 1},

		{"get_updates", "bot:obj extra:str", "update:obj", 2},

		{"send_message_channel", "bot:obj chat_id:long text:str parse_mode:str\
disable_web_page_preview:bool disable_notification:bool reply_to_message_id:long\
reply_markup:str", "message:obj", 8},

		{"set_chat_title_chat", "bot:obj chat_id:long title:str", ":int", 3},
		{"get_chat_chat", "bot:obj, chat_id:str", "chat:obj", 2},
		{"get_chat_member_chat", "bot:obj chat_id:long user_id:long", "", 3}
	};
}

void verify_function(){
	Functions * ffunction;
	int i;

	for(i = 0; function; i++){
		
	}
}