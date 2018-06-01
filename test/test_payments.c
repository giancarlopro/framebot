#include <framebot/framebot.h>

#define COLOR_RESET  "\033[0m"
#define RED    		 "\033[22;31m"
#define BLUE   		 "\033[22;34m"
#define WHITE 		 "\033[01;37m"


Bot * _bot = NULL;
char *username = NULL;
int64_t chat_id = 0;
char *provider_token = NULL;
char *prices = "[{\"label\":\"produto 1\", \"amount\":4517}]";
int valid_username = 0;

void test_invoice(){
	Message *result = NULL;

	printf(WHITE "Send Invoice ... \n");
	set_provider_token(provider_token);


	printf(WHITE "Send invoice ........." COLOR_RESET);
	fflush(stdout);
	result = send_invoice(_bot, chat_id, "product 1", "(description)", "(param_payload)", "product_1", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(currency) ........." COLOR_RESET);
	fflush(stdout);
	set_currency(CODE_EUR);
	result = send_invoice(_bot, chat_id, "product 2", "(description)", "(param_payload)", "product_2", prices,
     NULL, 0, NULL);
	set_currency(CODE_USD); /* back DOLLAR */
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(photo) ........." COLOR_RESET);
	fflush(stdout);
	/* add_img_invoice(char *photo_url, uint64_t photo_size, uint32_t photo_width, uint32_t photo_heigth) */
	add_img_invoice("https://telegram.org/img/t_logo.png", 0, 50, 50);
	result = send_invoice(_bot, chat_id, "product 3", "(description)", "(param_payload)", "product_3", prices,
     NULL, 0, NULL);
	remove_image_invoice(); /* remove invoice image */
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : need_name) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(1, 0, 0, 0, 0, 0, 0);
	result = send_invoice(_bot, chat_id, "product 4", "(description)", "(param_payload)", "product_4", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : need_phone_number) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 1, 0, 0, 0, 0, 0);
	result = send_invoice(_bot, chat_id, "product 5", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : need_email) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 1, 0, 0, 0, 0);
	result = send_invoice(_bot, chat_id, "product 6", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : need_shipping_address) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 1, 0, 0, 0);
	result = send_invoice(_bot, chat_id, "product 7", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : send_phone_number_to_provider) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 0, 1, 0, 0);
	result = send_invoice(_bot, chat_id, "product 8", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : send_email_to_provider) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 0, 0, 1, 0);
	result = send_invoice(_bot, chat_id, "product 9", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : is_flexible) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 0, 0, 0, 1);
	result = send_invoice(_bot, chat_id, "product 10", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}


	printf(WHITE "Send invoice(option : all) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(1, 1, 1, 1, 1, 1, 1);
	result = send_invoice(_bot, chat_id, "product 11", "(description)", "(param_payload)", "para_start_parameter", prices,
     NULL, 0, NULL);
	if(result){
		printf(BLUE "OK\n" COLOR_RESET);
	}
	else{
		Error *error = get_error();
		if(error)
			printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);
		exit(-1);
	}
}

int main(int argc, char *argv[]){
	framebot_init();

	if(argc < 4){
		fprintf(stderr, "payments <token> <provider token> <username>");
		exit(-1);
	} 

	_bot = framebot(argv[1]);
	if(!_bot){
		fprintf(stderr, "ERROR authentic");
		exit(-1);
	}

	provider_token = argv[2];

	username = argv[3];

	Framebot *update = NULL;
	Update *message = NULL;

	update = get_updates(_bot, update, 0, 0, 0, "message");
	message = update->up_message;

	while(message){
		if(strcmp(update->up_message->message->from->username, argv[3]) == 0){
			valid_username = 1;
			chat_id = update->up_message->message->from->id;
			test_invoice();
			break;
		}

		printf("\nuser found: %s\n", update->up_message->message->from->username);
		message = message->next;

	}

	if(valid_username == 0)
		printf("\nUsername %s not found", argv[3]);


	return 0;
}
