#include "fractal.h"
#include <algorithm>

Fractal::Fractal()
{

}

Fractal::~Fractal()
{
    delete[] grayBuffer;
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

void Fractal::fillRgb(uint8_t *bufferRgb, const Palette::PaletteStruct &palette)
{
    for (int i = 0; i < width*height; ++i) {
        uint8_t gray = grayBuffer[i];
        bufferRgb[3*i + 0] = palette.palette[gray][0];
        bufferRgb[3*i + 1] = palette.palette[gray][1];
        bufferRgb[3*i + 2] = palette.palette[gray][2];
    }
}

