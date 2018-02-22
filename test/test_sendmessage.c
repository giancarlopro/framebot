#include <framebot/framebot.h>

Bot * _bot;

int main(int argc, char *argv[]){
	Message * message;

	framebot_init();

	if(argc < 3)
		fprintf(stderr, "sendmessage <token> <id user>");

    _bot = framebot(argv[1]);

/* Message * send_photo_chat(Bot * bot, long int chat_id, char * filename,
			  char * caption, bool disable_notification,
			  long int reply_to_message_id){
*/

    if(_bot)
		message = send_message(_bot, argv[2], "sendMessage = ok", NULL, 0, 0, 0, NULL);


	if(message){
		printf("enviado");
	}
	else{
		Error * error = show_error();
		if(error)
			printf("error_code=%ld error_descriptio=n%s\n", error->error_code, error->description);
	}

	return 0;
}
