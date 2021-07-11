#ifndef PASS_ONCE
#define PASS_ONCE

#include <iostream>
#include <string>
#include <cmath>

extern int seed; // seed
extern int prange; // player sight range

struct cell { // will be used later, much later
    short x, y;
    char wall, biome;
};

namespace PASSTYPE {
    extern int pass;
    extern int nopass;
}
namespace TYPE {
    extern int glyph;
    extern int name;
    extern int pass;
}

namespace content {
    std::string biome(int x, int y, int type);
    std::string wall(int x, int y, int type);
}
namespace game {
    extern int player[2];
    unsigned int grand(int x, int y, int k, int seed);
    void make();
    void move();
}

#endif