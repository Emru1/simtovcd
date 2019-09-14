#include "init.h"

int init(FILE* dest)
{
    //that function prints current date and program version to destination file

    time_t sec;
    time(&sec);
    struct tm* timex = localtime(&sec);
    fprintf( dest, 	"$date\n"                                           \
            "\t%02d-%02d-%04d %02d:%02d:%02d\n"                         \
            "$end\n",                                                   \
            timex->tm_mday, (timex->tm_mon)+1, (timex->tm_year)+1900,   \
            timex->tm_hour, timex->tm_min, timex->tm_sec                );

    fprintf( dest, 	"$version\n"                                        \
        "\tsimtovcd 0.2\n"                                              \
        "$end\n"                                                        );
    return 1;
}
