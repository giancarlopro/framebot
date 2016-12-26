#include <telebot.h>

int main(){
	User * usr = telebot_user(12345,"Giancarlo","Rocha","gianbeatbox");
	printf("%s\n", usr->username );
	return 0;
}
