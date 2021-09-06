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
#include <vector>
#include <SDL2/SDL.h>

extern int tilesize;
extern int sightrange;
extern int tick;

#define pyr short
// used for "syncing" coordinate types without having to replace 2763 instances

extern int Seed; // seed

#define PIXEL tilesize /* tile size */
#define PRANGE sightrange // player sight range
#define TICK tick /* tile size */

#define BORDER 32700 // world border

#define VERSION "v1.3π"
#define VERG "Gamne " VERSION

struct tile { // coordinate (used for empty cells)
    pyr x, y;
};

// no match for ‘operator==’ (operand types are ‘__gnu_cxx::__alloc_traits<std::allocator<tile> >::value_type {aka tile}’ and ‘tile’)
bool operator == (const tile c1, const tile c2);

// values used to determine whether or not you can walk through a wall
enum PASS {
    nopass, pass, chop, worldb
};

// namespaces
namespace content {
    struct Biome {
        int id;
        std::string glyph, name;
        int color;
    };
    struct Wall {
        int id;
        std::string glyph, name;
        PASS pass;
        int color;
    };

    bool isEmpty(tile c);
    Biome biome(pyr x, pyr y);
    Wall wall(pyr x, pyr y);
}
namespace game {
    extern pyr player[2];
    extern std::vector<tile> emtiles;

    int grand(pyr x, pyr y, int k, int seed);
    void make(SDL_Renderer* renderer);
    void Update();
}
namespace Perlin {
    double Perlin(double x, double y, int seed);
    double PerlinOc(double x, double y, int oc, double sc, int seed, double ocs = 4);

    double HeightMap(double x, double y);
    double TempMap(double x, double y);
}
namespace SDL {
    struct Color {
        int
        red,
        green,
        blue;
    };
    Color toColor(int col);
    SDL_Rect pixel(int x, int y);
}

#endif
