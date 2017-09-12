#include <telebot.h>

struct _config {
	char *command;
	char *response;
	struct _config *next;
};

static struct _config *config = NULL;
static int continued = 0;

void read_config(){
	FILE *fconfig;
	char *line_config;
	size_t error = 0, current_line = 1;

	fconfig = fopen("config", "r");
	if(fconfig){
		line_config = (char *) malloc(500);
		while(!feof(fconfig)){
			fgets(line_config, 500, fconfig);
			if(line_config){
				error = to_process_line_config(line_config);
				if(error > 0)
					error_read(error, current_line);
			}
			current_line++;
		}
		list_command();
	}
	else {
		printf("21ioeqwododfmsofnsmdf");
	}
}

static size_t to_process_line_config(char * line_config) {
	char *line, *command;
	size_t i = 0, active_commands = 1, error = 0;

	line = line_config;

		if(line[i] == '/' || continued == 1) {
			if(active_commands == 1){
				error = to_command_config(line);
			}
		}
		else if(line[i] == '#'){

		}
		else if(line[i] == '&'){
			if(strcmp(line_config, "&commands") == 1){
				active_commands = 0;
			}

			else if(strcmp(line_config, "&info") == 2){
				active_commands = 1;
			}
		}

	return error;
}

static size_t to_command_config(char *line_config) {

	size_t line_config_len = strlen(line_config), /* tamanho da linha */
		   active_bar_command = 0,  /* ativado significa que o primeiro caracter existi */
		   active_command = 0,		/* ativado ele obtém o comando sem contra-barra */
		   error_caracter = 0,  	/* identifica a posição do erro na linha */
		   active_quotes = 0, 		/* aspas simples 1-2 aspas duplas 3-4 */
		   active_equals = 0, 		/* Ativado significa que chegou no iqual entre comando e valor */
		   active_value = 0, 		/* ativado obtém o valorde resposta do comando */
		   off_caracter = 0,		/* ativado significa que o próximocaracter não será interpretado */
		   i = 0,					/* posição do caractere que está sendo processado */
		   number_line = 0;			/* numero de linha do resultado de um comando através do \ */

	char *command,             /* comando para string inteira */
		 *value,               /* valor para string inteira */
		 *c,                   /* usado para andar em cada caractere do var command */
		 *line = line_config;  /* usado para andar em cada caracter do line_config  */

	command = (char *) malloc(line_config_len);
	value = (char *) malloc(line_config_len);

	memset(value, '\0', line_config_len);
	memset(command, '\0', line_config_len);

	c = command;

	if(continued == 0) {
		while(*line && *line != '\n') {
			i++;
			/* primeiro caracter. Começo do nome do comando */
			if(*line == '/' && i == 1) {
				++active_bar_command;
				++active_command;
				*c = *line;
				c++;
			}
			/* bloco para obter comando */
			else if(active_bar_command == 1 && active_equals == 0 && active_command == 1) {
				/* fim do campo comando na linha*/
				if (*line == '=' && i > 2) {
					++active_equals;
					--active_command;
					*c = '\0';
				}
				/* caracter 0 - 9 */
				else if((int) *line >= 48 && (int) *line <= 57) {
					*c = *line;
				}
				/* A - Z */
				else if((int) *line >= 65 && (int) *line <= 90) {
					*c = *line;
				}
				/* a - z */
				else if((int) *line >= 97 && (int) *line <= 122) {
					*c = *line;
				}
				/* outro caracter que não seja alfanumérico */
				else {
					error_caracter = i;
					break;
				}

				/* próximo índice no array */
				c++;
			}
			else if(active_equals == 1 && active_quotes == 0) {
				if(*line == '\''){
					*c = '\0';
					active_quotes = 1;
					active_value++;
				}

				else if(*line == '\"'){
					*c = '\0';
					active_quotes = 3;
					active_value++;
				}

				else if(*line == ' '){
					error_caracter = i;
					break;
				}
				line++;
				break;

			}

			line++;
		}
	}

	if(error_caracter > 0)
		return error_caracter;

	if(continued == 0)
		insert_command(command);

	error_caracter = to_response_command_config(line, value, active_quotes, i);


	return error_caracter;
}

