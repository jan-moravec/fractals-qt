#ifndef FRACTAL_H
#define FRACTAL_H

#include <stdint.h>

class Fractal
{
public:
    Fractal();
    void setSize(int width, int height);

    virtual void calculate() = 0;
    virtual void fillRgb(uint8_t *bufferRgb);

protected:
    int width = 0;
    int height = 0;
    uint8_t *grayBuffer = nullptr;

};

#endif // FRACTAL_H
