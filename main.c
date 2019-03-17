#include <stdio.h>
#include "init.h"
#include "timescale.h"
#include "scope.h"
#include "vars.h"
#include "vars_first.h"
#include "import.h"



int main(int argc, char** argv)
{
	FILE* source = fopen( argv[1], "rt");
	FILE* destination = fopen( argv[2], "wt");

	if(!source || !destination)
		exit(1);

	init(destination);
	timescale(source, destination);
	scope(destination);
	int nvars = vars(source, destination);
	vars_first(source, destination, nvars);
	import(source, destination, nvars);

	fclose(source);
	fclose(destination);

	return 0;
}
