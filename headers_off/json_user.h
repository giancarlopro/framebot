#ifndef JSON_USER
#define JSON_USER

typedef struct _command {
    char *result_command;
} command;

struct _all_commands {
    char *thecommand;
    command value;
    struct _all_commands *next;
} all_commands;


#endif