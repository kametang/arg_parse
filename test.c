#include "option_parse.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i;
    char c = '\0';
    char *s = NULL;
    float f;
    double d;
    OPTION_ENTRY oe[] = {
        {"int", 'i', &i, "INT", OPTION_TYPE_INT},
        {"char", 'c', &c, "CHAR", OPTION_TYPE_CHAR},
        {"string", 's', &s, "STRING", OPTION_TYPE_STRING},
        {"float", 'f', &f, "FLOAT", OPTION_TYPE_FLOAT},
        {"double", 'd', &d, "DOUBLE", OPTION_TYPE_DOUBLE},
        {NULL}
    };
    optionParse(oe, argc, argv);
    printf("%d, %c, %s, %f, %lf\n", i, c, s, f, d);
    return 0;
}
