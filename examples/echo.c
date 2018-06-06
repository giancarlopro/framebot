#include <stdio.h>
#include <framebot/framebot.h>

int main (int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./echo BOT_TOKEN\n");
        exit(-1);
    }

    int64_t last_offset = 0;
    Bot *echo;
    Framebot *frame_update;
    Update *message, *temp;

    echo = framebot_init(argv[1]);


    frame_update = get_updates(echo, NULL, last_offset, 100, 0, NULL);
    message = frame_update->up_message;
    temp = message;

    while (temp) {
        if (temp->message) {
            if (send_message_chat (echo, temp->message->from->id, temp->message->text, 0, temp->message->message_id, NULL)) {
                printf("Sended: \"%s\" to %s!\n", temp->message->text, temp->message->from->username);
            }
        }

        last_offset = temp->update_id + 1;
        temp = temp->next;
    }

    get_updates(echo, frame_update, last_offset, 100, 0, NULL); // Reset update list
    framebot_free(frame_update);
    return 0;
}
