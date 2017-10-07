#ifndef PALETTE_H
#define PALETTE_H

#include <vector>
#include <string>

class Palette
{
public:
    Palette();
    struct PaletteStruct {
        uint8_t palette[256][3];
        std::string name;
    };

    int getCount(void) { return palettes.size(); }
    void setCurrent(int i);
    const PaletteStruct &getPalette(int i);
    const PaletteStruct &getCurrent(void) { return palettes.at(current); }

private:
    std::vector<PaletteStruct> palettes;
    int current = 0;

    void loadPalettes(void);
    void generatePalettes(void);
};

#endif // PALETTE_H
