// SDL stuff
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details
#include "h.h"
#include <SDL2/SDL.h>

const int SCSIZE = PIXEL * (2 * PRANGE + 1); /* window size */

namespace SDL {
    Color toColor(int col) {
        int red = col >> 16;
        int green = (col >> 8) - (red << 8);
        int blue = col - ((col >> 8) << 8);
        return {
            red: red,
            green: green,
            blue: blue
        };
    }
    /*void drawPixel(SDL_Renderer* renderer, int x, int y, Color col) {
        SDL_Rect tile = {
            x: PIXEL * x,
            y: PIXEL * y,
            w: PIXEL,
            h: PIXEL
        };
        SDL_SetRenderDrawColor(renderer, col.red, col.green, col.blue, 255);
        SDL_RenderFillRect(renderer, &tile);
    }*/
    SDL_Rect pixel(int x, int y) {
        return {
            x: PIXEL*x,
            y: PIXEL*y,
            w: PIXEL,
            h: PIXEL
        };
    }
}