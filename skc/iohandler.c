#include "iohandler.h"

char* optarg = NULL;
int optind = 1;
int optLen = 0;
int optCur = 0;

int t_getopt(int argc, char* argv[], const char* optstring)
{
    if (argc > 1) {
        if ((optind >= argc))
        {
            return -1;
        }
        if ((argv[optind][0] != '-') || (argv[optind][0] == 0))
        {
            return -1;
        }

        if (optLen == 0) {
            optLen = strlen(argv[optind] + 1);
        }
    
        int opt = argv[optind][optCur+1];
        optCur++;

        const char* p = strchr(optstring, opt);

        if (p == NULL)
        {
            return 63;
            optind = argc;
        }
        if (p[1] == ':' && optLen == 1)
        {
            optind++;
            if (optind >= argc)
            {
                return 63;
                optind = argc;
            }
            optarg = argv[optind];
            optind++;
        }
        if (optCur >= optLen)
        {
            optind++;
            optCur = 0;
            optLen = 0;
        }
        return opt;
    }
    return -1;
}

char * getHelp()
{
    return (char *)"A simplified Kotlin compiler for JVM. The list of supported functionality can be found here:\n\t<https://github.com/DedZinoviy/simplified_kotlin_compiler>\
    \nusage:\n\tskc[.exe] [options] input_file\noptions:\n\
    \t-c - output of the program tree in DOT language to the console;\n\
    \t-f - output of the program tree as a file in DOT language; output file name: \"program.gv\";\n\
    \t-h - help; in this mode, the parser does not start working;\n\
    \t-t - output of the found source tokens.\n";
}
