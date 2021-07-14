// defines the variables in h.h, hopefully that will be the solution to the "multiple definitions of 'x'" thing
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"

int seed = 10; // seed
int prange = 10; // player sight range

// no match for ‘operator==’ (operand types are ‘__gnu_cxx::__alloc_traits<std::allocator<coord> >::value_type {aka coord}’ and ‘coord’)
bool operator == (const coord c1, const coord c2) {
    if(c1.x == c2.x && c1.y == c2.y)
        return true;
    return false;
}

namespace PASSTYPE {
    int nopass = 0;
    int pass = 1;
    int chop = 2;
}
namespace TYPE {
    int glyph = 0;
    int name = 1;
    int pass = 2;
}
