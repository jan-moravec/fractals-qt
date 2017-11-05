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
        double x = 0; // Resolution coordinate
        double y = 0;
        double xRel = 0; // Relative coordinate [0-1]
        double yRel = 0;
        double scale = 1.0;
    };
    void setZoom(double x, double y, double scale);
    void zoomIn(int x, int y, double scale);
    void zoomOut(void);
    Zoom getZoom(void) const;
    double getProgressPercent(void) const;

    virtual void calculate() = 0;
    virtual void fillRgb(uint8_t *bufferRgb, const Palette::PaletteStruct &palette);

protected:
    int width = 0;
    int height = 0;
    int iterationMax = 0;
    uint8_t *grayBuffer = nullptr;
    Zoom zoom;
    std::vector<Zoom> zoomHistory;
    double progress = 0;
    void updateProgress(double progressPercent);
};

#endif // FRACTAL_H
