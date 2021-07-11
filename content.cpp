// defines biome locations and thing like that

#include "h.h"
using namespace std;

namespace content {
    /* int test = 3;
    int testf(int h) {
        return h + 3;
    } */
    float distance(int x, int y) {
        return sqrt(x*x + y*y);
    }
    string wallrh(string glyph, string name, int pass, int type) { // wall return help
        if(type == TYPE::glyph) return glyph;
        else if(type == TYPE::name) return name;
        else if(type == TYPE::pass) return to_string(pass);
    }
    string biome(int x, int y, int type) {
        if(sinf(x/10.) + sinf(y/10.) > 1) {
            return type ? "Mountains" : "^";
        }
        if(sinf(x/10.) + sinf(y/10.) > -0.5) {
            return type ? "Forest" : ",";
        }
        return type ? "Plains" : "."; // default
    }
    string wall(int x, int y, int type) {
        string cbiome = biome(x, y, TYPE::name);
        if(cbiome == "Forest") {
            if(game::grand(x, y, 20, seed) < 1) {
                return wallrh("+", "tree", PASSTYPE::nopass, type);
            }
        }
        if(cbiome == "Mountains") {
            if(game::grand(x, y, 20, seed) < 19) {
                return wallrh("Λ", "mountain", PASSTYPE::nopass, type);
            }
        }
        return "."; // keep this at last
    }
}