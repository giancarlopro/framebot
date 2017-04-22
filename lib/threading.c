#include <telebot.h>

void handle_updates(Bot *bot, char *extra) {
	Update *updates = get_updates(bot, extra);
	
	int n_updates = update_len(updates);

	Update *handle;
	int tid;

	int i;
	Update *non_processed_updates = NULL, *up;
	for (i = 0; i < n_updates; i++) {
		up = update_get(updates, i);
		if (log_update(up)) {
			if (!non_processed_updates) {
				non_processed_updates = up;
				continue;
			}
			update_add(non_processed_updates, up);
		}
	}
	n_updates = update_len(non_processed_updates);
	if (n_updates == 0)
		return;

	printf("\nFound %d updates!", n_updates);

	#pragma omp parallel private(handle, tid) shared(non_processed_updates) num_threads(n_updates)
	{
		tid = omp_get_thread_num();
		handle = update_get(non_processed_updates, tid);

		send_message(bot, handle->message->chat->id, handle->message->text, format("parse_mode=Markdown"));
		printf("\nSended a message to: %s", handle->message->from->username);
	}

	update_free(updates);
	update_free(non_processed_updates);
	update_free(up);
}