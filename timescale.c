#include "timescale.h"


void timescale(FILE* source, FILE* dest)
{
    short pos1 = 0;
    short pos2 = 0;
    short i = 0;
    short mult = 0;
    short j = 0;
    int freq = 0;

    char* freqs = malloc(128);

    //array on which the function will work
    char* line = malloc(LINE_SIZE);

    //get second line to string from source file
    rewind(source);
    fgets(line, LINE_SIZE, source);
    fgets(line, LINE_SIZE, source);

    fprintf(dest, "$timescale\n");

    //if no clock is specified in source file
    if(!(strcmp(line, "noclk\n")))
    {
        fprintf(dest, "\t1s\n"  \
            "$end\n"            );
        free(line);
        return;
    }


    for(i = 2; *(line+i) ; i++)
    {
        if( ( *(line+i-2) == 'H' ) && ( *(line+i-1) == 'z') && ( *(line+i) == '\n'))
        {
            //print frequency multiplier to destination file
            switch( *(line+i-3))
            {
                case 'K':
                    mult = 2;
                    break;
                case 'M':
                    mult = 3;
                    break;
                case 'G':
                    mult = 4;
                    break;
                default:
                    mult = 1;
            }
            break;
        }
    }

    //get position of ':' which is located after frequency value
    while(i != 0)
    {
        if( *(line+i) == ':')
        {
            pos2 = i;
            break;
        }
        i--;
    }
    i--;

    //get position of ':' which is located before frequency value
    for(; !pos1; i--)
        if( *(line+i) == ':')
            pos1 = i;

    //get frequency value from source file to array
    for(i = pos1+1; i < pos2; i++, j++)
        *(freqs+j) = *(line+i);
    *(freqs+j) = '\0';

    //convert frequency array to integer
    freq = 1000 / atoi(freqs);

    //when frequency is equal to 1000, increase value of multiplier
    if(freq == 1000)
    {
        fprintf(dest, "\t1");
        mult++;
    }
    else
        fprintf(dest, "\t%d", freq);

    //print time multiplier value to destination file
    switch(mult)
    {
        case 0:
            fprintf(dest, "s\n");
            break;
        case 1:
            fprintf(dest, "ms\n");
            break;
        case 2:
            fprintf(dest, "us\n");
            break;
        case 3:
            fprintf(dest, "ns\n");
            break;
        case 4:
            fprintf(dest, "ps\n");
            break;
        case 5:
            fprintf(dest, "fs\n");
            break;
        default:
        fprintf(dest, "s\n");
    }

    fprintf(dest, "$end\n");
    free(line);
    free(freqs);
}
