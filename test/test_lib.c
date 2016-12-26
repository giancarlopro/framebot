#include <telebot.h>

int main(){

	User * usr = telebot_json_user("{\"id\":312367410,\"first_name\":\"ChallengeBot\",\"username\":\"ChallengeCRobot\"}");

	printf("Id: %d\nName: %s\nUsername: %s\n",usr->id,usr->first_name,usr->username );

	return 0;
}
