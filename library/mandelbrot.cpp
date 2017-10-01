#include "mandelbrot.h"
#include <complex>
#include <iostream>
Mandelbrot::Mandelbrot() : Fractal()
{

}

void Mandelbrot::calculate()
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double c_re = (x - width/2.0) * 4.0/width;
            double c_im = (y - height/2.0) * 4.0/width;
            std::complex<double> c = {c_re, c_im};
            std::complex<double> z = 0;
            /*double x = 0, y = 0;
            */
            int iteration = 0;

            while (std::abs (z) <= 2 && iteration < 100) {
                z = z*z + c;
                iteration++;
            }


            if (iteration < 100) {
                // OK
                grayBuffer[width*y + x] = 255;
            } else {
                // NOT
                grayBuffer[width*y + x] = 0;
            }
        }
    }
}
