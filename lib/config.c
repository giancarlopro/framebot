#include <telebot.h>

#define OPTION_LEN 25
#define OPTION_VALUE_LEN 100

static struct _optconfig opt[] = {

	{0,  "image_use",      0, true, true },
	{1,  "image_size",     0, true, false},
	{2,  "image_count",    0, true, false},
	
	{3,  "document_use",   0, true, true },
	{4,  "document_size",  0, true, false},
	{5,  "document_count", 0, true, false},
	
	{6,  "audio_use",      0, true, true },
	{7,  "audio_size",     0, true, false},
	{8,  "audio_count",    0, true, false},
	
	{9, "video_use",       0, true, true },
	{10, "video_size",     0, true, false},
	{11, "video_count",    0, true, false},
	
	{12, "voice_use",      0, true, true },
	{13, "voice_size",     0, true, false},
	{14, "voice_count",    0, true, false},

	{15, "contact_use",    0, true, true },
	{16, "contact_count",  0, true, false},
	
	{17, "log",            0, false, false},

	/* put token manually
	 * {17, "log", .value={.str_value={"<<<here>>>"}}, false, false} */
	{18, "token",          0, false, false},
	
	{19, NULL, 0, false, false}
};

static struct _cfgconfig *config = NULL;
static bool continued_command = false;
static size_t current_line = 0;


void read_config(){
	FILE *fconfig;
	char *line_config;
	size_t error = 0;
	int i = 0;

	fconfig = fopen("config", "r");

	if(fconfig){

		line_config = (char *) malloc(500);

		while(!feof(fconfig)){
			current_line++;
			fgets(line_config, 500, fconfig);

			if(line_config && *line_config != '\n' && *line_config != 0){
				error = to_process_line_config(line_config);
				if(error > 0)
					error_read(error, current_line);

			} 	
			memset(line_config, '\0', 500);

		}

		list_command();
	}
	else {
		printf(CLRED "Not Found config");
	}
}




static size_t to_process_line_config(char * line_config) {
	char *line, *command;
	size_t i = 0, error = 0;
	bool active_commands = true;

	line = line_config;

	if(line[i] == '#'){

	}

	else if(line[i] == '/' || continued_command == true) {
		if(active_commands == true){
			error = to_command_config(line);
		}
	}

	else if(line[i] == '&'){
		if(strcmp(line_config, "&commands") == 0){
			active_commands = 0;
		}
	}

	else {
		read_option(line_config);
	}

	return error;
}





static size_t to_command_config (char *line_config) {



	size_t line_config_len = strlen (line_config), /* tamanho da linha */
		   i 				  = 0,	/* posição do caractere que está sendo processado */
		   index              = 0;

	bool   active_command     = false,
		   active_value       = false,
   		   active_bar_command = false,
   		   active_equals      = false,
   		   single_quotes      = false,
   		   double_quotes      = false,
   		   off_caracter       = false,
   		   error_caracter     = false,
   		   space              = false;


	char  *command,             /* comando para string inteira */
		  *value,               /* valor para string inteira */
		  *line = line_config;  /* usado para andar em cada caracter do line_config  */

	command = (char *) malloc (line_config_len);
	value = (char *) malloc (line_config_len);

	memset (value, '\0', line_config_len);
	memset (command, '\0', line_config_len);

	if (continued_command == false) {
		
		while (*line && *line != '\n') {
			i++;
			/* primeiro caracter. Começo do nome do comando */
			if (*line == '/' && i == 1) {
				active_bar_command = true;
				active_command = true;;
				command[index++] = *line;
			}
			/* bloco para obter comando */
			else if (active_bar_command == true && active_equals == false && active_command == true) {
				/* fim do campo comando na linha*/
				if (*line == '=' && i > 2) {
					active_equals = true;
					active_command = false;
					command[index++] = '\0';
				}
				else if (*line == ' ' && i > 2) {
					++space;
					active_command = false;
					command[index++] = '\0';
				}
				/* caracter 0 - 9 */
				else if ( (int) *line >= 48 && (int) *line <= 57) {
					command[index++] = *line;
				}
				/* A - Z */
				else if ( (int) *line >= 65 && (int) *line <= 90) {
					command[index++] = *line;
				}
				/* a - z */
				else if ( (int) *line >= 97 && (int) *line <= 122) {
					command[index++] = *line;
				}
				/* outro caracter que não seja alfanumérico */
				else {
					error_caracter = true;
					break;
				}
			}
			else if (active_equals == true || space == true) {
				if (*line == '\'' && active_equals == true){
					single_quotes = 1;
					active_value = true;
					line++;
					break;
				}

				else if (*line == '\"' && active_equals == 1){
					double_quotes = true;
					active_value = true;;
					line++;
					break;
				}

				else if (*line == '=') {
					if (active_equals == false) {
						active_equals = true;
					}

					else {
						error_caracter = true;
					}
				}
				else if (*line != ' ')
				{
					error_caracter = true;
				}
			}

			line++;
		}
	}

	if(error_caracter == true || (error_caracter == true && active_bar_command == true && active_equals == true && (single_quotes == true || double_quotes == true)))
		return i; /* Error caracter */

	if(continued_command == false)
		insert_command(command);

	i = to_response_command_config (line, value, single_quotes, double_quotes, i);

	if(strlen(line_config) == (i + 1))
		return 0;

	return i;
}





