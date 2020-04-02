// Code by: Shawn Halayka -- sjhalayka@gmail.com
// Code is in the public domain


#ifndef MAIN_H
#define MAIN_H


#include "image.h"


#include <cmath>
#include <complex>
using namespace std;


float iterate_mandelbrot(
    const complex<float> C,
    const short unsigned int max_iterations,
    const float threshold)
{
    complex<float> Z(0, 0);

    for (short unsigned int i = 0; i < max_iterations; i++)
    {
        Z = Z * Z + C;

        if (abs(Z) >= threshold)
            break;
    }

    return abs(Z);
}


#endif