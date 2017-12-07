#include <telebot.h>

static const char *directory_log;
static bool exist = false;

char *get_file(long int user_log, enum Etype type, char *file_name) {
	if(exist == true){
		char *path;
		size_t path_len;

		path_len = strlen(directory_log) + 40 + strlen(file_name);
		path = malloc(path_len);

		if(type == t_image)
			snprintf(path, path_len, "%s/%ld/image/%s", directory_log, user_log, file_name);
		else if(type == t_document)
			snprintf(path, path_len, "%s/%ld/document/%s", directory_log, user_log, file_name);
		else if(type == t_voice)
			snprintf(path, path_len, "%s/%ld/voice/%s", directory_log, user_log, file_name);
		else if(type == t_audio)
			snprintf(path, path_len, "%s/%ld/audio/%s", directory_log, user_log, file_name);
		else if(type == t_video)
			snprintf(path, path_len, "%s/%ld/video/%s", directory_log, user_log, file_name);
		else if(type == t_contact)
			snprintf(path, path_len, "%s/%ld/contact/%s", directory_log, user_log, file_name);


		if(access_log(path) == 1)
			return path;
	}

	return NULL;
}

int access_log(const char *path){
	if(access(path, F_OK) == -1) {
		if(errno == ENOENT){
			return 0; /* does not exist */
		}

		return -1; /* error */
	}

	return 1; /* exist */
}

char *insert_file(long int user, enum Etype type, char *name_file) {
	char *path_user;
	char *full_path;
	size_t path_user_len, full_path_len;
	int returned;

	if(exist == true){
		path_user_len = strlen(directory_log) + 25;
		path_user = malloc(path_user_len);
		snprintf(path_user, path_user_len , "%s/%ld", directory_log, user);

		if((returned == access_log(path_user)) == -1)
			goto log_error;

		if(returned == 0){
			if(mkdir(path_user, S_IRWXU|S_IRWXU|S_IXGRP|S_IROTH|S_IXOTH) == -1)
				goto log_error;
		}


		full_path_len = strlen(path_user) + 25 + strlen(name_file);
		full_path = malloc(full_path_len);

		if(type == t_image)
			snprintf(full_path, full_path_len, "%s/image/", path_user);
		else if(type == t_document)
			snprintf(full_path, full_path_len, "%s/document/", path_user);
		else if(type == t_voice)
			snprintf(full_path, full_path_len, "%s/voice/", path_user);
		else if(type == t_audio)
			snprintf(full_path, full_path_len, "%s/audio/", path_user);
		else if(type == t_video)
			snprintf(full_path, full_path_len, "%s/video/", path_user);
		else if(type == t_contact)
			snprintf(full_path, full_path_len, "%s/contact/", path_user);


		if((returned == access_log(full_path)) == -1)
			goto log_error_user;

		if(returned == 0){
			if(mkdir(full_path, S_IRWXU|S_IRWXU|S_IXGRP|S_IROTH|S_IXOTH) == -1)
				goto log_error_user;
		}

		strncat(full_path, name_file, strlen(name_file));

		free(path_user);

		return full_path;

	}

	return NULL;

log_error:
	free(path_user);
	return name_file;

log_error_user:
	free(path_user);
	free(full_path);
	return name_file;
}

bool text_log(long int user_log, char *extra, long int date, const char *text) {
	char *path, fdate[25];
	size_t path_len;
	int returned;
	struct tm *loctime;
	FILE *fd_log;

	if(exist == true){
		path_len = strlen(directory_log) + 30;
		path = malloc(path_len);

		snprintf(path, path_len, "%s/%ld", directory_log, user_log);

		if((returned = access_log(path)) == -1){
			goto error_path;
		}
		if(returned == 0){
			if(mkdir(path, S_IRWXU | S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH) == -1)
				goto error_path;
		}

		strcat(path, "/log");

		if((returned = access_log(path))== -1){
			goto error_path;
		}

		fd_log = fopen(path, "a");
		if(!fd_log)
			goto error_path;

		loctime = localtime(&date);
		strftime(fdate, 25, "%F %T", loctime);

		fprintf(fd_log, "\n %s\nid: %ld\extra: %s\nmessage: %s\n", fdate, user_log, extra, text);


		free(path);

		return true;
	}


error_path:
	free(path);
	return false;
}

void log_init(){
	directory_log = get_log();
	printf("\nlog = %s", directory_log);

	if(mkdir(directory_log, S_IRWXU | S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH) == -1){
		if(errno == EEXIST){
			exist = true;
		}
		else {
			printf("\nerror in the path to the log\nverify config\npress enter to continue without log");
			getchar();
		}
	}
}
