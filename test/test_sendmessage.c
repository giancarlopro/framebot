#include <framebot/framebot.h>

int main(int argc, char *argv[]){
	Message * message = NULL;
	Bot * _bot = NULL;

	framebot_init();

	if(argc < 3)
		fprintf(stderr, "sendmessage <token> <id user>");

    _bot = framebot(argv[1]);

    if(_bot)
		message = send_message(_bot, argv[2], "sendMessage = ok", NULL, 0, 0, 0, NULL);


	if(message){
		printf("enviado");
		message_free(message);
		bot_free(_bot);
	}
	else{
		Error * error = show_error();
		if(error)
			printf("error_code=%ld error_descriptio=n%s\n", error->error_code, error->description);
	}

	return 0;
}
