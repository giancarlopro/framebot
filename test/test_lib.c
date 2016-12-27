#include <telebot.h>

int main(){

	User * usr = telebot_json_user("{\"id\":312367410,\"first_name\":\"ChallengeBot\",\"last_name\":0,\"username\":\"ChallengeCRobot\"}");

	printf("Id: %d\nName: %s %s\nUsername: %s\n",usr->id,usr->first_name,usr->last_name,usr->username );

	return 0;
}
