#include <framebot/util.h>

int api_tg_exist(const char *filename){
    FILE *b;

    b = fopen(filename, "r");


    if(b){
        fclose(b);
        return 1;
    }

    return 0;
}
