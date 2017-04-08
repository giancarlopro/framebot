#include <telebot.h>

#define MAX_URL_SZ 2000

char *format(char *formats, ...) {

	va_list params;
	va_start(params, formats);
	
	char *buffer = (char *)malloc(MAX_URL_SZ);
	
	int i = vsprintf(buffer, formats, params);

	va_end(params);

	return buffer;
}