static size_t to_response_command_config(char *line, char *value, size_t active_quotes, size_t i) {
	size_t off_caracter = 0, error_caracter = 0;
	char *v = value;

	while(*line && *line != '\n'){
		/* contra barra serve para as aspas não ser
		 * interpretada. Contra barra só serve para aspas ou colocar uma barra */
		if(*line == '\\'){
			/* Se off_caracter é 0 e quando chegar a 1 
			 * o caracter não será interpretado normalmente*/
			if(off_caracter == 0){
				++off_caracter;
				line++;
				continue;
			}
			else{
				--off_caracter;
				if((int)off_caracter == -1){
					error_caracter = i;
					break;
				}
				*v = *line;
			}
		}
		else if(*line == '\''){
			if(off_caracter == 1){
				--off_caracter;
				*v = *line;
			}
			else if(off_caracter == 0){
				if(active_quotes == 1){
					*v = '\0';
					break;
				}
				else{
					error_caracter = i;
					break;
				}
			}
		}
		else if(*line == '\"'){
			if(off_caracter == 1){
				--off_caracter;
				*v = *line;
			}
			else if(off_caracter == 0){
				if(active_quotes == 3){
					*v = '\0';
					break;
				}
				else if(continued == 1){
					*v = '\0';
					break;
				}
				else{
					error_caracter = i;
					break;
				}
			}
		}
		else if(off_caracter == 1){
			error_caracter = i;
			break;
		}
		else{
			*v = *line;
		}
		
		if(off_caracter == 0)
			v++;   
		i++;
		line++;
	}

	if(off_caracter > 0 ){
		continued = 1;
	}
	else{
		continued = 0;
	}

	insert_response_command(value);

	return error_caracter;
}


static void error_read(size_t position_caracter, size_t current_line){
	printf("Error reading \nline=%lu\nposition=%lu\n", current_line, position_caracter);
}

static struct _config *last_config(){
	struct _config *pconfig = config;

	if(!pconfig){
		return NULL;
	}

	while(pconfig->next){
		pconfig = pconfig->next;
	}

	return pconfig;
}

static void insert_command(char *command){
	struct _config *config_command = last_config();

	if(!config_command){
		config = malloc(sizeof(struct _config));
		config_command = config;
		config->next = NULL;
	}
	else{
		config_command->next = malloc(sizeof(struct _config));
		config_command = config_command->next;
		config_command->next = NULL;
	}

	config_command->command = malloc(strlen(command) + 1);

	strcpy(config_command->command, command);
}

static void insert_response_command(char *response_command){
	static int count = 0;

	struct _config *config_response = last_config();

	if(count == 0){
		config_response->response = malloc(strlen(response_command) + 1);
		memset(config_response->response, '\0', strlen(response_command));
		strcpy(config_response->response, response_command);
		count++;
	}
	else{
		size_t config_response_len = strlen(config_response->response) + strlen(response_command);
		config_response->response = realloc(config_response->response, config_response_len + 1);
		strcat(config_response->response, response_command);
	}

	if(continued == 0){
		count = 0;
	}
}

static void list_command(){
	int id = 0;
	struct _config *list_config = config;

	while(list_config){
		printf("\tcomando = %s\n", list_config->command);
		printf("\tresposta = %s\n", list_config->response);
		printf("\n");
		fflush(stdout);
		id++;
		list_config = list_config->next;
	}
	fflush(stdout);

}

char *search_command(char *command) {

	char *response = NULL;
	struct _config *config_response = config;

	if(!command)
		return response;

	while(config_response) {
		printf("->%s\n%s\n", config_response->command, command);
		if(strcmp(config_response->command, command) == 0) {
			response = malloc(strlen(config_response->response) + 1);
			strcpy(response, config_response->response);
			break;
		}

		config_response = config_response->next;
	}

	return response;
}
