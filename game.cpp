// Used for rendering and random numbers
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace game {
    int player[2] = {10,0};
    unsigned int grand(int x, int y, int k, int seed = seed) {
        srand(x+seed);
        int xr = rand();
        srand(y+seed);
        int yr = rand();
        return (xr + yr) % k;
    }
    string getChar(int x, int y) {
        if(x == player[0] && y == player[1]) return "@";
        if(content::wall(x,y,TYPE::glyph) == ".") return content::biome(x,y,TYPE::glyph);
        return content::wall(x,y,TYPE::glyph);
    }
    void make() { // renders to console
        int x = player[0] - prange; int y = player[1] + prange;
        string tekh;
        while(y >= player[1] - prange) {
            tekh += getChar(x,y);
            x++;
            if(x > player[0] + prange) {
                y--;
                x = player[0] - prange;
                tekh += "\n"; 
            }
        }
        std::cout << tekh;
    }
}
