#include <telebot.h>

static struct _log log;

int log_update(Update *update) {

	char *fname = format("updates/%ld", update->update_id);
	if (!file_exists(fname)) {
		FILE *fp = fopen(fname, "w+");
		//fprintf(fp, "%ld", update->update_id);
		free(fname);
		fclose(fp);

		return 1;
	}
	return 0;
}

int file_exists(char *name) {
	FILE *fp = fopen(name, "r");
	if (fp) {
		fclose(fp);
		return 1;
	}
	return 0;
}

/* verify directories e file logs */
void log_init() {
	char *pwd, *log_dir, *log_dir_chat, *bot_log;
	size_t size_path_log, size_pwd;
	FILE *f_log;

	printf("%s", CSCREEN);
	printf("LOG:\n");

	pwd = getcwd(NULL, 0);
	size_pwd = strlen(pwd);

	/* block log_dir */
	size_path_log = size_pwd + strlen("/log/") + 1;
	log_dir = malloc(size_path_log);
	strncpy(log_dir, pwd, size_pwd + 1);
	strcat(log_dir, "/log/");

	/* block log_chat */
	size_path_log = size_pwd + strlen("/chat/") + 1;
	log_dir_chat = malloc(size_path_log);
	strncpy(log_dir_chat, pwd, size_pwd + 1);
	strcat(log_dir_chat, "/chat/");

	/* bot_log */
	size_path_log = size_pwd + strlen("log") + 1;
	bot_log = malloc(size_path_log);
	strncpy(bot_log, pwd, size_pwd + 1);
	strcat(bot_log, "log");

	if(create_log_bot(bot_log) == -1)
		exit(-1);

	if(create_dir_chat_log(log_dir_chat) == -1)
		exit(-1);

	if(create_dir_log(log_dir) == -1)
		exit(-1);


	log.folder 	= alloc_string(log_dir);
	log.chat 	= alloc_string(log_dir_chat);
	log.prefix  = alloc_string("log_");

	update_log(START_API);

	free	(pwd);
	free	(log_dir);
	free	(log_dir_chat);
	free	(bot_log);
}

void update_log(char *str){

	char str_date[19], *path_log;
	size_t size_str_to_file;
	time_t seconds;
	struct tm *date;
	FILE *f_log;

	/* get date */
	seconds = time(NULL);
	date = gmtime(&seconds);
	date->tm_year += 1900;
	date->tm_mon += 1;
	date->tm_hour -= 4;
	strftime(str_date, sizeof str_date, "%d/%b %T ", date);

	/* path log */
	path_log = malloc(strlen(log.folder) + strlen(log.prefix) + 1);
	strcpy(path_log, log.folder);
	strcat(path_log, log.prefix);

	f_log = fopen(path_log, "a");
	if(f_log){
		fprintf(f_log, "%s %s\n", str_date, str);

		fclose(f_log);
		free(path_log);
	}
	
}

void update_log_chat(char *str, size_t *id_chat){

	char str_date[19], *path_log, *str_id_char;
	size_t size_str_to_file;
	time_t seconds;
	struct tm *date;
	FILE *f_log;

	/* get date */
	seconds = time(NULL);
	date = gmtime(&seconds);
	date->tm_year += 1900;
	date->tm_mon += 1;
	date->tm_hour -= 4;
	strftime(str_date, sizeof str_date, "%d/%b %T ", date);

	/* path log */
	size_str_to_file = strlen(log.folder) + strlen(log.prefix) + 15 + 1;
	path_log = malloc(size_str_to_file);
	snprintf(path_log, size_str_to_file, "%s%s%ld\n", log.folder, log.prefix, id_chat);

	f_log = fopen(path_log, "a");
	if(f_log){
		fprintf(f_log, "%s %s\n", str_date, str);
		fclose(f_log);
		free(path_log);
	}
	else{
		
	}
}

int create_log_bot (char *path_bot_log){

	int valid_log;
	FILE *f_log;

	/* file bot log */
	valid_log = access(path_bot_log, R_OK|W_OK);
	if(valid_log){
		if(EACCES == errno){
			printf("\n\nfile = %s\n\tAccess Denied log\
\tAcesso Negado Log\n\n", path_bot_log);
			return -1;
		}

		printf("\tcreate file log: ");
		f_log = fopen(path_bot_log, "a");
		if(!f_log){
			printf("false");
			printf("\n\nfile = %s\n\tCreate Denied log\
\tCriar Negado Log\n\n", path_bot_log);
			exit(-1);
		}
		printf("OK\n");
		fclose(f_log);
	}
	else {
		printf("already exist file bot log\n");
	}
	fflush(stdout);

	return 0;
}

int create_dir_chat_log(char *log_dir_chat){

	int valid_log;
	FILE *f_log;

	/* dir log chat */
	valid_log = access(log_dir_chat, R_OK|W_OK);
	if(valid_log == -1){
		if(EACCES == errno){
			printf("\n\ndir = %s\n\tAccess Denied log\
\n\tAcesso Negado Log\n\n", log_dir_chat);
			return -1;
		}

		printf("\tcreate dir log chat: ");
		mkdir(log_dir_chat, S_IRWXU | S_IRGRP);
		printf("OK\n");
	}
	else {
		printf("alredy exist dir chat log\n");
	}
	fflush(stdout);

	return 0;
}

int create_dir_log(char *log_dir){

	int valid_log;
	FILE *f_log;

	/* dir log root */
	valid_log = access(log_dir, R_OK | W_OK);
	if(valid_log == -1){
		if(EACCES == errno){
			printf("\n\ndir = %s\n\tAccess Denied log\
\n\tAcesso Negado Log\n\n", log_dir);
			return -1;
		}

		printf("\tcreate dir log: ");
		mkdir(log_dir, S_IRWXU | S_IRGRP );
		printf("OK\n");
	}
	else {
		printf("already exist dir log\n");
	}
	fflush(stdout);

	return 0;
}
