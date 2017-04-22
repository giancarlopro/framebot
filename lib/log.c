#include <telebot.h>

int log_update(Update *update) {

	char *fname = format("updates/%ld", update->update_id);
	if (!file_exists(fname)) {
		FILE *fp = fopen(fname, "w+");
		//fprintf(fp, "%ld", update->update_id);
		free(fname);
		fclose(fp);

		return 1;
	}
	return 0;
}

int file_exists(char *name) {
	FILE *fp = fopen(name, "r");
	if (fp) {
		fclose(fp);
		return 1;
	}
	return 0;
}

void log_init() {
	//FILE *fp = fopen("updates/initialized", "w+");
	//fclose(fp);
	system("mkdir updates");
}