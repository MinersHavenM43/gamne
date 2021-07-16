// main file
// Copyright (C) 2021 MinersHavenM43, see 'h.h' for details
#include "h.h"
using namespace std;

// int a = 2; test variable
int main() {
    std::cout <<
    "Gamne v1.1 by MinersHaven\n"
    "Released under GNU GPL version 2, and thus does not come with any warranty. See COPYING for details"
    << endl;
    std::cout << "Press 'y' to start. Press 'H' for a list of commands" << endl;
    game::move();
    return 0;
}
