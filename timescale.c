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
	char* line = malloc(LINE_SIZE);								/* work array                 */

	rewind(source);												/* get second line            */
	fgets(line, LINE_SIZE, source);								/*                            */
	fgets(line, LINE_SIZE, source);								/*                            */

	fprintf(dest,	"$timescale\n");

	if(!(strcmp(line, "noclk\n")))								/* if there is no clock specified */
	{															/*                                */
		fprintf(dest,	"\t1s\n"								/*                                */
						"$end\n"	);							/*                                */
		free(line);												/*                                */
		return;													/*                                */
	}


	for(i = 0; *(line+i) ; i++)
	{
		if( ( *(line+i-2) == 'H' ) && ( *(line+i-1) == 'z') && ( *(line+i) == '\n'))
		{
			switch( *(line+i-3))				/* printing multiplier to destination             */
			{									/*                                                */
				case 'K':						/*                                                */
					mult = 2;					/*                                                */
					break;						/*                                                */
				case 'M':						/*                                                */
					mult = 3;					/*                                                */
					break;						/*                                                */
				case 'G':						/*                                                */
					mult = 4;					/*                                                */
					break;						/*                                                */
				default:						/*                                                */
					mult = 1;					/*                                                */
			}									/*                                                */
			break;								/*                                                */
		}
	}

	while(i != 0)								/* get position of ':' after the value of freq    */
	{											/*                                                */
		if( *(line+i) == ':')					/*                                                */
		{										/*                                                */
			pos2 = i;							/*                                                */
			break;								/*                                                */
		}										/*                                                */
		i--;									/*                                                */
	}											/*                                                */
	i--;										/*                                                */

	for(; !pos1; i--)							/* get position of ':' before value of freq       */
		if( *(line+i) == ':')					/*                                                */
			pos1 = i;							/*                                                */

	for(i = pos1+1; i < pos2; i++, j++)			/* get the value of frequency and put it to array */
		*(freqs+j) = *(line+i);					/*                                                */
	*(freqs+j) = '\0';							/*                                                */

	freq = 1000 / atoi(freqs);					/* get frequency to int value                     */

	if(freq == 1000)							/* when frequency is round 1000, decrease value   */
	{											/* of multiplier                                  */
		fprintf(dest, "\t1");					/*                                                */
		mult--;									/*                                                */
	}
	else
		fprintf(dest, "\t%d", freq);

	switch(mult)								/* print proper value of time multiplier to dest  */
	{											/*                                                */
		case 0:									/*                                                */
			fprintf(dest, "s\n");				/*                                                */
			break;								/*                                                */
		case 1:									/*                                                */
			fprintf(dest, "ms\n");				/*                                                */
			break;								/*                                                */
		case 2:									/*                                                */
			fprintf(dest, "us\n");				/*                                                */
			break;								/*                                                */
		case 3:									/*                                                */
			fprintf(dest, "ns\n");				/*                                                */
			break;								/*                                                */
		case 4:									/*                                                */
			fprintf(dest, "ps\n");				/*                                                */
			break;								/*                                                */
		case 5:									/*                                                */
			fprintf(dest, "fs\n");				/*                                                */
			break;								/*                                                */
		default:								/*                                                */
			fprintf(dest, "s\n");				/*                                                */
	}

	fprintf(dest, "$end\n");
	free(line);
	free(freqs);
}
