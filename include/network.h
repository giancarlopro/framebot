#ifndef NETWORK_H
#define NETWORK_H

#include <telebot.h>

#define API_URL "https://api.telegram.org/bot"
#define API_URL_LEN 28

#define API_URL_FILE "https://api.telegram.org/file/bot"
#define API_URL_FILE_LEN 33

#define SENDPHOTO 100
#define SENDAUDIO 200
#define SENDDOCUMENT 300
#define SENDVIDEO 400
#define SENDVOICE 500
#define SENDVIDEONOTE 600

typedef struct _mem_store {
    char *content;
    size_t size;
} MemStore;

typedef MemStore* MemStorePtr;

typedef struct _sphoto{
	int type;
	char * chat_id;
	char * filename;
	char * caption;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} sphoto;

typedef struct _saudio{
	int type;
	char * chat_id;
	char * filename;
	char * caption;
	char * duration;
	char * performer;
	char * title;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} saudio;

typedef struct _sdocument{
	int type;
	char * chat_id;
	char * filename;
	char * caption;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} sdocument;

typedef struct _svideo{
	int type;
	char * chat_id;
	char * filename;
	char * duration;
	char * width;
	char * height;
	char * caption;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} svideo;

typedef struct _svoice{
	int type;
	char * chat_id;
	char * filename;
	char * caption;
	char * duration;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} svoice;

typedef struct _svnote{
	int type;
	char * chat_id;
	char * filename;
	char * duration;
	char * length;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} svNote;

typedef union _ifile{
	int type;
	sphoto photo;
	saudio audio;
	sdocument document;
	svideo video;
	svoice voice;
	svNote videonote;
} IFile;


void network_init();
MemStore * mem_store();
void mem_store_free(MemStore * memStore);
size_t mem_write_callback(void *content, size_t size, size_t nmemb, void *userp);
MemStore *call_method(const char *token, char *method);
char * call_method_download(const char * token, char * dir, File * ofile);
MemStore * call_method_input_file(const char * token, IFile ifile);

#endif
