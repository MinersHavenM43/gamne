// Deals with character movement
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details

#include "h.h"
using namespace std;

namespace game {
    bool noclip;
    PASS passable(pyr x,pyr y) {
        return content::wall(x, y).pass;
    }
    void noPassM(string s, PASS passtype) {
        if(passtype == worldb) {
            if(noclip) {
                std::cout << "Haha. Did you really think that ħæ©ĸ→ŋg can help you uncover the secrets of the world border? No. It won't. Unicode character 1F60E" << endl;
                return;
            }
            std::cout << "You cannot move through the " << s << "!" << endl;
            return;
        }
        if(passtype == nopass) { std::cout << "You cannot move through the " << s << "!" << endl; return; }
        if(passtype == chop) { std::cout << "You chop the " << s << "." << endl; return; }
        std::cout << "You " << s << "." << endl;
    }
    void helpText() {
        std::cout <<
        "Commands: \n"
        "H: shows a list of commands \n"
        "wasd: moves the character through the world (the @) \n"
        "F3: shows coordinates \n"
        "N: noclip \n"
        "T: debug temperature values \n"
        ;
    }
    void Update() {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window* window = SDL_CreateWindow(VERG, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, PIXEL * (2 * PRANGE + 1), PIXEL * (2 * PRANGE + 1), SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Event event;
        content::Wall wall;
        bool running = 1;
        pyr player2[2];
        int mx, my;

        player2[0] = player[0]; player2[1] = player[1];
        make(renderer);
        while(true) {
            if(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT)
                    running = 0;
                if(event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                    switch(event.key.keysym.sym) {
                        case SDLK_w: case SDLK_UP:
                            player2[1]++;
                        break;
                        case SDLK_a: case SDLK_LEFT:
                            player2[0]--;
                        break;
                        case SDLK_s: case SDLK_DOWN:
                            player2[1]--;
                        break;
                        case SDLK_d: case SDLK_RIGHT:
                            player2[0]++;
                        break;
                        case SDLK_h:
                            helpText();
                        break;
                        case SDLK_F3:
                            std::cout << "x, y: " << (int)player[0] << ", " << (int)player[1] << endl;
                        break;
                        case SDLK_t:
                            std::cout <<
                            "Height: " << Perlin::HeightMap(player[0],player[1]) <<
                            "Temp: " << Perlin::TempMap(player[0],player[1]) << endl;         
                        break;
                        case SDLK_n:
                            noclip = !noclip;
                            std::cout << ( noclip ? "Noclip activated \n" : "Noclip deactivated \n" );
                        break;
                    }
                    wall = content::wall(player2[0], player2[1]);
                    if(wall.pass != pass) {
                        if(wall.pass == worldb || !noclip) {
                            if(wall.pass == chop) {
                                emtiles.push_back({player2[0], player2[1]});
                            }
                            noPassM(wall.name, wall.pass); 
                            player2[0] = player[0]; player2[1] = player[1];
                        }
                    }
                    player[0] = player2[0]; player[1] = player2[1];
                }
                if(running == 0) break;
                make(renderer);
                SDL_RenderPresent(renderer);    
            }
            SDL_Delay(1);
        }
    }
}
