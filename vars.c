#include "vars.h"

int vars(FILE* source, FILE* dest)
{
	char* line = malloc(2048);
	rewind(source);
	fgets(line, 2048, source);
	int i;
	char** names = malloc(sizeof(char*) * 93);
	for(i = 0; i < 93; i++)
		*(names+i) = malloc(128);
	int j = 0;
	int g = 0;
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
	for(i = 0; i < g; i++)
	{
		fprintf(dest, "$var wire 1 %c %s $end\n", i + '!', *(names+i));
	}
	for( g = 0; g < 93; g++)
		free(*(names+g));
	free(names);
	free(line);
	fprintf(dest, 	"$upscope $end\n"			\
					"$enddefinitions $end\n"	\
					"$dumpvars\n"				);
	return i;
}
