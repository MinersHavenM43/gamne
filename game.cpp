// Used for rendering and random numbers
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace game {
    short player[2] = {0,0};
    vector<tile> emtiles; // empty tiles

    int grand(short x, short y, int k, int seed = seed) {
        srand(211*x + 379*y + seed);
        return rand() % k;
    }
    string getChar(int x, int y) {
        if(x == player[0] && y == player[1]) return "@";
        if(!content::wall(x,y).id) return content::biome(x,y).glyph;
        return content::wall(x,y).glyph;
    }
    string repeat(string s, int r) {
        string ss;
        for(int i; i < r; i++) {
            ss += s;
        }
        return ss;
    }
    void make(string msg) { // renders to console
        int x = player[0] - PRANGE; int y = player[1] + PRANGE;
        string tekh;
        system("clear"); // clears the terminal
        tekh += repeat(" ", PRANGE - content::biome(player[0], player[1]).name.size()/2) + content::biome(player[0], player[1]).name + "\n";
        while(y >= player[1] - PRANGE) {
            tekh += getChar(x,y);
            x++;
            if(x > player[0] + PRANGE) {
                y--;
                x = player[0] - PRANGE;
                tekh += "\n"; 
            }
        }
        tekh += msg;
        std::cout << tekh << endl;
    }
}