static size_t to_response_command_config (char *line, char *value, bool single_quotes, bool double_quotes, size_t i) {

	size_t index = 0;

	bool off_caracter = false,
	     error_caracter = false;

	while (*line && *line != '\n') {
		i++;
		/* contra barra serve para as aspas não ser
		 * interpretada. Contra barra só serve para aspas ou colocar uma barra */
		if (*line == '\\') {
			/* Se off_caracter é 0 e quando chegar a 1 
			 * o caracter não será interpretado normalmente*/
			if (off_caracter == false) {
				off_caracter = true;
				line++;
				continue;
			}
			else {
				off_caracter = false;
				value[index++] = *line;
			}
		}
		else if (*line == '\'') {
			if (off_caracter == true) {
				off_caracter = false;
				value[index++] = *line;
			}
			else if (off_caracter == false) {
				if (single_quotes == true) {
					value[index++] = '\0';
					break;
				}
				else {
					error_caracter = i;
					break;
				}
			}
		}
		else if (*line == '\"') {
			if (off_caracter == true) {
				off_caracter = false;
				value[index++] = *line;
			}
			else if (off_caracter == false) {
				if (double_quotes == true) {
					value[index++] = '\0';
					break;
				}
				else if (continued_command == true) {
					value[index++] = '\0';
					break;
				}
				else{
					error_caracter = i;
					break;
				}
			}
		}
		else if (off_caracter == 1) {
			error_caracter = i;
			break;
		}
		else {
			value[index++] = *line;
		}

		line++;
	}

	if (off_caracter == true ) {
		continued_command = true;
	}
	else {
		continued_command = false;
	}

	insert_response_command (value);

	return i;
}





static void error_read (size_t position_caracter, size_t current_line){
	printf (CRED "Error reading\n\tline=%s%lu\n%s\tposition=%s%lu\n",  CRESET, current_line, CRED, CRESET, position_caracter);

}





static struct _cfgconfig *last_config (){
	struct _cfgconfig *pconfig = config;

	if (!pconfig){
		return NULL;
	}

	while (pconfig->next){
		pconfig = pconfig->next;
	}

	return pconfig;
}





static void insert_command (char *command){
	struct _cfgconfig *config_command = last_config ();

	if (!config_command){
		config = malloc (sizeof (struct _cfgconfig));
		config_command = config;
		config->next = NULL;
	}
	else{
		config_command->next = malloc (sizeof (struct _cfgconfig));
		config_command = config_command->next;
		config_command->next = NULL;
	}

	config_command->command = malloc (strlen (command) + 1);

	strcpy(config_command->command, command);
}





static void insert_response_command (char *response_command){
	static int count = 0;

	struct _cfgconfig *config_response = last_config ();

	if (count == 0) {
		config_response->response = malloc (strlen (response_command) + 1);
		memset(config_response->response, '\0', strlen (response_command));
		strcpy(config_response->response, response_command);
		count++;
	}
	else {
		size_t config_response_len = strlen (config_response->response) + strlen (response_command);
		config_response->response = realloc (config_response->response, config_response_len + 1);
		strcat (config_response->response, response_command);
	}

	if (continued_command == false) {
		count = 0;
	}
}





static void list_command (){
	int id = 0;
	struct _cfgconfig *list_config = config;
	struct _optconfig *p_opt = opt;


	while (list_config){
		printf (CRESET "comando %s%s %s= %s%s%s\n", CCYAN, list_config->command, CRESET, CCYAN, list_config->response, CRESET);
		printf ("\n");
		list_config = list_config->next;
	}

	while(p_opt) {
		if(p_opt->opt == NULL)
			break;
		if(p_opt->only_number == true)
			if(p_opt->only_boolean == true)
				printf(CRESET "Option: %s%s %s = %s%d%s\n", CCYAN, p_opt->opt, CRESET, CCYAN, p_opt->value.bool_value, CRESET);
			else
				printf(CRESET "Option: %s%s %s = %s%d%s\n", CCYAN, p_opt->opt, CRESET, CCYAN, p_opt->value.long_value, CRESET);
		else{
			printf(CRESET "Option: %s%s %s = %s%s%s\n", CCYAN, p_opt->opt, CRESET, CCYAN, p_opt->value.str_value, CRESET);
		}

		p_opt++;
	}

	fflush(stdout);
}





