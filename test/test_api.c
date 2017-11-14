#include <telebot.h>

typedef struct _function {
	char * function;
	char * parameter;
	int count_parameter;
} Functions;

Functions * function;

void set_function();

int main(int argc, char * argv[]){
	set_function();


	return 0;
}

void set_function(){
	Functions f[] = {
		{"telebot", "token:str", 1},

		{"get_updates", "bot:obj extra:str", 2},

		{"send_message_channel", "bot:obj chat_id:str \
text:str parse_mode:str disable_web_page_preview:bool \
disable_notification:bool reply_to_message_id:long reply_markup:str", 8},

		{"send_message_chat", "bot:obj chat_id:long \
text:str parse_mode:str disable_web_page_preview:bool \
disable_notification:bool reply_to_message_id:long reply_markup:str", 8},

	};


}
