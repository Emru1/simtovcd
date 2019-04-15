#include "vars.h"

int vars(FILE* source, FILE* dest, unsigned short* bits)
{
	char** names = malloc(sizeof(char*) * 93);						/* array for names of devices */
	char* line = malloc(LINE_SIZE);									/* working string             */
	int i = 0;
	int j = 0;
	int g = 0;

	for(i = 0; i < 93; i++)
		*(names+i) = malloc(128);

	rewind(source);													/* Getting here first line of logisim output     */
	fgets(line, LINE_SIZE, source);									/*                                               */

	for(i = 0; *(line+i) != '\0'; i++)								/* Getting names of devices                      */
	{																/*                                               */
		if( *(line + i) == '\t')									/*                                               */
		{															/*                                               */
			*( *(names + g) +j) = '\0';								/*                                               */
			j = 0;													/*                                               */
			g++;													/*                                               */
		}															/*                                               */
		else														/*                                               */
		{															/*                                               */
			*( *(names + g) + j) = *(line + i);						/*                                               */
			j++;													/*                                               */
		}															/*                                               */
	}																/*                                               */

	fgets(line, LINE_SIZE, source);									/* Getting third line of logisim output          */
	fgets(line, LINE_SIZE, source);									/*                                               */

	for(i = 0, j = 0; *(line+i); i++)								/* Number of bits for each device                */
	{																/*                                               */
		if( *(line+i) == '\t')										/*                                               */
		{															/*                                               */
			j++;													/*                                               */
			continue;												/*                                               */
		}															/*                                               */
																	/*                                               */
		*(bits+j) += 1;												/*                                               */
	}																/*                                               */

	for(i = 0; i < g; i++)
		fprintf(dest, "$var wire %u %c %s $end\n", *(bits+i),  i + '!', *(names+i));

	fprintf(dest, 	"$upscope $end\n"			\
					"$enddefinitions $end\n"	\
					"$dumpvars\n"				);


	for(g = 0; g < 93; g++)
		free(*(names+g));

	free(names);
	free(line);

	return i;
}
