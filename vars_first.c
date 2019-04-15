#include "vars_first.h"

int vars_first(FILE* src, FILE* dest, int nvars, unsigned short* bits)
{
	rewind(src);

	int i = 0;
	int j = 0;
	char* line = malloc(LINE_SIZE);					/* work array   */

	fgets(line, LINE_SIZE, src);					/* skpi 3 lines */
	fgets(line, LINE_SIZE, src);					/*              */
	fgets(line, LINE_SIZE, src);					/*              */



	if(*(bits+j) > 1)									/* check if first value is multibit */
		fprintf(dest, "b");								/*                                  */

	for(i = 0; *(line+i); i++)
	{
		if(*(line+i) == '\t')
		{
			if(*(bits+j) > 1)							/* if multibit - add space before ident */
				fprintf(dest, " ");						/* gtkwave doesn't read file without it */

			fprintf(dest, "%c", '!' + j);				/* print ident mark                     */

			if(*(line+i+1) != '\n')						/* avoid unnecesary LF                  */
				fprintf(dest, "\n");					/*                                      */

			j++;										/* increment device number              */

			if(*(bits+j) > 1)							/* if multibit - add 'b'                */
				fprintf(dest, "b");						/*                                      */
		}
		else
		{												/* printing a value from input file     */
			fprintf(dest, "%c", *(line+i));				/*                                      */
		}												/*                                      */
	}

	fprintf(dest, "$end\n");
	free(line);
	return 0;
}
