// defines the variables in h.h, hopefully that will be the solution to the "multiple definitions of 'x'" thing
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details
#include "h.h"

int seed = 10; // seed
int prange = 10; // player sight range

namespace PASSTYPE {
    int pass = 0;
    int nopass = 1;
}
namespace TYPE {
    int glyph = 0;
    int name = 1;
    int pass = 2;
}
