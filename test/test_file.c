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
char *file_id = NULL;
char *namefile = NULL;


int _file(){
	printf(WHITE "Send file ... "COLOR_RESET);

	if(file_download(_bot, get_file(_bot, file_id), namefile)){
			printf(BLUE "OK\n" COLOR_RESET);
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

	if(argc < 2){
		fprintf(stderr, "file <token> or file <token> <dir>");
		exit(-1);
	}

	_bot = framebot_init(argv[1]);
	if(!_bot){
		fprintf(stderr, "ERROR authentic");
		exit(-1);
	}

	username = argv[2];

	Framebot *_update = NULL;

	_update = get_updates(_bot, _update, 0, 0, 100, NULL);
	Update *update = _update->up_message;
	File *ofile = NULL;
	int id = 0;
	char *dir;

	if(argv[2] == NULL)
		dir = NULL;
	else
		dir = argv[3];

	while(update){
		if(update->message->audio){
			ofile = get_file(_bot, update->message->audio->file_id);
			printf("%d.\nuser:%s\ndate:%ld\nfile_path:%s\n\n", id++, update->message->from->username, update->message->date, ofile->file_path);
			file_download(_bot, ofile, namefile);
		}
		else if(update->message->document){
			ofile = get_file(_bot, update->message->document->file_id);
			printf("%d.\nuser:%s\ndate:%ld\nfile_path:%s\n\n", id++, update->message->from->username, update->message->date, ofile->file_path);
			file_download(_bot, ofile, namefile);
		}
		else if(update->message->photo){
			ofile = get_file(_bot, update->message->photo->file_id);
			printf("%d.\nuser:%s\ndate:%ld\nfile_path:%s\n\n", id++, update->message->from->username, update->message->date, ofile->file_path);
			file_download(_bot, ofile, namefile);
		}
		else if(update->message->video){
			ofile = get_file(_bot, update->message->video->file_id);
			printf("%d.\nuser:%s\ndate:%ld\nfile_path:%s\n\n", id++, update->message->from->username, update->message->date, ofile->file_path);
			file_download(_bot, ofile, namefile);
		}
		else if(update->message->voice){
			ofile = get_file(_bot, update->message->voice->file_id);
			printf("%d.\nuser:%s\ndate:%ld\nfile_path:%s\n\n", id++, update->message->from->username, update->message->date, ofile->file_path);
			file_download(_bot, ofile, namefile);
		}
		else if(update->message->video_note){
			ofile = get_file(_bot, update->message->voice->file_id);
			printf("%d.\nuser:%s\ndate:%ld\nfile_path:%s\n\n", update->message->from->username, update->message->date, ofile->file_path);
			file_download(_bot, ofile, namefile);
		}


		update = update->next;
	}

	if(valid_username == 0)
		printf("Username not found\n");

	return 0;
}
