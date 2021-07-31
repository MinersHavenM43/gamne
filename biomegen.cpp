// defines biome locations and things like that
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

#define BIOME(glyph, name, varname, id) content::Biome varname = {id, glyph, name};
#define WALL(glyph, name, varname, pass, id) content::Wall varname = {id, glyph, name, pass};

// 1.0
BIOME(".", "Plains", biPlains, 0)
BIOME(",", "Forest", biForest, 1)
BIOME("^", "Mountains", biMountains, 2)

WALL("", "", waNone, PASS::pass, 0)
WALL("+", "tree", waTree, PASS::chop, 1)
WALL("Λ", "mountain", waMountain, PASS::nopass, 2)

// 1.1
BIOME("_", "Shore", biShore, 3)
BIOME("*", "Ocean", biOcean, 4)

WALL("+", "pine tree", waPineTree, PASS::chop, 3)
WALL("", "ocean", waOcean, PASS::nopass, 4)
WALL("/", "world border", waWB, PASS::nopass, 5)

// 1.2
BIOME("¯", "Desert", biDesert, 5)
BIOME("'", "Taiga", biTaiga, 6)
BIOME("\"", "Tundra", biTundra, 7)
BIOME("~", "Jungle", biJungle, 8)
BIOME("°", "Cold Ocean", biCOcean, 9)

WALL("ψ", "Cactus", waCactus, PASS::chop, 6)
WALL("O", "Ice Patch", waIce, PASS::pass, 7)
WALL("+", "Palm Tree", waPalm, PASS::chop, 8)

namespace content {
    /* int test = 3;
    int testf(int h) {
        return h + 3;
    } */

    float distance(pyr x, pyr y) {
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

    Biome biome(pyr x, pyr y) {
        using namespace Perlin;
        double HEIGHT = HeightMap(x,y);
        double TEMP = TempMap(x,y);
        
        if(HEIGHT < 0.45) { // Oceanic biome optimization
            if(HEIGHT < 0.4 && HEIGHT > 0.1 && TEMP < 0.3) {
                return biCOcean;
            }
            if(HEIGHT < 0.4) {
                return biOcean;
            }
            if(HEIGHT < 0.45) {
                return biShore;
            }
        }

        if(HEIGHT > 0.85) {
            return biMountains;
        }
        if(TEMP < 0.1) {
            return biTundra;
        }
        if(TEMP < 0.3) {
            return biTaiga;
        } 
        if(TEMP > 0.85) {
            return biJungle;
        }
        if(TEMP > 0.75) {
            return biDesert;
        }
        if(TEMP > 0.5) {
            return biForest;
        }
        return biPlains; // keep this last
    }
    Wall wall(pyr x, pyr y) {
        #define GRAND(k) game::grand(x, y, k, Seed)
        int cbiome = biome(x, y).id;
        if(isEmpty({x,y})) return waNone;
        if(abs(x) > BORDER || abs(y) > BORDER) return waWB;
        switch(cbiome) {
            case 0: // plains
                if(GRAND(100) < 1) {
                    return waTree;
                }
            break;
            case 1: // forest
                if(GRAND(20) < 4) {
                    return waTree;
                }
            break;
            case 2: // mountains
                if(GRAND(60) < 1) {
                    return waPineTree;
                }
                else if(GRAND(20) < 100 * (Perlin::HeightMap(x,y)-.85)) {
                    return waMountain;
                }
            break;
            case 3: // (shore) doesn't need to exist  edit: nevermind
                if(GRAND(100) < 4) {
                    return waPalm;
                }
            break;
            case 4: // ocean
                return waOcean;
            break;
            case 5: // desert
                if(GRAND(60) < 1) {
                    return waCactus;
                }
            break;
            case 6: // taiga
                if(GRAND(20) < 4) {
                    return waPineTree;
                }
            break;
            case 7: // tundra
                if(GRAND(100) < 4) {
                    return waPineTree;
                }
            break;
            case 8: // jungle
                if(GRAND(10) < 4) {
                    return waTree;
                }
            break;
            case 9: // cold ocean
                if(Perlin::TempMap(x, y) < 0.2) {
                    return waIce;
                }
                return waOcean;
            break;
        }
        return waNone; // keep this at last
    }
}
