#pragma once

#include "header.h"
#include <stdio.h>

namespace LexicAnalyzer {
	unsigned int getTokens(FILE* F);
	void printTokens(void);
	void fprintTokens(FILE* F);
}
