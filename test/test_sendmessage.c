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
	printf(WHITE "Send sendmessage ... \n");

	printf(WHITE "Send chat_id ........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, "parameter chat_id", NULL, 0, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send username ........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, "parameter username", NULL, 0, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send parse_mode HTML ........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, "parameter parse_mode = MODE_HTML%0Abold = <b>bold</b>, <strong>bold</strong>%0Aitalic = <i>italic</i>, <em>italic</em>%0Agithub = <a href=\"https://github.com/giancarlopro/framebot\">inline URL</a>", MODE_HTML, 0, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send parse_mode MARKDOWN ........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, "parameter parse_mode = MODE_MARKDOWN%0Abold = *bold text*%0Aitalic = _italic text_%0A[inline URL](https://github.com/giancarlopro/framebot)%0A```block_languagepre-formatted fixed-width code block```", MODE_MARKDOWN, 0, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send disable_web_page_preview (not thumb)........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, "parameter disable_web_page_preview https://github.com/giancarlopro/framebot", NULL, 1, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send disable_notification ........." COLOR_RESET);
	fflush(stdout);
	result = send_message_chat(_bot, chat_id, "parameter disable_notification", NULL, 1, 1, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send reply_to_message_id ........." COLOR_RESET);
	fflush(stdout);
	Message * forward = send_message_chat(_bot, chat_id, "parameter reply_to_message_id", NULL, 1, 0, result->message_id, NULL);
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
		fprintf(stderr, "sendphoto <token> <username>");
		exit(-1);
	}

	_bot = framebot(argv[1]);
	if(!_bot){
		fprintf(stderr, "ERROR authentic");
		exit(-1);
	}

	username = argv[2];

	Framebot *update = NULL;
	Update *message = NULL;

	update = get_updates(_bot, update, 0, 0, 0, "message");
	message = update->up_message;

	while(message){
		if(strcmp(update->up_message->message->from->username, argv[2]) == 0){
			valid_username = 1;
			chat_id = update->up_message->message->from->id;
			_message();
			break;
		}

		printf("\nuser found: %s\n", update->up_message->message->from->username);
		message = message->next;

	}

	if(valid_username == 0)
		printf("\nUsername %s not found", argv[2]);


	return 0;
}
