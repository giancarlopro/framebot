#include <framebot/framebot.h>

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

Bot * _bot = NULL;
char *username = NULL;
long int chat_id = 0;
int valid_username = 0;
char *text = NULL;
Message *result = NULL;

int _message(){
	printf(WHITE "Send voice ... \n");

	/* Bot *bot, long int chat_id, char *text, char *parse_mode,
            bool disable_web_page_preview, bool disable_notification, long int reply_to_message_id,
            char * reply_markup */

    printf(WHITE "Send chat_id ........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, text, NULL, 0, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	return 0;
}

int main(int argc, char *argv[]){
	framebot_init();

	if(argc < 4){
		fprintf(stderr, "sendphoto <token> <username> <message>");
		exit(-1);
	}

	_bot = framebot(argv[1]);
	if(!_bot){
		fprintf(stderr, "ERROR authentic");
		exit(-1);
	}

	text = argv[3];
	username = argv[2];

	Framebot *update = NULL;

	update = get_updates(_bot, update, 0, 0, 0, "message");

	while(update->message){
		if(strcmp(update->message->message->from->username, argv[2]) == 0){
			valid_username = 1;
			chat_id = update->message->message->from->id;
			_message();
			break;
		}
	}

	if(valid_username == 0)
		printf("Username not found");


	return 0;
}
