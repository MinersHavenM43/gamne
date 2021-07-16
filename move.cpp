// Deals with character movement
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details
#include "h.h"
using namespace std;

namespace game {
    bool noclip;
    int passable(int x,int y) {
        return content::wall(x, y).pass;
    }
    void noPassM(string s, int passtype) {
        if(passtype == PASSTYPE::nopass) make("You cannot move through the " + s + "!");
        if(passtype == PASSTYPE::chop) make("You chop the " + s + ".");
    }
    void helpText() {
        std::cout <<
        "Commands: \n"
        "H: shows a list of commands \n"
        "y: renders the game without moving, before it was a test command used for showing the world when the player was stuck in spawn"
        "wasd: moves the character through the world (the @) \n"
        "3: shows coordinates \n"
        "N: noclip \n"
        ;
    }
    void move() {
        while(true) {
            char k;
            std::cin >> k;
            int oldPlayer[2] = {player[0], player[1]};
            switch(k) {
                case 'w':
                    player[1]++;
                break;
                case 'a':
                    player[0]--;
                break;
                case 's':
                    player[1]--;
                break;
                case 'd':
                    player[0]++;
                break;
                case 'H': // help
                    helpText();
                break;
                case 'y':
                    make("");
                break;
                case '3': //'f3':
                    std::cout << player[0] << ", " << player[1] << endl;
                break;
                case 'N': // nocliṕ
                    noclip = !noclip;
                    std::cout << ( noclip ? "Noclip activated \n" : "Noclip deactivated \n" );
                break;
            }
            content::Wall pwall = content::wall(player[0],player[1]);
            if(pwall.pass == PASSTYPE::nopass && !noclip) {
                player[0] = oldPlayer[0]; player[1] = oldPlayer[1]; 
                noPassM(pwall.name, PASSTYPE::nopass);
                
            }
            else if(pwall.pass == PASSTYPE::chop && !noclip) {
                emtiles.push_back({player[0],player[1]});
                player[0] = oldPlayer[0]; player[1] = oldPlayer[1]; 
                noPassM(pwall.name, PASSTYPE::chop);
            }
            else {
                if( k == 'w' || k == 'a' || k == 's' || k == 'd' ) {
                    make("");
                }
            }
        }
    }
}
