#include <telebot.h>

Bot * _bot;


void upp(UserProfilePhotos * oupp){
	int i, x, q;
	PhotoSize * l;
	printf("%ld", oupp->total_count);
	for(i = 0; i < oupp->total_count; i++){
		l = oupp->photos[i];
		for(x = 0; x < photo_size_len(oupp->photos[i]); x++){
			if(l->file_id)
				printf("photos[%d][%d]{\n\tfile_id=%s\n\twidth=%d\n\theight=%d\n\tfile_size=%ld\n}\n", i, x, l->file_id, l->width, l->height, l->file_size);
			l = l->next;
		}
	}

	user_profile_photos_free(oupp);
	if(!oupp)
		printf("OK!");

}


int main(int argc, char *argv[]){
	telebot_init();

	if(argc != 2)
		fprintf(stderr, "update <token>");

    _bot = telebot(argv[1]);

	UserProfilePhotos * oupp = get_user_profile_photos(_bot, "100856717", 0, 0, 0);

	if(oupp){
		printf("true");
		upp(oupp);
	}

	return 0;
}