char * search_command (char *line, int *i) {
	char *response = NULL, *command = NULL, *char_command = NULL, *char_line = NULL;
	size_t line_len = strlen (line);
	struct _cfgconfig *config_response = config;

	command = malloc (32);

	memset (command, '\0', 31);

	char_command = command;
	char_line = line;

	for (*i = 0; *char_line && *char_line != ' '; (*i)++){
		if (*char_line != '/' && *i == 0){
			free (command);
			*i = -1;
			return response;
		}

		*char_command = *char_line;
		char_command++;
		char_line++;
		if (*i > 30) {
			free (command);
			*i = -1;
			return response;
		}
	}

	command[strlen (command)] = '\0';

	while(config_response) {

		if(strcmp (config_response->command, command) == 0) {
			response = (char *) malloc (strlen (config_response->response) + 1);
			strcpy(response, config_response->response);
			break;
		}

		config_response = config_response->next;
	}

	free (command);

	return response;
}





int read_option (char *line) {
	char *char_line = line;
	char option[OPTION_LEN];
	char option_value[OPTION_VALUE_LEN];
	size_t i = 0, error_caracter = 0;
	bool only_number = true, option_null = false, active_option = true,
	acttive_option_value = false, active_equals = false;
	
	memset(option, '\0', sizeof(option));
	memset(option_value, '\0', sizeof(option_value));

	while (*char_line) {
		if((*char_line == ' ' || *char_line == '=') && acttive_option_value == false && active_option == false) {

			if(i != 0 && option_null == false){
				option_null = true;
				option[i] = '\0';
			}
			i = 0;

			if(active_equals == false) {
				active_equals = true;
			}
			else{
				error_caracter = i;
			}
		}
		else if(((i + 1) == OPTION_LEN) && active_equals == false) {
			option[i] = '\0';
		}
		else if((i + 1) == 100 && active_equals == true) {
			option_value[i] = '\0';
			break;
		}
		else if(active_equals == false) {
			option[i] = *char_line;
			active_option = false;
		}
		else {
			if(i == 1 && option_value[0] == '\0'){
				acttive_option_value = true;
				i = 0;
			}

			if(*char_line < 48 || *char_line > 57) {
				only_number = false;
			}

			option_value[i] = *char_line;

			if(!(*(char_line + 1)) || *(char_line + 1) == '\n'){
				option_value[++i] = '\0';
				break;
			}
		}

		char_line++;
		i++;
	}

	insert_option(option, option_value, only_number);

	return error_caracter;
}



static void insert_option(char *option, char *option_value, bool only_number) {
	char *optn = option, *opt_value = option_value, 
	ext_size[2][3] = {"KB","MB"};
	size_t i, x = 0;
	bool found = false, error_value = true;
	struct _optconfig *p_opt = opt;
	long int number;

	while(p_opt) {
		if(p_opt->opt == NULL)
			break;

		if(strcmp(p_opt->opt, optn) == 0) {
			found = true;

			if(strcmp(p_opt->opt, "log") && opt_value[0] == '0') {
				p_opt->value.str_value[0] = '\0';
				break;
			}
			if(strlen(opt_value) > 0){
				if(strstr(optn, "size") != NULL) {
					
					if(kbext(opt_value) == -1)
						found = false;
						error_value = false;
				}
				
				if(p_opt->only_number == true) {
					number = atol(opt_value);
				
					if(number > 0 && p_opt->only_boolean == true) {
						p_opt->value.bool_value = true;
					}
					else if(number == 0 && p_opt->only_boolean == true) {
						p_opt->value.bool_value = false;
					}
					else {
						p_opt->value.long_value = number;
					}
				}
				
				else {
					strcpy(p_opt->value.str_value, opt_value);
				}
				
				break;
			}
		}

		p_opt++;
	}

	if(found == false)
		error_option(option, current_line, error_value);

}



