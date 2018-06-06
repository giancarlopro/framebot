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
int64_t chat_id = 0;
int valid_username = 0;
char *filename = NULL;
Message *result = NULL;

int _video(){

	printf(WHITE "Send video ... \n");

	/* Bot * bot, char * chat_id, char * filename, int64_t duration,
    int64_t length, bool disable_notification, int64_t reply_to_message_id,
    char * reply_markup */

	printf(WHITE "Send chat_id ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 0, 0, 0, NULL, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send username ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 0, 0, 0, NULL, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send duration ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 0, 0, NULL, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send width ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 10, 0, NULL, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send height ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 10, 10, NULL, 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send caption ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 10, 1, "caption", 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send parse_mode ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 10, 1, "<b>caption</b>", 0, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send supports_streaming ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 10, 1, "caption", 1, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send disable_notification ........." COLOR_RESET);
	fflush(stdout);
	result = send_video_chat(_bot, chat_id, filename, 10, 10, 1, "caption", 1, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	printf(WHITE "Send reply_to_message_id ........." COLOR_RESET);
	fflush(stdout);
	Message *forward = send_video_chat(_bot, chat_id, filename, 10, 10, 1, "caption", 1, result->message_id, NULL);
	if(forward){
		printf(BLUE "OK\n" COLOR_RESET);
		message_free(forward);
		message_free(result);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}

	return 0;
}

int main(int argc, char *argv[]){

	if(argc < 4){
		fprintf(stderr, "sendvideonote <token> <username> <path audio>");
		exit(-1);
	}

	_bot = framebot_init(argv[1]);
	if(!_bot){
		fprintf(stderr, "ERROR authentic");
		exit(-1);
	}

	filename = argv[3];
	username = argv[2];

	Framebot *update = NULL;

	update = get_updates(_bot, update, 0, 0, 0, "message");

	while(update->up_message){
		if(strcmp(update->up_message->message->from->username, argv[2]) == 0){
			valid_username = 1;
			chat_id = update->up_message->message->from->id;
			_video();
			break;
		}
	}

	if(valid_username == 0)
		printf("Username not found");

	return 0;
}
