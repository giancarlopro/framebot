#ifndef LOG_H
#define LOG_H

#define F_LOG 			"/log_api" /* file bot log */	
#define D_LOG_CHAT 		"/chat/" /* dir chat log */
#define PREFIX_LOG 		"/log_" /* prefix log chat */


#define START_API 		"----- Start API -----"
#define ETOKEN 			"Failed to authenticate token \n\tmethod(telegram): getME\n\tToken: "
#define PRINT_ETOKEN	"Failed to authenticate"


struct _log {
	char *folder;
	char *chat;
	char *prefix;
};

int log_update(Update *update);
void log_init();
int file_exists(char *name);
void update_log(char *log);
void update_log_chat(char *str, size_t *id_chat);
int create_log_bot (char *path_bot_log);
int create_dir_chat_log(char *log_dir);
int create_dir_log(char *log_dir);
#endif
