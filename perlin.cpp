// Modified from Wikipedia (https://en.wikipedia.org/wiki/Perlin_noise)
// CC-BY-SA is kind of similar to GPL, so I believe I can use it here?

#include "h.h"

namespace Perlin {
    float interpolate(float x0, float x1, float w) {
        return x0 + (x1-x0) * (3-2*w) * w * w; // 4x-4x² integral
    }

    struct vec {
        float x, y;
    };

    vec randomGradient(int x, int y, int seed = Seed) {
        #define THING(s) (2 * (int)s + (s - (int)s)) // this doubles the number before the '.', but keeps the decimal. for example: 2.7 -> 4.7, 14.2 -> 28.2, 5.123 -> 10.123, and so on.
        #define SIN(s) sinf(s * x + THING(s + seed) * y)
        #define COS(s) cosf((s + seed) * y + THING(s) * x)

        float r = SIN(1.5) + COS(2.7) + SIN(6.6) + COS(9.7) + SIN(28.3) + COS(51.9);
        return {sinf(r), cosf(r)};
    }

    float dotGridGradient(int ix, int iy, float x, float y, int seed = Seed) {
        vec gradient = randomGradient(ix, iy, seed);

        float dx = x - ix;
        float dy = y - iy;

        return (dx*gradient.x + dy*gradient.y);
    }

    double Perlin(double x, double y, int seed) {
        x += 40000; y += 100000; // shifts the perlin noise map diagonally because the perlin noise in the center looks awful
        int x0 = (int)x;
        int x1 = x0 + 1;
        int y0 = (int)y;
        int y1 = y0 + 1;

        float sx = x - x0;
        float sy = y - y0;

        float n0, n1, ix0, ix1, value;

        n0 = dotGridGradient(x0, y0, x, y, seed);
        n1 = dotGridGradient(x1, y0, x, y, seed);
        ix0 = interpolate(n0, n1, sx);

        n0 = dotGridGradient(x0, y1, x, y, seed);
        n1 = dotGridGradient(x1, y1, x, y, seed);
        ix1 = interpolate(n0, n1, sx);

        value = interpolate(ix0, ix1, sy);
        return (double)value + .5;
    }

    double PerlinOc(double x, double y, int oc, double sc, int seed, double ocs /*= 4*/) {
        double p = 0;
        double ocsh = ocs/2;

        double oct_scale = 1;
        double oct_mult = 1;
        for(int i = 0; i < oc; i++) {
            p += (Perlin( x * oct_scale / sc, y * oct_scale / sc, seed ) - .5) * oct_mult;
            oct_scale /= ocs;
            oct_mult /= ocsh;
        }
        return p + .5;
    }

    double HeightMap(double x, double y) {
        #define h 50. // used for large scale terrain debugging
        return PerlinOc(x, y, 4, h, Seed);
        #undef h
    }
    double TempMap(double x, double y) {
        #define h 128.
        return Perlin(x/h, y/h, Seed * 2);
        #undef h
    }
}