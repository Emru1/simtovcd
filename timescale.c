#include "timescale.h"


void timescale(FILE* source, FILE* dest)
{
	fprintf(dest,	"$timescale\n");

	rewind(source);
	char* line = malloc(2048);
	fgets(line, 2048, source);
	fgets(line, 2048, source);
	if(!(strcmp(line, "noclk\n")))
	{
		fprintf(dest,	"\t1s\n"		\
						"$end\n"	);
		free(line);
		return;
	}

	short i;
	short mult = 0;
	for(i = 0; *(line+i) ; i++)
	{
		if( ( *(line+i-2) == 'H' ) && ( *(line+i-1) == 'z') && ( *(line+i) == '\n'))
		{
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
	short pos1 = 0;
	short pos2 = 0;

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
	for(; !pos1; i--)
		if( *(line+i) == ':')
			pos1 = i;

	char* freqs = malloc(128);
	short j = 0;

	for(i = pos1+1; i < pos2; i++, j++)
		*(freqs+j) = *(line+i);
	*(freqs+j) = '\0';

	int freq = 1000 / atoi(freqs);
	if(freq == 1000)
	{
		fprintf(dest, "\t1");
		mult--;
	}
	else
		fprintf(dest, "\t%d", freq);
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
