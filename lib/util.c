#include <util.h>

// format = (char *param_alias), (bool param), (char *param_alias), (bool param), ...
char *vsboolean_param_parser (char *base, int psize, ...) {
    va_list params;
    va_start(params, psize);
    
    int i;

    char *alias, *tmp, *base_tmp = base;
    bool param;

    for (i = 0; i < psize; i++) {
        alias = va_arg(params, char*);
        param = va_arg(params, bool);

        if (param) {
            tmp = format("&%s=True", alias);
        } else {
            tmp = format("&%s=False", alias);
        }

        base_tmp = realloc_string(base_tmp, tmp);
        free(tmp);
    }

    return base_tmp;
}
