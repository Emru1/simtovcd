#include "import.h"
#include <stdio.h>
#include <stdlib.h>

int import(FILE* src, FILE* dest, int nvars, unsigned short* bits)
{
    int i = 0;
    int j = 0;
    int g = 0;
    char* line = malloc(LINE_SIZE);
    char *c = line;

    //get third line of source file to string
    rewind(src);
    fgets(line, LINE_SIZE, src);
    fgets(line, LINE_SIZE, src);
    fgets(line, LINE_SIZE, src);


    for(i = 0; c; i++)
    {
        fprintf(dest, "#%d\n", i+1);
        g = 0;

        //check if device is multi-bit
        if(*(bits+g) > 1)
            fprintf(dest, "b");

        for(j = 0; *(line+j); j++)
        {
            if(*(line+j) == '\t')
            {

                //if device is multi-bit, add space before ident
                //GTKwave does not read input properly without this
                if(*(bits+g) > 1)
                    fprintf(dest, " ");

                //device identification char
                fprintf(dest, "%c", '!' + g);

                //avoid unnecessary LF
                if(*(line+j+1) != '\n')
                    fprintf(dest, "\n");

                //increment device number
                g++;

                //if device is multi-bit, add 'b' before state values
                if(*(bits+g) > 1)
                    fprintf(dest, "b");
            }
            else
            {
                //prints next char value from string
                fprintf(dest, "%c", *(line+j));
            }
        }

        //get next line from source file
        c = fgets(line, LINE_SIZE, src);
    }

    free(line);
    return 0;
}
