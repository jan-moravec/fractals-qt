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

void Fractal::setZoom(double x, double y, double scale)
{
    zoom.x = x;
    zoom.y = y;
    zoom.scale = scale;
}

void Fractal::zoomIn(int x, int y, double scale)
{
    zoomHistory.push_back(zoom);

    zoom.x += x / zoom.scale;
    zoom.y += y / zoom.scale;
    zoom.scale *= scale;
}

void Fractal::zoomOut(void)
{
    if (zoomHistory.size() == 0) {
        return;
    }

    Zoom z = zoomHistory.back();
    zoomHistory.pop_back();

    zoom.x = z.x;
    zoom.y = z.y;
    zoom.scale = z.scale;
}

Fractal::Zoom Fractal::getZoom(void) const
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

void Fractal::updateProgress(double progressPercent)
{
    progress = progressPercent;
}

double Fractal::getProgressPercent(void) const
{
    return progress;
}

