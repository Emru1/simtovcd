#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "timescale.h"
#include "scope.h"
#include "vars.h"
#include "vars_first.h"
#include "import.h"


int main(int argc, char** argv)
{
    //the number of device bits
    unsigned short* bits = calloc( 93, sizeof(unsigned short));

    FILE* source = fopen( argv[1], "rt");
    FILE* destination = fopen( argv[2], "wt");

    if(!source || !destination)
    {
    fprintf( stderr,    "No file specified!\n"            \
                        "./simtovcd [input] [output]\n"   );
    exit(1);
    }

    init(destination);

    timescale(source, destination);

    scope(destination);

    int nvars = vars(source, destination, bits);

    vars_first(source, destination, nvars, bits);

    import(source, destination, nvars, bits);

    free(bits);
    fclose(source);
    fclose(destination);

    return 0;
}
