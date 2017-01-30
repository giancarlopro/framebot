#include <json.h>

User * json_user(char * json){
	json_t * user;
	json_error_t error;

	user = json_loads(json,0,&error);

	if(json_is_object(user)){
		json_t *id,*first_name,*last_name,*username;
		id = json_object_get(user, "id");
		first_name = json_object_get(user, "first_name");
		last_name = json_object_get(user, "last_name");
		username = json_object_get(user, "username");

		User * usr = user(json_integer_value(id),json_string_value(first_name),json_string_value(last_name),json_string_value(username));
		return usr;
	}

	json_decref(user);

	return NULL;
}
