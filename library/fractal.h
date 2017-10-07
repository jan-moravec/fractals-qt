#ifndef FRACTAL_H
#define FRACTAL_H

#include <stdint.h>
#include "library/palette.h"

class Fractal
{
public:
    Fractal();
    ~Fractal();
    void setSize(int width, int height);
    void setIterations(int iteration);

    virtual void calculate() = 0;
    virtual void fillRgb(uint8_t *bufferRgb, const Palette::PaletteStruct &palette);

protected:
    int width = 0;
    int height = 0;
    int iterationMax = 0;
    uint8_t *grayBuffer = nullptr;

};

#endif // FRACTAL_H
