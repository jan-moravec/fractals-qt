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

void Fractal::setZoom(int x, int y, double scale)
{
    /*if (x < 0) {
        x = 0;
    } else if (x > width) {
        x = width;
    }

    if (y < 0) {
        y = 0;
    } else if (y > height) {
        y = height;
    }*/

    if (scale < 1.0) {
        scale = 1.0;
    }

    zoom.x = x;
    zoom.y = y;
    zoom.scale = scale;
}

void Fractal::addZoom(int x, int y, double scale)
{
    if (x < 0) {
        x = 0;
    } else if (x > width) {
        x = width;
    }

    if (y < 0) {
        y = 0;
    } else if (y > height) {
        y = height;
    }

    if (scale < 1.0) {
        scale = 1.0;
    }

    zoom.x += x / zoom.scale;
    zoom.y += y / zoom.scale;
    zoom.scale *= scale;
}

Fractal::Zoom Fractal::getZoom()
{
    return zoom;
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

