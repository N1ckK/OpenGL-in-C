#include <math.h>
#include <stdlib.h>
#include "../../HeaderFiles/defines.h"
#include "../../../../libs/complex/complex.h"

long double map(long double v, long double a, long double b, long double c,
    long double d){

    /*  Maps the value v element of (a, b) interval
    to (c, d) interval */
    return c + (d - c) * ( v / (b - a) - a / (b - a) );
}

struct Vertex* calcVerts(int width, int height){
    struct Vertex* verts = malloc(sizeof(struct Vertex) * width * height);
    int counter = 0;
    for (int i = 0 ; i < width ; ++i){
        for (int j = 0 ; j < height ; ++j){
            long double i_m = map(i, 0, width, -1, 1);
            long double j_m = map(j, 0, height, -1, 1);
            COMPLEX c = {map(i, 0, width, -3, 3), map(j, 0, height, -2, 2)};
            COMPLEX z = {0, 0};
            int k = 0;
            while (k <= 40){
                z = add(multiply(z, z), c);
                if (z.real + z.imag > 16 || z.real + z.imag < -16) break;
                k += 1;
            }
            k = ((int)((double) k / 40 * 255) % 255);
            double r = (int)(sin(k) * k + 1 * k) % 255;
            double g = (int)(1 * k) % 255;
            double b = (int)(k + cos(1) * k) % 255;

            struct Vertex v = {(double) i / (double) width * 2.0 - 1.0,
                (double) j / (double) height * 2.0 - 1.0, 0,
                r / 255.0, g / 255.0, b / 255.0, 1.0};
            verts[counter] = v;
            counter ++;
        }
    }
    return verts;
}
