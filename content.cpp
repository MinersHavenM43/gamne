// defines biome locations and things like that
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace content {
    /* int test = 3;
    int testf(int h) {
        return h + 3;
    } */

    Wall wnone = {0, "", "", PASSTYPE::pass};

    float distance(int x, int y) {
        return sqrt(x*x + y*y);
    }
    bool isEmpty(tile c) {
        int ecsize = game::emtiles.size();
        int z = 0; // doesn't work if it's just int z; for some reason
        while(z < ecsize) {
            if(game::emtiles[z] == c) return true;
            z++;
        }
        return false;
    }
    tile xy(int x, int y) {
        return {x: (short)x, y: (short)y};
    }

    Biome biome(int x, int y) {
        if(sinf((x+200)/100.) + sinf((y+30)/100.) < 0.5) {
            return {3, ";", "Ocean"};
        }
        if(sinf((x+200)/100.) + sinf((y+30)/100.) < 0.55) {
            return {4, "_", "Beach"};
        }
        if(sinf(x/10.) + sinf(y/10.) > 1) {
            return {2, "^", "Mountains"};
        }
        if(sinf(x/21.) + sinf(y/21.) > -0.5) {
            return {1, ",", "Forest"};
        }

        return {0, ".", "Plains"}; // keep thing at last
    }
    Wall wall(int x, int y) {
        int cbiome = biome(x, y).id;
        if(isEmpty(xy(x,y))) return wnone;
        if(x == 0 && y == 0) return wnone; // no walls at spawn :)
        if(abs(x) > BORDER || abs(y) > BORDER) return {10, "/", "world border", PASSTYPE::nopass};
        switch(cbiome) {
            case 0:
                if(game::grand(x, y, 100, seed) < 1) {
                    return {1, "+", "tree", PASSTYPE::chop};
                }
            break;
            case 1:
                if(game::grand(x, y, 20, seed) < 4) {
                    return {1, "+", "tree", PASSTYPE::chop};
                }
            break;
            case 2:
                if(game::grand(x, y, 60, seed) < 1 && sinf(x/10.) + sinf(y/10.) < 1.5) {
                    return {3, "+", "pine tree", PASSTYPE::chop};
                }
                else if(game::grand(x, y, 20, seed) < 10) {
                    return {2, "Λ", "mountain", PASSTYPE::nopass};
                }
            break;
            case 3:
                return {4, ";", "ocean", PASSTYPE::nopass};
        }

        return {0, "", "", PASSTYPE::pass}; // keep this at last
    }
}
