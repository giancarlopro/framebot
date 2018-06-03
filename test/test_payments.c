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


bool accpte_payment(){

	Framebot *framebot = NULL;

	char *tax = "{\"id\":\"product_12\", \"title\":\"Product_12\", \"prices\":[{\"label\":\"tax\", \"amount\":515}]}";
	char *notax = "";

	while(1){
		if(framebot == NULL)
			framebot = get_updates(_bot, framebot, 0, 0, 0, NULL);
		else
			framebot = get_updates(_bot, framebot, framebot->update_id + 1, 0, 0, NULL);

		while(framebot->up_shipping_query != NULL){
			Update *s_q = framebot->up_shipping_query;

			if(strcmp(s_q->shipping_query->invoice_payload, "product_12") == 0 ||
				strcmp(s_q->shipping_query->invoice_payload, "product_11") == 0){
				answerShippingQuery(_bot, s_q->shipping_query->id, 1, "[{\"id\":\"product_12\", \"title\":\"Product_12\", \"prices\":[{\"label\":\"tax\", \"amount\":515}]}]", NULL);
			}
			else{
				answerShippingQuery(_bot, s_q->shipping_query->id, 1, NULL, NULL);
			}


			Error *error = get_error();
			if(error)
				printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);

			framebot->up_shipping_query = framebot->up_shipping_query->next;
			update_free(s_q);

		}
		while(framebot->up_pre_checkout_query != NULL){
			Update *p_c_q = framebot->up_pre_checkout_query;
			
			answerPreCheckoutQuery(_bot, p_c_q->pre_checkout_query->id, 1, NULL);

			Error *error = get_error();
			if(error)
				printf(RED"false\ncode:%ld | description:%s\n"COLOR_RESET, error->error_code, error->description);

			framebot->up_pre_checkout_query = framebot->up_pre_checkout_query->next;
			update_free(p_c_q);
		}
	}
}


void test_invoice(){
	Message *result = NULL;

	printf(WHITE "Send Invoice ... \n");
	set_provider_token(provider_token);


	printf(WHITE "Send invoice .............................." COLOR_RESET);
	fflush(stdout);
	result = send_invoice(_bot, chat_id, "product 1", "(description)", "product_1", "forward_product1", prices,
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



	printf(WHITE "Send invoice(currency) ............." COLOR_RESET);
	fflush(stdout);
	set_currency(CODE_EUR);
	result = send_invoice(_bot, chat_id, "product 2", "currency (description)", "product 2", "forward_product2", prices,
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


	printf(WHITE "Send invoice(photo) ..............." COLOR_RESET);
	fflush(stdout);
	/* add_img_invoice(char *photo_url, uint64_t photo_size, uint32_t photo_width, uint32_t photo_heigth) */
	add_img_invoice("https://telegram.org/img/t_logo.png", 0, 50, 50);
	result = send_invoice(_bot, chat_id, "product 3", "photo (description)", "product_3", "forward_product3", prices,
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
	result = send_invoice(_bot, chat_id, "product 4", "need_name (description)", "product_4", "forward_product4", prices,
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
	result = send_invoice(_bot, chat_id, "product 5", "need_phone_number (description)", "product_5", "forward_product5", prices,
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
	result = send_invoice(_bot, chat_id, "product 6", "need_email (description)", "product_6", "forward_product6", prices,
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


	printf(WHITE "Send invoice(option : need_shipping_address) .." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 1, 0, 0, 0);
	result = send_invoice(_bot, chat_id, "product 7", "need_shipping_address (description)", "product_7", "forward_product7", prices,
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


	printf(WHITE "Send invoice(option : send_phone_number_to_provider) ..." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 0, 1, 0, 0);
	result = send_invoice(_bot, chat_id, "product 8", "send_phone_number_to_provider (description)", "product_8", "forward_product8", prices,
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


	printf(WHITE "Send invoice(option : send_email_to_provider) ...." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 0, 0, 1, 0);
	result = send_invoice(_bot, chat_id, "product 9", "send_email_to_provider (description)", "product_9", "forward_product9", prices,
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
	result = send_invoice(_bot, chat_id, "product 10", "is_flexible (description)", "product_10", "forward_product10", prices,
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
	result = send_invoice(_bot, chat_id, "product 11", "all (description)", "product_11", "forward_product11", prices,
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


	printf(WHITE "Send invoice(option : tax) ........." COLOR_RESET);
	fflush(stdout);
	option_payment(0, 0, 0, 0, 0, 0, 1);
	result = send_invoice(_bot, chat_id, "product 12", "delivery (description)", "product_12", "forward_product12", prices,
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
			accpte_payment();
			break;
		}

		printf("\nuser found: %s\n", update->up_message->message->from->username);
		message = message->next;

	}

	if(valid_username == 0)
		printf(RED "\nUsername %s not found" COLOR_RESET, argv[3]);


	return 0;
}
