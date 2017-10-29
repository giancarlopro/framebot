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
Bot *_bot;

int _file(char * file_id){
	char str[15];
	strcpy(str, "CMakeFiles/");

	get_file(_bot, str, file_id);
}

void _message(Update * update){
	if(update){
		if(update->message){
			if(update->message->document)
				_file(update->message->document->file_id);
		}
	}

}


/* only document */
int main(int argc, char **argv){
	size_t update_length, i;
	telebot_init();

	if(argc != 2)
		fprintf(stderr, "update <token>");

    _bot = telebot(argv[1]);

	Update * update = get_updates(_bot, NULL);

	update_length = update_len(update);

	while(update){
		_message(update);
		update = update->next;
	}

	return 0;
}