# Gamne
This is a gamne that I created in like a week

Also it's pronounced /geɪmʷə/ or /geɪmwə/ (geymwuh) because I kinda associate "mn" with /ŋ͡m/, which for me kinda sounds like /mw/

It has a [discord server](https://discord.com/invite/qNH8GHk9EU), where you can discuss modding and suggestions for the gamne

Some of the gamne's "terminology" was inspired by [HyperRogue](https://github.com/zenorogue/hyperrogue), probably because I made a mod for the game.

Released under [GNU General Public License version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html), and thus does not come with any warranty.

## Gameplay
Currently, there is no gameplay. You can currently only walk around in 10 procedurally-generated biomes.

# Compiling
If you're on Linux, you can run this:
```
git clone https://github.com/MinersHavenM43/gamne.git gamne
cd gamne
make
./gamne
```
It is the same on Windows, however if you are compiling with MinGW you'll need some libraries, which you can simply copy over from the MingW folder.

The Windows version also has some tree generation errors for some reason, and does not clear the terminal because in Windows the clear command is "clc"

# Modding
Modding the gamne isn't very hard. You don't even need much programming experience to mod it (though the more, the better). In fact, it could teach you some C++!
## Creating new biomes
Content are defined in `biomegen.cpp`, and to create a new biome you have to put `BIOME(glyph, name, variable name, id)` in the top of the file.

Then, you have to define where it spawns. Gamne does this using the heat and temperature of the location at line 57, In the function `Biome biome(pyr x, pyr y)`.

## Creating new walls
Creating walls is very similar to creating biomes: you have to define the walls (but with `WALL(glyph, name, variable name, pass index, id)`), with the additional parameter of the pass index.

## Creating a new data type
To create a new datatype (for this example, and item), you have to go to `gamne.h` at line 65, and define a new `struct`, with your datatype and its parameters. For an item, you could have:
```cpp
struct Item {
    int id;
    std::string glyph, name;
};
```
Then go to the top of `biomegen.cpp`, and you could put something like:
```cpp
#define ITEM(glyph, name, varname, id) content::Item varname = {id, glyph, name};
```
You then have to put the function to determine where to generate items. After the `Wall wall(pyr x, pyr y)` function, you can put:
```cpp
Item item(pyr x, pyr y) {
    #define GRAND(k) game::grand(x, y, k, Seed) // random number generator
    int cbiome = biome(x, y).id; // biome id
    switch(cbiome) {
        case 0: // plains
            if(GRAND(200) < 1) { // 1/200 chance
                return itItem; // generate itItem
            }
        break;
        case 1: // forest
            if(GRAND(555) < 2) {
                return itItem2; // generate itItem2
            }
        break;
        // ...
    }
    return "";
}
```
The items will, however, not render.

To fix that, go to `game.cpp` in the function `getChar(pyr x, pyr y)`, and add a case for items. SOmething like this would work:
```cpp
string getChar(pyr x, pyr y) {
    if(x == player[0] && y == player[1]) return "@";
    if(content::wall(x,y).glyph != "") return content::wall(x,y).glyph;
    if(content::item(x,y).glyph != "") return content::item(x,y).glyph;
    return content::biome(x,y).glyph;
}
```
Still have more questions? Join the [discord server](https://discord.com/invite/qNH8GHk9EU), in the #modding channel.
