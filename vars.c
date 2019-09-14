#include "vars.h"

int vars(FILE* source, FILE* dest, unsigned short* bits)
{
    //array for devices names
    char** names = malloc(sizeof(char*) * 93);

    //array on which the function will work
    char* line = malloc(LINE_SIZE);
    int i = 0;
    int j = 0;
    int g = 0;

    for(i = 0; i < 93; i++)
        *(names+i) = malloc(128);

    //get first line of source file to array
    rewind(source);
    fgets(line, LINE_SIZE, source);

    //get names of devices
    for(i = 0; *(line+i) != '\0'; i++)
    {
        if( *(line + i) == '\t')
        {
            *( *(names + g) +j) = '\0';
            j = 0;
            g++;
        }
        else
        {
            *( *(names + g) + j) = *(line + i);
            j++;
        }
    }

    //get third line of source file to array
    fgets(line, LINE_SIZE, source);
    fgets(line, LINE_SIZE, source);

    //get the number of bits of each device
    for(i = 0, j = 0; *(line+i); i++)
    {
        if( *(line+i) == '\t')
        {
            j++;
            continue;
        }

        *(bits+j) += 1;
    }

    //print all devices, their names and  the number of bits
    for(i = 0; i < g; i++)
        fprintf(dest, "$var wire %u %c %s $end\n", *(bits+i),  i + '!', *(names+i));

    fprintf(dest, "$upscope $end\n" \
        "$enddefinitions $end\n" \
        "$dumpvars\n" );


    for(g = 0; g < 93; g++)
        free(*(names+g));

    free(names);
    free(line);

    return i;
}
