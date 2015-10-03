#include "option_parse.h"
#include <stdio.h>
#include <string.h>

// Map to OPTION_TYPE
static char *OPTION_FORMAT[] = {
    "%d", "%c", "%s", "%f", "%lf"
};

static const char OPTION_DUMP_FORMAT[] = " -%c,--%-10s%s\n";

static void _optionDump(OPTION_ENTRY *oe){
    OPTION_ENTRY *_oe = oe;
    printf("Options:\n");
    printf(OPTION_DUMP_FORMAT, 'h', "help", "Show this list");
    for(;_oe->longname != NULL; _oe++){
        printf(OPTION_DUMP_FORMAT, _oe->shortname, _oe->longname, _oe->description);
    }
}

static int _optionSet(void **buf, char *name, char *value, OPTION_TYPE t){
    char *tf = OPTION_FORMAT[t];
    int rs = 1;
    if(t == OPTION_TYPE_STRING && *buf == NULL){
        *buf = strdup(value);
        rs = (buf==NULL)?0:1;
    }else{
        rs = sscanf(value, tf, buf);
    }
    if(rs == 0){
        option_print("%s set failure\n", name);
        exit(1);
    }
    return rs;
}

static int _optionMatch(OPTION_ENTRY *oe, char *name, char *value, ARG_TYPE t){
    OPTION_ENTRY *_oe = oe;
    
    if((t == ARG_SINGLE && name[0] == 'h') || (t == ARG_DOUBLE && strcmp("help", name) == 0)){
        _optionDump(oe);
        exit(0);
    }

    for(;_oe->longname != NULL; _oe++){
        if(t == ARG_SINGLE &&_oe->shortname == name[0]){
                return _optionSet(_oe->buf, name, value, _oe->type);
        }else if(t == ARG_DOUBLE && strcmp(_oe->longname, name) == 0){
            return _optionSet(_oe->buf, name, value, _oe->type);
        }
    }

    option_print("Parameter(Option) '%s' is not avaiable\nGot detail with --help/-h", name);
    return 0;
}

static int _optionCheck(OPTION_ENTRY *oe, char *name, char *value){
    char *p = name;
    if(*p++ == '-'){
        if(*p++ == '-'){
            return _optionMatch(oe, p, value, ARG_DOUBLE);
        }else{
            return _optionMatch(oe, --p, value, ARG_SINGLE);
        }
    }

    option_print("Parameter(Option) '%s' format is invalid\nGot detail with --help/-h", name);
    return 0;
}

int optionParse(OPTION_ENTRY *oe, int argc, char **argv){
    int i, rs;
    for(i = 1; i < argc; i += 2){
        rs = _optionCheck(oe, argv[i], argv[i+1]);
    }

    return 1;
}
