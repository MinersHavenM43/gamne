// Deals with character movement
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details
#include "h.h"
using namespace std;

namespace game {
    int passable(int x,int y) {
        return content::wall(x, y).pass;
    }
    void noPassM(string s, int passtype) {
        if(passtype == PASSTYPE::nopass) cout << "You cannot move through the " << s << "!" << endl;
        if(passtype == PASSTYPE::chop) cout << "You chop the " << s << "." << endl;
    }
    void helpText() {
        std::cout <<
        "Commands: \n"
        "help: shows a list of commands \n"
        "wasd: moves the character through the world (the @) \n"
        "f3: shows coordinates \n"
        "y: test command used for showing the world when the player was stuck in spawn"
        ;
    }
    void move() {
        while(true) {
            int k;
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
                case 'help':
                    helpText();
                break;
                case 'y':
                    make();
                break;
                case 'f3':
                    std::cout << player[0] << ", " << player[1] << endl;
                break;
            }
            content::Wall pwall = content::wall(player[0],player[1]);
            if(pwall.pass == PASSTYPE::nopass) {
                noPassM(pwall.name, PASSTYPE::nopass);
                player[0] = oldPlayer[0]; player[1] = oldPlayer[1]; 
            }
            else if(pwall.pass == PASSTYPE::chop) {
                noPassM(pwall.name, PASSTYPE::chop);
                game::emptytiles.push_back({player[0],player[1]});
                player[0] = oldPlayer[0]; player[1] = oldPlayer[1]; 
            }
            else {
                if( k == 'w' || k == 'a' || k == 's' || k == 'd' ) {
                    system("clear"); // clears the terminal
                    make();
                }
            }
        }
    }
}
