#include <framebot/framebot.h>

#define BOLD         "\033[1m"
#define COLOR_RESET  "\033[0m"
#define BLACK  "\033[22;30m"
#define RED    "\033[22;31m"
#define GREEN  "\033[22;32m"
#define BROWN  "\033[22;33m"
#define BLUE   "\033[22;34m"
#define MAGENTA "\033[22;35m"
#define CYAN   "\033[22;36m"
#define GRAY   "\033[22;37m"
#define DARK_GRAY "\033[01;30m"
#define LIGHT_RED "\033[01;31m"
#define LIGHT_GREEN "\033[01;32m"
#define YELLOW "\033[01;33m"
#define LIGHT_BLUE "\033[01;34m"
#define LIGHT_MAGENTA "\033[01;35m"
#define LIGHT_CYAN "\033[01;36m"
#define WHITE "\033[01;37m"


int main(int argc, char **argv){
	Update *message, *edited_message, *channel_post, *edited_channel_post,
		*inline_query, *chosen_inline_result, *callback_query, *shipping_query, *pre_checkout_query;
	Error *error = NULL;

	if(argc < 2)
		fprintf(stderr, "update <token>");


    Bot *bot = framebot_init(argv[1]);
    if(!bot){
		error = get_error();
		if(error)
			printf(RED"false\ncode:%d | description:%s\n"COLOR_RESET, error->error_code, error->description);

    	fprintf(stderr, "Error Authentic");
    	exit(-1);
    }


    printf(WHITE"\nget_updates(bot, NULL, 0, 0, 0, NULL)");
	Framebot *fbot = get_updates(bot, NULL, 0, 0, 0, NULL);
	error = get_error();
	if(error)
		printf(RED"false\ncode:%d | description:%s\n" COLOR_RESET, error->error_code, error->description);
	printf(BLUE " . . . OK\n" COLOR_RESET);

	/* message */
	message = fbot->up_message;
	printf(BLUE "\n\tmessage : %d" COLOR_RESET, (int)update_len(message));

	/* edited_message */
	edited_message = fbot->up_edited_message;
	printf(BLUE "\n\tedited_message : %d" COLOR_RESET, (int)update_len(edited_message));

	/* channel_post */
	channel_post = fbot->up_channel_post;
	printf(BLUE "\n\tchannel_post : %d" COLOR_RESET, (int)update_len(channel_post));

	/* edited_channel_post */
	edited_channel_post = fbot->up_edited_channel_post;
	printf(BLUE "\n\tedited_channel_post : %d" COLOR_RESET, (int)update_len(edited_channel_post));

	/* inline_query */
	inline_query = fbot->up_inline_query;
	printf(BLUE "\n\tinline_query : %d" COLOR_RESET, (int)update_len(inline_query));

	/* chosen_inline_result */
	chosen_inline_result = fbot->up_chosen_inline_result;
	printf(BLUE "\n\tchosen_inline_result : %d" COLOR_RESET, (int)update_len(chosen_inline_result));

	/* callback_query */
	callback_query = fbot->up_callback_query;
	printf(BLUE "\n\tcallback_query : %d" COLOR_RESET, (int)update_len(callback_query));

	/* shipping_query */
	shipping_query = fbot->up_shipping_query;
	printf(BLUE "\n\tshipping_query : %d" COLOR_RESET, (int)update_len(shipping_query));

	/* pre_checkout_query */
	pre_checkout_query = fbot->up_pre_checkout_query;
	printf(BLUE "\n\tpre_checkout_query : %d" COLOR_RESET, (int)update_len(pre_checkout_query));

	printf(BLUE "\nfree request" COLOR_RESET);
	framebot_free(fbot);

	fbot = NULL;

    printf(WHITE"\nget_updates(bot, fbot, 0, 0, 10, NULL)");
	fbot = get_updates(bot, fbot, 0, 0, 10, NULL);
	error = get_error();
	if(error)
		printf(RED"false\ncode:%d | description:%s\n" COLOR_RESET, error->error_code, error->description);
	printf(BLUE " . . . OK\n" COLOR_RESET);

	/* message */
	message = fbot->up_message;
	printf(BLUE "\n\tmessage : %d" COLOR_RESET, (int)update_len(message));

	/* edited_message */
	edited_message = fbot->up_edited_message;
	printf(BLUE "\n\tedited_message : %d" COLOR_RESET, (int)update_len(edited_message));

	/* channel_post */
	channel_post = fbot->up_channel_post;
	printf(BLUE "\n\tchannel_post : %d" COLOR_RESET, (int)update_len(channel_post));

	/* edited_channel_post */
	edited_channel_post = fbot->up_edited_channel_post;
	printf(BLUE "\n\tedited_channel_post : %d" COLOR_RESET, (int)update_len(edited_channel_post));

	/* inline_query */
	inline_query = fbot->up_inline_query;
	printf(BLUE "\n\tinline_query : %d" COLOR_RESET, (int)update_len(inline_query));

	/* chosen_inline_result */
	chosen_inline_result = fbot->up_chosen_inline_result;
	printf(BLUE "\n\tchosen_inline_result : %d" COLOR_RESET, (int)update_len(chosen_inline_result));

	/* callback_query */
	callback_query = fbot->up_callback_query;
	printf(BLUE "\n\tcallback_query : %d" COLOR_RESET, (int)update_len(callback_query));

	/* shipping_query */
	shipping_query = fbot->up_shipping_query;
	printf(BLUE "\n\tshipping_query : %d" COLOR_RESET, (int)update_len(shipping_query));

	/* pre_checkout_query */
	pre_checkout_query = fbot->up_pre_checkout_query;
	printf(BLUE "\n\tpre_checkout_query : %d" COLOR_RESET, (int)update_len(pre_checkout_query));

	printf(BLUE "\nfree request" COLOR_RESET);
	framebot_free(fbot);
	fbot = NULL;


    printf(WHITE"\nget_updates(bot, fbot, 0, 0, 0, [\"message\", \"edited_channel_post\", \"callback_query\"])");
	fbot = get_updates(bot, fbot, 0, 0, 0, "[\"message\", \"edited_channel_post\", \"callback_query\"]");
	error = get_error();
	if(error)
		printf(RED"false\ncode:%d | description:%s\n" COLOR_RESET, error->error_code, error->description);
	printf(BLUE " . . . OK\n" COLOR_RESET);

	/* message */
	message = fbot->up_message;
	printf(BLUE "\n\tmessage : %d" COLOR_RESET, (int)update_len(message));

	/* edited_message */
	edited_message = fbot->up_edited_message;
	printf(BLUE "\n\tedited_message : %d" COLOR_RESET, (int)update_len(edited_message));

	/* channel_post */
	channel_post = fbot->up_channel_post;
	printf(BLUE "\n\tchannel_post : %d" COLOR_RESET, (int)update_len(channel_post));

	/* edited_channel_post */
	edited_channel_post = fbot->up_edited_channel_post;
	printf(BLUE "\n\tedited_channel_post : %d" COLOR_RESET, (int)update_len(edited_channel_post));

	/* inline_query */
	inline_query = fbot->up_inline_query;
	printf(BLUE "\n\tinline_query : %d" COLOR_RESET, (int)update_len(inline_query));

	/* chosen_inline_result */
	chosen_inline_result = fbot->up_chosen_inline_result;
	printf(BLUE "\n\tchosen_inline_result : %d" COLOR_RESET, (int)update_len(chosen_inline_result));

	/* callback_query */
	callback_query = fbot->up_callback_query;
	printf(BLUE "\n\tcallback_query : %d" COLOR_RESET, (int)update_len(callback_query));

	/* shipping_query */
	shipping_query = fbot->up_shipping_query;
	printf(BLUE "\n\tshipping_query : %d" COLOR_RESET, (int)update_len(shipping_query));

	/* pre_checkout_query */
	pre_checkout_query = fbot->up_pre_checkout_query;
	printf(BLUE "\n\tpre_checkout_query : %d" COLOR_RESET, (int)update_len(pre_checkout_query));


	printf(BLUE "\nfree request" COLOR_RESET);
	framebot_free(fbot);
	fbot = NULL;

    printf(WHITE"\nget_updates(bot, fbot, 12345, 0, 0, NULL)");
	fbot = get_updates(bot, fbot, 12345, 0, 0, NULL);
	error = get_error();
	if(error)
		printf(RED"false\ncode:%d | description:%s\n" COLOR_RESET, error->error_code, error->description);
	printf(BLUE " . . . OK\n" COLOR_RESET);

	/* message */
	message = fbot->up_message;
	printf(BLUE "\n\tmessage : %d" COLOR_RESET, (int)update_len(message));

	/* edited_message */
	edited_message = fbot->up_edited_message;
	printf(BLUE "\n\tedited_message : %d" COLOR_RESET, (int)update_len(edited_message));

	/* channel_post */
	channel_post = fbot->up_channel_post;
	printf(BLUE "\n\tchannel_post : %d" COLOR_RESET, (int)update_len(channel_post));

	/* edited_channel_post */
	edited_channel_post = fbot->up_edited_channel_post;
	printf(BLUE "\n\tedited_channel_post : %d" COLOR_RESET, (int)update_len(edited_channel_post));

	/* inline_query */
	inline_query = fbot->up_inline_query;
	printf(BLUE "\n\tinline_query : %d" COLOR_RESET, (int)update_len(inline_query));

	/* chosen_inline_result */
	chosen_inline_result = fbot->up_chosen_inline_result;
	printf(BLUE "\n\tchosen_inline_result : %d" COLOR_RESET, (int)update_len(chosen_inline_result));

	/* callback_query */
	callback_query = fbot->up_callback_query;
	printf(BLUE "\n\tcallback_query : %d" COLOR_RESET, (int)update_len(callback_query));

	/* shipping_query */
	shipping_query = fbot->up_shipping_query;
	printf(BLUE "\n\tshipping_query : %d" COLOR_RESET, (int)update_len(shipping_query));

	/* pre_checkout_query */
	pre_checkout_query = fbot->up_pre_checkout_query;
	printf(BLUE "\n\tpre_checkout_query : %d" COLOR_RESET, (int)update_len(pre_checkout_query));

	printf(BLUE "\nfree request" COLOR_RESET);
	framebot_free(fbot);
	fbot = NULL;

    printf(WHITE"\nget_updates(bot, fbot, 0, 3, 0, NULL)");
	fbot = get_updates(bot, fbot, 0, 3, 0, NULL);
	error = get_error();
	if(error)
		printf(RED"false\ncode:%d | description:%s\n" COLOR_RESET, error->error_code, error->description);
	printf(BLUE " . . . OK\n" COLOR_RESET);

	/* message */
	message = fbot->up_message;
	printf(BLUE "\n\tmessage : %d" COLOR_RESET, (int)update_len(message));

	/* edited_message */
	edited_message = fbot->up_edited_message;
	printf(BLUE "\n\tedited_message : %d" COLOR_RESET, (int)update_len(edited_message));

	/* channel_post */
	channel_post = fbot->up_channel_post;
	printf(BLUE "\n\tchannel_post : %d" COLOR_RESET, (int)update_len(channel_post));

	/* edited_channel_post */
	edited_channel_post = fbot->up_edited_channel_post;
	printf(BLUE "\n\tedited_channel_post : %d" COLOR_RESET, (int)update_len(edited_channel_post));

	/* inline_query */
	inline_query = fbot->up_inline_query;
	printf(BLUE "\n\tinline_query : %d" COLOR_RESET, (int)update_len(inline_query));

	/* chosen_inline_result */
	chosen_inline_result = fbot->up_chosen_inline_result;
	printf(BLUE "\n\tchosen_inline_result : %d" COLOR_RESET, (int)update_len(chosen_inline_result));

	/* callback_query */
	callback_query = fbot->up_callback_query;
	printf(BLUE "\n\tcallback_query : %d" COLOR_RESET, (int)update_len(callback_query));

	/* shipping_query */
	shipping_query = fbot->up_shipping_query;
	printf(BLUE "\n\tshipping_query : %d" COLOR_RESET, (int)update_len(shipping_query));

	/* pre_checkout_query */
	pre_checkout_query = fbot->up_pre_checkout_query;
	printf(BLUE "\n\tpre_checkout_query : %d\n" COLOR_RESET, (int)update_len(pre_checkout_query));
	fbot = NULL;


	return 0;
}
