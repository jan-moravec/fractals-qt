#include "fractal.h"
#include <algorithm>

Fractal::Fractal()
{

}

void Fractal::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    delete[] grayBuffer;
    grayBuffer = new uint8_t[width*height]();
}

void Fractal::setIterations(int iteration)
{
    this->iterationMax = iteration;
}

void Fractal::fillRgb(uint8_t *bufferRgb)
{
    for (int i = 0; i < width*height; ++i) {
        bufferRgb[3*i + 0] = grayBuffer[i];
        bufferRgb[3*i + 1] = grayBuffer[i];
        bufferRgb[3*i + 2] = grayBuffer[i];
    }
}

