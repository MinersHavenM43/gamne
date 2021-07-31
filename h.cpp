// defines the variables in h.h, hopefully that will be the solution to the "multiple definitions of 'x'" thing
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"

int Seed = 10; // seed

// no match for ‘operator==’ (operand types are ‘__gnu_cxx::__alloc_traits<std::allocator<tile> >::value_type {aka tile}’ and ‘tile’)
bool operator == (const tile c1, const tile c2) {
    if(c1.x == c2.x && c1.y == c2.y)
        return true;
    return false;
}

namespace PASS {
    int nopass = 0;
    int pass = 1;
    int chop = 2;
}
