#ifndef CONFIG__
#define CONFIG__


void read_config();
static size_t to_process_line_config(char * line_config);
static size_t to_command_config(char *line_config);
static void error_read(size_t position_caracter, size_t current_line);
static size_t to_response_command_config(char *line, char *value, size_t active_quotes, size_t i);
static void insert_command(char *command);
static void insert_response_command(char *response_command);
static struct _config *last_config();
static void list_command();
char *search_command(char *command);

#endif