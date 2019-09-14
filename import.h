#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

int import(FILE* src, FILE* dest,  int nvars, unsigned short* bits);
