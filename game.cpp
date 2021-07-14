// Used for rendering and random numbers
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace game {
    short player[2] = {0,0};
    vector<coord> emptytiles;

    int grand(short x, short y, int k, int seed = seed) {
        srand(13*x + 29*y);
        return rand() % k;
    }
    string getChar(int x, int y) {
        if(x == player[0] && y == player[1]) return "@";
        if(!content::wall(x,y).id) return content::biome(x,y).glyph;
        return content::wall(x,y).glyph;
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
