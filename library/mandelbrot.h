#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "fractal.h"

class Mandelbrot : public Fractal
{
public:
    Mandelbrot();

    virtual void calculate();
};

#endif // MANDELBROT_H
