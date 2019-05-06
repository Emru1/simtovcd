#include "vars_first.h"

int vars_first(FILE* src, FILE* dest, int nvars, unsigned short* bits)
{
	rewind(src);

	int i = 0;
	int j = 0;
	//work array
	char* line = malloc(LINE_SIZE);

	//get third line of source file to array
	fgets(line, LINE_SIZE, src);
	fgets(line, LINE_SIZE, src);
	fgets(line, LINE_SIZE, src);


	//check if first value is multi-bit
	if(*(bits+j) > 1)
		fprintf(dest, "b");

	for(i = 0; *(line+i); i++)
	{
		if(*(line+i) == '\t')
		{
			//if device is multibit, add space before ident
			//GTKwave does not read properly without it
			if(*(bits+j) > 1)
				fprintf(dest, " ");

			//print device identification mark
			fprintf(dest, "%c", '!' + j);

			//avoid unnecesary LF
			if(*(line+i+1) != '\n')
				fprintf(dest, "\n");

			//increment device number
			j++;

			//if device is multi-bit, add 'b' before state values
			if(*(bits+j) > 1)
				fprintf(dest, "b");
		}
		else
		{
			//prints next char value from string
			fprintf(dest, "%c", *(line+i));	
		}
	}

	fprintf(dest, "$end\n");
	free(line);
	return 0;
}
