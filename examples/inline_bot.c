#define DEBUG

#include <framebot/framebot.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <Windows.h>
    #define sleep(mili) Sleep(mili)
#else
    #include <unistd.h>
    #define sleep(mili) usleep(mili)
#endif

int main (int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./inline BOT_TOKEN\n");
        exit(-1);
    }
    framebot_init();

    char *result = alloc_string("[{\"type\":\"sticker\",\"id\":\"1\",\"sticker_file_id\":\"CAADAQADCQADEcFSHDYMLlVh2wPKAg\"}]");
    Bot *inbot = framebot(argv[1]);
    if(!inbot)
    	return -1;

    Framebot *updates = NULL;
    Update *queries = NULL;

    updates = get_updates(inbot, NULL, 0, 100, 0, NULL);
    if (updates->inline_query) {
        queries = updates->inline_query;

        answer_inline_query(inbot, queries->inline_query->id, result, 0, 0, NULL, NULL, NULL);
    }
    
    bot_free(inbot);
    free(result);
    framebot_free(updates);

    return 0;
}