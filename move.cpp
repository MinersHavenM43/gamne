// Deals with character movement
#include "h.h"
using namespace std;

namespace game {
    bool passable(int x,int y) {
        if(content::wall(x,y,TYPE::pass) == "1") return 0;
        return 1;
    }
    void noPassM(string s) {
        cout << "You cannot move through the " << s << "!" << endl;
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
            }
            if(!passable(player[0], player[1])) {
                noPassM(content::wall(player[0],player[1],TYPE::name));
                player[0] = oldPlayer[0]; player[1] = oldPlayer[1];
            }
            else {
                system("clear"); // clears the terminal
                make();
            }
        }
    }
}