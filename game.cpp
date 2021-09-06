// Used for rendering and random numbers
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace game {
    pyr player[2] = {0, 0};
    vector<tile> emtiles = { {0,0} }; // empty tiles

    int grand(pyr x, pyr y, int k, int seed) {
        srand(x*y*y + 7*x*y + x - y + seed);
        return rand() % k;
    }

    string getChar(pyr x, pyr y) {
        content::Wall wall;
        wall = content::wall(x,y);
        if(x == player[0] && y == player[1]) return "@";
        if(wall.glyph == "") return content::biome(x,y).glyph;
        return wall.glyph;
    }
    SDL::Color getColor(pyr x, pyr y) {
        content::Wall wall;
        content::Biome biome;
        wall = content::wall(x,y);
        biome = content::biome(x,y);
        if(x == player[0] && y == player[1]) return {0,0,0};
        if(wall.color == -1) {
            if(biome.id == 10 && wall.id == 4) return SDL::toColor(0x101040);
            return SDL::toColor(biome.color);
        }
        return SDL::toColor(wall.color);
        /*return
        {
            red: 255 * Perlin::TempMap(x, y),
            green: 0,
            blue: 255 * Perlin::HeightMap(x, y),
        };*/
    }

    string repeat(string s, int r) {
        string ss;
        for(int i; i < r; i++) {
            ss += s;
        }
        return ss;
    }
    void make(SDL_Renderer* renderer) { // renders to console
        pyr x = player[0] - PRANGE; pyr y = player[1] + PRANGE;
        pyr x0 = 0; pyr y0 = 0;
        SDL::Color color;
        SDL_Rect tile;
        while(y0 <= 2 * PRANGE) {
            color = getColor(x,y);
            tile = SDL::pixel(x0,y0);
            SDL_SetRenderDrawColor(renderer, color.red, getColor(x,y).green, getColor(x,y).blue, 255);
            SDL_RenderFillRect(renderer, &tile);
            x++;
            x0++;
            if(x0 > 2 * PRANGE) {
                y--;
                y0++;
                x = player[0] - PRANGE;
                x0 = 0;
            }
        }
    }
}
