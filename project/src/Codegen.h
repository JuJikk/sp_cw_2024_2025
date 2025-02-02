#pragma once

#include "header.h"

#include <stdio.h>
#include <stdlib.h>

namespace Codegen {
    void codegen(FILE* outFile, struct astNode* node);
}