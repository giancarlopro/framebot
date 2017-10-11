#ifndef CONFIG_H
#define CONFIG_H

struct _cfgconfig {
	char *command;
	char *response;
	struct _cfgconfig *next;
};

struct _optconfig {
	int     id;
	char    *opt;
	union _value {
		long int long_value;
		int      bool_value;
		char     str_value[100];
	} value;
	bool only_number;
	bool only_boolean;
};


/* image option */
#define INDEX_IMAGE_USE 0
#define INDEX_IMAGE_SIZE 1
#define INDEX_IMAGE_COUNT 2

/* document option */
#define INDEX_DOCUMENT_USE 3
#define INDEX_DOCUMENT_SIZE 4
#define INDEX_DOCUMENT_COUNT 5

/* audio option */
#define INDEX_AUDIO_USE 6
#define INDEX_AUDIO_SIZE 7
#define INDEX_AUDIO_COUNT 8

/* video option */
#define INDEX_VIDEO_USE 9
#define INDEX_VIDEO_SIZE 10
#define INDEX_VIDEO_COUNT 11

/* voice option */
#define INDEX_VOICE_USE 12
#define INDEX_VOICE_SIZE 13
#define INDEX_VOICE_COUNT 14

#define INDEX_CONTACT_USE 15
#define INDEX_CONTACT_COUNT 16

#define INDEX_LOG 17

#define INDEX_TOKEN 18

void read_config();
static size_t to_process_line_config(char * line_config);
static size_t to_command_config(char *line_config);
static void error_read(size_t position_caracter, size_t current_line);
static size_t to_response_command_config(char *line, char *value, bool single_quotes, bool double_quotes, size_t i);
static void insert_command(char *command);
static void insert_response_command(char *response_command);
static struct _cfgconfig *last_config();
static void list_command();
char * search_command(char *command, int *i);
static int read_option(char *line);
static void insert_option(char *option, char *option_value, bool only_number);
static void error_option(char *option, size_t current_line, bool error_value);
char *str_cpy(char *dest,  char *src, size_t char_len);

/* IMAGE */
bool image_is_activated();
bool image_size(long int size);
bool image_count( );

/* DOCUMENT */
bool document_is_activated();
bool document_size(long int size);
bool document_count();

/* AUDIO */
bool audio_is_activated();
bool audio_size(long int size);
bool audio_count();

/* VIDEO */
bool video_is_activated();
bool video_size(long int size);
bool video_count();

/* VOICE */
bool voice_is_activated();
bool voice_size(long int size);
bool voice_count();

/* CONTACT */
bool contact_is_activated();
bool contact_count();

const char *get_log();

const char *get_token();

bool format_type(const char *type);
long kbext(char *str_size);

#endif