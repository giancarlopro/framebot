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

#ifdef _WIN32
    #include <Windows.h>
    #define custom_sleep(mili) Sleep(mili)
#else
    #include <unistd.h>
    #define custom_sleep(mili) sleep(mili)
#endif

Bot * _bot = NULL;
char *username = NULL;
long int chat_id = 0;
long int user_id = 0;
int valid_username = 0;
char *text = NULL;
Message *result = NULL;


int _func(){
	
	printf("message ........ ");
	result  = send_message_chat (_bot, chat_id, text, NULL,
            0, 0, 0, NULL);
	if(result){
		printf("ok\n");
	}
	else{
		printf("false\n");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}

	#ifdef _WIN32
		custom_sleep(5000);
	#else
		custom_sleep(5);
	#endif

	printf("get_chat ........ ");
	Chat *a = get_chat_chat(_bot, chat_id);
	if(a){
		printf("ok\n");
		chat_free(a);
	}
	else{
		printf("false\n");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}
	


	printf("user_profile_photos .......... ");
	UserProfilePhotos * b =
			get_user_profile_photos_chat(_bot, user_id, 1, 0);
	if(b){
		printf("ok\n");
		user_profile_photos_free(b);
	}
	else{
		printf("false\n");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}


	printf("forward_message_from_chat ............. ");
	Message * c = forward_message_chat (_bot, chat_id, chat_id, 
            0, result->message_id);
	if(c){
		printf("ok\n");
		message_free(c);
	}
	else{
		printf("false\n");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}

	#ifdef _WIN32
		custom_sleep(5000);
	#else
		custom_sleep(5);
	#endif

	printf("send_location_chat ............ ");
	Message * d = send_location_chat (_bot, chat_id, -25.064949, -130.101544,
            400, 1, 0, NULL);
	if(d){
		printf("ok\n");
		message_free(d);
	}
	else{
		printf("false\n");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}


	printf("send_contact ...... ");
	Message * e = send_contact_chat(_bot, chat_id, "65 9999-9992", "Framebot",
            "API", 0, 0, NULL);
	if(e){
		printf("ok\n");
		message_free(e);
	}
	else{
		printf("false\n");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}

	#ifdef _WIN32
		custom_sleep(5000);
	#else
		custom_sleep(5);
	#endif

	printf("send sendchataction ............ ");
	if(send_chat_action_chat(_bot, chat_id, "typing")){
		printf("ok\n");
	}
	else{
		printf("false");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
	}


	printf("send edit_message_text ............. ");
	Message *f = edit_message_text_chat(_bot, chat_id, result->message_id,
    NULL, "Mudou - MUDOU", NULL, 0, NULL);
    if(f){
    	printf("ok\n");
    	message_free(f);
    }
    else{
    	printf("false");
		Error *e1 = get_error();
		if(e1)
			printf("false\ncode:%ld | description:%s\n", e1->error_code, e1->description);
		exit(-1);
    }


	return 0;
}

int main(int argc, char *argv[]){
	framebot_init();

	if(argc < 4){
		fprintf(stderr, "sendvideonote <token> <username> <text>");
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

	while(update->up_message){
		if(strcmp(update->up_message->message->from->username, argv[2]) == 0){
			valid_username = 1;
			chat_id = update->up_message->message->chat->id;
			user_id = update->up_message->message->from->id;
			_func();
			break;
		}
		update->up_message = update->up_message->next;
	}

	bot_free(_bot);
	framebot_free(update);

	if(valid_username == 0)
		printf("Username not found");

	return 0;
}
