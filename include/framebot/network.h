/**
 * MIT License
 * Copyright (c) 2016 - 2018 Giancarlo Rocha & Ródgger Bruno
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <framebot/framebot.h>

#define API_URL "https://api.telegram.org/bot"
#define API_URL_LEN 28

#define API_URL_FILE "https://api.telegram.org/file/bot"
#define API_URL_FILE_LEN 35

#define SENDPHOTO 100
#define SENDAUDIO 200
#define SENDDOCUMENT 300
#define SENDVIDEO 400
#define SENDVOICE 500
#define SENDVIDEONOTE 600
#define SETCHATPHOTO 700

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
	char * parse_mode;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} sphoto;

typedef struct _saudio{
	int type;
	char * chat_id;
	char * filename;
	char * caption;
	char * parse_mode;
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
	char * parse_mode;
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
	char * parse_mode;
	char * supports_streaming;
	char * disable_notification;
	char * reply_to_message_id;
	char * reply_markup;
} svideo;

typedef struct _svoice{
	int type;
	char * chat_id;
	char * filename;
	char * caption;
	char * parse_mode;
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

typedef struct _chatphoto{
	int type;
	char * chat_id;
	char * filename;
} scphoto;

typedef union _ifile{
	int type;
	scphoto chatphoto;
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
MemStore *call_method(const char *token, const char *method);
int call_method_download(const char * token, char * namefile, File * ofile);
MemStore * call_method_upload(const char * token, IFile ifile);

#endif
