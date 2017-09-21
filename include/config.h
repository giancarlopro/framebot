#ifndef CONFIG__
#define CONFIG__

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
	bool value_boolean;
};

struct _botconfig {
	int id;
	char *opt;
};

/* image option */
#define SIZE_IMAGE 1
#define COUNT_IMAGE 2
#define USE_IMAGE 0

/* document option */
#define SIZE_DOCUMENT 1
#define COUNT_DOCUMENT 2
#define USE_DOCUMENT 3

/* gifs option */
#define SIZE_GIFS 1
#define COUNT_GIFS 2
#define USE_GIFS 3

/* audio option */
#define SIZE_AUDIO 1
#define COUNT_AUDIO 2
#define USE_AUDIO 3

/* sticker option */
#define COUNT_STICKER 1
#define USE_STICKER 2

void read_config();
static size_t to_process_line_config(char * line_config);
static size_t to_command_config(char *line_config);
static void error_read(size_t position_caracter, size_t current_line);
static size_t to_response_command_config(char *line, char *value, size_t active_quotes, size_t i);
static void insert_command(char *command);
static void insert_response_command(char *response_command);
static struct _cfgconfig *last_config();
static void list_command();
char * search_command(char *command, int *i);
static int read_option(char *line);
static void insert_option(char *option, char *option_value, bool only_number);
static void error_option(char *option, size_t current_line, bool error_value);
char *str_cpy(char *dest,  char *src, size_t char_len);
bool is_active_image(int image_index);
bool size_image(int index_image, size_t size);
int count_image(int index_image);
int document_option(int document_option);
int gifs_option(int gifs_option);
int audio_option(int audio_option);
int sticker_option(int sticker_option);
long kbext(char *str_size);

#endif