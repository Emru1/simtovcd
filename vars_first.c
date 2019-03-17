#include "vars_first.h"

int vars_first(FILE* src, FILE* dest, int nvars)
{
	rewind(src);
	const short line_size = (2048);
	char* line = malloc(line_size);
	fgets(line, line_size, src);
	fgets(line, line_size, src);
	fgets(line, line_size, src);
	int i;

	for(i = 0; i < nvars; i++)
		fprintf(dest, "%c%c\n", *(line + 2*i), '!' + i);

	fprintf(dest, "$end\n");
	free(line);
	return 0;
}