long kbext(char *str_size) {
	size_t i;
	bool kb = false, mb = false;
	char k = 'k', m = 'm';
	long int size = 0;
	char str[50];

	for(i = 0; i < strlen(str_size); i++) {

		if((str_size[i] < 48 || str_size[i] > 57) && i > 0) {
		
			if((int)k == tolower(str_size[i])){
				kb = true;
			}
			else if((int)m == tolower(str_size[i])) {
				mb = true;
			}
			else{
				break;
			}
		}
	}

	if(kb == true) {
		size = atol(str_size);
		size = size * 1024;
		sprintf(str_size, "%lu", size);
		return size;		
	}
	else if(mb == true) {
		size = atol(str_size);
		size = (size *1024) * 1024;  
		sprintf(str_size, "%lu", size);
		return size;
	}

	return -1;
}


static void error_option(char *option, size_t current_line, bool error_value) {
	bool space = true, tabulation = true, first_valid = false;
	char *char_option = option;
	size_t i = 0;

	printf(CRED "Option not found:\n\toption:%s%s\n\t%sline:%s%lu", CRESET,option, CRED, CRESET, current_line);

	while(*char_option) {
		if(i == 0 && (*char_option == ' ' || *char_option == '\t')) {
			first_valid = true;
		}
		if(*char_option != ' ' && *char_option != '\t'){
			space = false;
			tabulation = false;
		}
		char_option++;
	}

	if(error_value == false)
		printf(CRED "\nError in value of option");

	if(space == true || tabulation == true || first_valid == true)
		printf(CLRED "\nOption (can be space or tabulation)\n\n");
	else {
		printf("\n\n");
	}

	printf(CRESET "");

	exit(-1);
}


/* IMAGE */
bool image_is_activated() {

	if(opt[INDEX_IMAGE_USE].value.bool_value == true)
		return true;

	return false;
}

bool image_size(long int size) {

	if(opt[INDEX_IMAGE_SIZE].value.long_value >= size || opt[INDEX_IMAGE_SIZE].value.long_value == 0)
		return true;

	return false;
}

bool image_count( ) {
	/* still without */
	return true;
}
/* END IMAGE */




/* DOCUMENT */
bool document_is_activated() {

	if(opt[INDEX_DOCUMENT_USE].value.bool_value == true) {
		return true;
	}

	return false;
}

bool document_size(long int size) {

	if(opt[INDEX_DOCUMENT_SIZE].value.long_value >= size || opt[INDEX_DOCUMENT_SIZE].value.long_value == 0)
		return true;

	return false;
}

bool document_count() {
	/* still without */
	return true;
}
/* END DOCUMENT */



/* AUDIO */
bool audio_is_activated() {
	
	if(opt[INDEX_AUDIO_USE].value.bool_value == true)
		return true;

	return false;
}

bool audio_size(long int size) {

	if(opt[INDEX_AUDIO_SIZE].value.long_value >= size || opt[INDEX_AUDIO_SIZE].value.long_value == 0)
		return true;

	return false;
}

bool audio_count() {
	/* still without */
	return true;
}
/* END AUDIO */



/* VIDEO */
bool video_is_activated() {

	if(opt[INDEX_VIDEO_USE].value.bool_value == true)
		return true;

	return false;
}

bool video_size(long int size) {

	if(opt[INDEX_VIDEO_SIZE].value.long_value >= size || opt[INDEX_VIDEO_SIZE].value.long_value == 0)
		return true;

	return false;
}

bool video_count() {
	/* still without */
	return true;
}
/* END VIDEO */



/* VOICE */
bool voice_is_activated() {
	
	if(opt[INDEX_VOICE_USE].value.bool_value == true)
		return true;

	return false;
}

bool voice_size(long int size) {

	if(opt[INDEX_VOICE_SIZE].value.long_value >= size || opt[INDEX_VOICE_SIZE].value.long_value == 0)
		return true;

	return false;
}

bool voice_count() {
	/* still without */
	return true;
}
/* END VOICE */



/* CONTACT */
bool contact_is_activated() {

	if(opt[INDEX_CONTACT_USE].value.bool_value == true)
		return true;

	return false;
}

bool contact_count() {
	/* still without */
	return true;
}
/* END CONTACT */


const char *get_log() {
	return opt[INDEX_LOG].value.str_value;
}


const char *get_token() {
	return opt[INDEX_TOKEN].value.str_value;
}


bool format_type(const char *type) {

	if(image_is_activated() && strstr(type, "image") != NULL) {
		return true;
	}
	else if(audio_is_activated() && strstr(type, "audio") != NULL) {
		return true;
	}
	else if(video_is_activated() && strstr(type, "video") != NULL) {
		return true;
	}
	else if(document_is_activated()){

	}

	return false;
}
