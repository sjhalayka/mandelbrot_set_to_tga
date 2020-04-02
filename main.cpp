// Code by: Shawn Halayka -- sjhalayka@gmail.com
// Code is in the public domain


#include "main.h"


int main(int argc, char **argv)
{
    const size_t res = 3000;

    const float x_grid_max = 1.5;
    const float x_grid_min = -2.5;
    const size_t x_res = res;
    const complex<float> x_step_size((x_grid_max - x_grid_min) / (x_res - 1), 0);

    const float y_grid_max = 2;
    const float y_grid_min = -2;
    const size_t y_res = res;
    const complex<float> y_step_size(0, (y_grid_max - y_grid_min) / (y_res - 1));

    const unsigned short int max_iterations = 32;
    const float threshold = 2.0f;

    float_grayscale luma;
    luma.px = x_res;
    luma.py = y_res;
    luma.pixel_data.resize(static_cast<size_t>(luma.px)* static_cast<size_t>(luma.py));

    // Too small
    if (luma.px < 3 || luma.py < 3)
    {
        cout << "Template must be at least 3x3 pixels in size." << endl;
        return 2;
    }

    // Not square
    if (luma.px != luma.py)
    {
        cout << "Template must be square." << endl;
        return 3;
    }
    
    // Calculate Mandelbrot set
    complex<float> pos(x_grid_min, y_grid_min);

    for (size_t x = 0; x < x_res; x++, pos += x_step_size)
    {
        pos = complex<float>(pos.real(), y_grid_min);

        for (size_t y = 0; y < y_res; y++, pos += y_step_size)
        {
            float magnitude = iterate_2d(pos, max_iterations, threshold);

            // Truncate
            if (magnitude > threshold)
                magnitude = threshold;

            // Normalize
            magnitude /= threshold;

            // Invert
            magnitude = 1 - magnitude;

            luma.pixel_data[y * x_res + x] = magnitude;
        }
    }

	write_float_grayscale_to_tga("out.tga", luma);

	return 0;
}

