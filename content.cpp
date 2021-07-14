// defines biome locations and things like that
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace content {
    /* int test = 3;
    int testf(int h) {
        return h + 3;
    } */

    float distance(int x, int y) {
        return sqrt(x*x + y*y);
    }
    bool isEmpty(coord c) {
        int ecsize = game::emptytiles.size();
        int z = 0; // doesn't work if it's just int z; for some reason
        while(z < ecsize) {
            if(game::emptytiles[z] == c) return true;
            z++;
        }
        return false;
    }
    coord xy(int x, int y) {
        return {x: (short)x, y: (short)y};
    }

    Biome biome(int x, int y) {
        if(sinf(x/10.) + sinf(y/10.) > 1) {
            return {2, "^", "Mountains"};
        }
        if(sinf(x/10.) + sinf(y/10.) > -0.5) {
            return {1, ",", "Forest"};
        }
        return {0, ".", "Plains"}; // default
    }
    Wall wall(int x, int y) {
        int cbiome = biome(x, y).id;
        if(isEmpty(xy(x,y))) return {0, "", "", PASSTYPE::pass};
        if(x == 0 && y == 0) return {0, "", "", PASSTYPE::pass}; // no walls at spawn :)
        switch(cbiome) {
            case 1:
                if(game::grand(x, y, 20, seed) < 4) {
                    return {1, "+", "tree", PASSTYPE::chop};
                }
            break;
            case 2:
                if(game::grand(x, y, 20, seed) < 10) {
                    return {2, "Λ", "mountain", PASSTYPE::nopass};
                }
            break;
        }
        return {0, "", "", PASSTYPE::pass}; // keep this at last
    }
}
