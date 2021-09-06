// defines biome locations and things like that
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

#define BIOME(glyph, color, name, varname, id) content::Biome varname = {id, glyph, name, color};
#define WALL(glyph, color, name, varname, passs, id) content::Wall varname = {id, glyph, name, passs, color};

// 1.0
BIOME(".", 0x5AD05A, "Plains", biPlains, 0)
BIOME(",", 0x209020, "Forest", biForest, 1)
BIOME("^", 0x666666, "Mountains", biMountains, 2)

WALL("" , -      1, "", waNone, pass, 0)
WALL("+", 0x502A20, "tree", waTree, chop, 1)
WALL("Λ", 0x333333, "mountain", waMountain, nopass, 2)

// 1.1
BIOME("_", 0xFFFFB0, "Shore", biShore, 3)
BIOME("*", 0x1A1AA0, "Ocean", biOcean, 4)

WALL("+", 0x4F332B, "pine tree", waPineTree, chop, 3)
WALL("" , -      1, "ocean", waOcean, nopass, 4)
WALL("/", 0x200020, "world border", waWB, worldb, 5)

// 1.2
BIOME("-", 0xFFD08A, "Desert", biDesert, 5)
BIOME("'", 0x305C30, "Taiga", biTaiga, 6)
BIOME("\"", 0xF0F0F0, "Tundra", biTundra, 7)
BIOME("~", 0x15AA15, "Jungle", biJungle, 8)
BIOME("°", 0x3A3AA1, "Cold Ocean", biCOcean, 9)

WALL("ψ", 0x209020, "cactus", waCactus, chop, 6)
WALL("O", 0x7777D4, "Ice Patch", waIce, pass, 7)
WALL("+", 0x503A20, "palm tree", waPalm, chop, 8)

// 1.3
BIOME("¨", 0x204020, "Swamp", biSwamp, 10)

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
            if(HEIGHT < 0.4 && HEIGHT > 0.1 && TEMP < 0.1) {
                return biCOcean;
            }
            if(HEIGHT < 0.4) {
                return biOcean;
            }
            if(HEIGHT < 0.45) {
                if(TEMP > 0.7 && TEMP < 0.75) return biSwamp;
                return biShore;
            }
        }

        if(HEIGHT > 0.85) {
            return biMountains;
        }
        if(TEMP < 0.3) {
            if(TEMP < 0.1) {
                return biTundra;
            }
            return biTaiga;
        } 
        if(TEMP > 0.75) {
            if(TEMP > 0.9) {
                return biJungle;
            }
            return biDesert;
        }
        if(TEMP > 0.5) {
            if(HEIGHT < 0.5 && TEMP > 0.7) return biSwamp;
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
            case 3:
                if(GRAND(100) < 1) {
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
                if(GRAND(100) < 2) {
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
            case 10: // swamp
                if(Perlin::PerlinOc(x, y, 2, 5, Seed) < 0.5) {
                    return waOcean;
                }
                if(GRAND(100) < 8) {
                    return waTree;
                }
            break;
        }
        return waNone; // keep this at last
    }
}
