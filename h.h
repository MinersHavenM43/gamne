// Main header file
/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
