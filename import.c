#include "import.h"
#include <stdio.h>
#include <stdlib.h>

int import(FILE* src, FILE* dest, int nvars)
{
	rewind(src);
	const short line_size = (2048);
	char* line = malloc(line_size);
	fgets(line, line_size, src);
	fgets(line, line_size, src);
	fgets(line, line_size, src);
	int i, j;
	char *c = line;
	for(i = 0; c; i++)
	{
		fprintf(dest, "#%d\n", i);
		for(j = 0; j < nvars; j++)
			fprintf(dest, "%c%c\n", *(line + 2*j), '!' + j);

		c = fgets(line, line_size, src);
	}
	free(line);
	return 0;
}
