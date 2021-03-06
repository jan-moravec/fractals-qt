#include "mandelbrot.h"
#include <complex>
#include <iostream>
#include <QDebug>

Mandelbrot::Mandelbrot() : Fractal()
{

}

void Mandelbrot::calculate()
{
    updateProgress(0);

    double step = 255.0 / iterationMax;
    int pixelTotal = width * height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // (-2, 2)
            double c_re = (4.0*x/width / zoom.scale + 4.0*zoom.xRel*width/width - 2.0);
            double c_im = (4.0*y/width / zoom.scale + 4.0*zoom.yRel*height/width - 2.0*height/width);
            std::complex<double> c = {c_re, c_im};
            std::complex<double> z = 0;

            int iteration = 0;
            while (std::abs (z) <= 2 && iteration < iterationMax) {
                z = z*z + c;
                iteration++;
            }

            int pixel = width*y + x;
            grayBuffer[pixel] = iteration * step;

            if (pixel % (pixelTotal / 100) == 0) {
                updateProgress(100 * pixel / pixelTotal);
            }
        }
    }

    updateProgress(100);
}
