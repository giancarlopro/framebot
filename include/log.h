
#ifndef LOG_H
#define LOG_H

#define F_LOG 			"/log_api" /* file bot log */	
#define D_LOG_CHAT 		"/chat/" /* dir chat log */
#define PREFIX_LOG 		"/log_" /* prefix log chat */


#define START_API 		"----- Start API -----"
#define GETME_LOG 		"token Authentication: ok id_bot=%ld username=%s"
#define GETME_ELOG		"Failed to authenticate"

enum Etype {t_image, t_document, t_voice, t_video, t_contact} type;

char *get_file(long int user_log, enum Etype type);
bool insert_file(long int user_log, enum Etype type, char *current);
bool cp_file(long int user_log, enum Etype type, char *current);
bool text_log(long int user_log, char *extra, long int date, char *text);
void log_init();


#endif
