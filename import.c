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

	rewind(src);
	fgets(line, LINE_SIZE, src);							/* get to third line                    */
	fgets(line, LINE_SIZE, src);							/*                                      */
	fgets(line, LINE_SIZE, src);							/*                                      */


	for(i = 0; c; i++)
	{
		fprintf(dest, "#%d\n", i+1);
		g = 0;

		if(*(bits+g) > 1)									/* check if first value is multibit     */
			fprintf(dest, "b");								/*                                      */

		for(j = 0; *(line+j); j++)
		{
			if(*(line+j) == '\t')
			{
				if(*(bits+g) > 1)							/* if multibit - add space before ident */
					fprintf(dest, " ");						/* gtkwave doesn't read file without it */

				fprintf(dest, "%c", '!' + g);				/* ident mark                           */

				if(*(line+j+1) != '\n')						/*  avoid unnecesary LF                 */
					fprintf(dest, "\n");					/*                                      */

				g++;										/* increment device number              */

				if(*(bits+g) > 1)							/* if multibit - add 'b'                */
					fprintf(dest, "b");						/*                                      */
			}
			else
			{												/* prints next char of value            */
				fprintf(dest, "%c", *(line+j));				/*                                      */
			}
		}

		c = fgets(line, LINE_SIZE, src);
	}

	free(line);
	return 0;
}
