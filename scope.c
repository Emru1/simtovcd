#include "scope.h"

int scope(FILE* dest)
{
	fprintf(dest,	"$scope\n"				\
					"\tmodule logic\n"	    \
					"$end\n"		        );
	return 1;
}
