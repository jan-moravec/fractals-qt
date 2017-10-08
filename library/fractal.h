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

    struct Zoom {
        int x = 0;
        int y = 0;
        double scale = 1.0;
    };
    void setZoom(int x, int y, double scale);
    void addZoom(int x, int y, double scale);
    Zoom getZoom();

    virtual void calculate() = 0;
    virtual void fillRgb(uint8_t *bufferRgb, const Palette::PaletteStruct &palette);

protected:
    int width = 0;
    int height = 0;
    int iterationMax = 0;
    uint8_t *grayBuffer = nullptr;
    Zoom zoom;
};

#endif // FRACTAL_H
