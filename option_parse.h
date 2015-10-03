#ifndef __OPTION_ENTRY__
#define __OPTION_ENTRY__

#include <stdlib.h>

#ifndef option_print
#define option_print(args ...) printf(args)
#endif

typedef enum {
    OPTION_TYPE_INT,
    OPTION_TYPE_CHAR,
    OPTION_TYPE_STRING,
    OPTION_TYPE_FLOAT,
    OPTION_TYPE_DOUBLE
} OPTION_TYPE;

typedef enum { ARG_SINGLE, ARG_DOUBLE } ARG_TYPE;

typedef struct _option_entry{
    char *longname;
    char shortname;
    void *buf;
    char *description;
    OPTION_TYPE type;
} OPTION_ENTRY;

int optionParse(OPTION_ENTRY *oe, int argc, char **argv);

#endif
