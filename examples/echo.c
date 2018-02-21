#include <stdio.h>
#include <framebot/framebot.h>

int main (int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./echo BOT_TOKEN\n");
        exit(-1);
    }
    framebot_init();

    Bot *echo = framebot(argv[1]);

    long int last_offset = 0;

    Update *last_updates = get_updates(echo, last_offset, 100, 0, NULL);
    Update *temp = last_updates;

    while (temp) {
        if (temp->message) {
            if (send_message_chat (echo, temp->message->from->id, temp->message->text, "HTML", 0, 0, temp->message->message_id, "")) {
                printf("Sended: \"%s\" to %s!\n", temp->message->text, temp->message->from->username);
            }
        }

        last_offset = temp->update_id + 1;
        temp = temp->next;
    }

    get_updates(echo, last_offset, 100, 0, NULL); // Reset update list
    return 0;
}