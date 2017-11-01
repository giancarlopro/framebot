#include "../include/telebot.h"

Bot * _bot;

int main(int argc, char *argv[]){
	telebot_init();

	if(argc != 2)
		fprintf(stderr, "update <token>");

    _bot = telebot(argv[1]);

	UserProfilePhotos * oupp = get_user_profile_photos(_bot, 100856717, 0, 0);

	if(oupp){
		printf("true");
	}

	return 0;
}