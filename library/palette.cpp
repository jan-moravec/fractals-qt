#include "palette.h"
#include <iostream>
#include <fstream>
#include <dirent.h>

Palette::Palette()
{
    generatePalettes();
    loadPalettes();
}

void Palette::loadPalettes(void)
{
    DIR *dir;
    struct dirent *ent;

    dir = opendir("palette");
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string paletteName(ent->d_name);
            std::size_t ind = paletteName.find(".plt");
            if (ind != std::string::npos) {
                // Load palette
                std::ifstream inFile("palette/" + paletteName);
                if (inFile.is_open()) {
                    palettes.push_back(PaletteStruct());
                    int line = 0;
                    int pal[3];
                    while (inFile && line < 256) {
                        inFile >> pal[0] >> pal[1] >> pal[2];
                        palettes.back().palette[line][0] = pal[0];
                        palettes.back().palette[line][1] = pal[1];
                        palettes.back().palette[line][2] = pal[2];
                        line++;
                    }
                    inFile.close();
                    palettes.back().name = paletteName.substr(0, ind);
                }
            }
        }
        closedir(dir);
    }
}

void Palette::generatePalettes(void)
{

    palettes.push_back(PaletteStruct());
    palettes.back().name = "Gray";
    for (int i = 0; i < 256; ++i) {
        palettes.back().palette[i][0] = i;
        palettes.back().palette[i][1] = i;
        palettes.back().palette[i][2] = i;
    }

    palettes.push_back(PaletteStruct());
    palettes.back().name = "Red";
    for (int i = 0; i < 256; ++i) {
        palettes.back().palette[i][0] = i;
        palettes.back().palette[i][1] = 0;
        palettes.back().palette[i][2] = 0;
    }

    palettes.push_back(PaletteStruct());
    palettes.back().name = "Green";
    for (int i = 0; i < 256; ++i) {
        palettes.back().palette[i][0] = 0;
        palettes.back().palette[i][1] = i;
        palettes.back().palette[i][2] = 0;
    }

    palettes.push_back(PaletteStruct());
    palettes.back().name = "Blue";
    for (int i = 0; i < 256; ++i) {
        palettes.back().palette[i][0] = 0;
        palettes.back().palette[i][1] = 0;
        palettes.back().palette[i][2] = i;
    }
}

void Palette::setCurrent(int i)
{
    if (i < 0) {
        i = 0;
    } else if (i >= palettes.size()) {
        i = palettes.size() - 1;
    }

    current = i;
}
const Palette::PaletteStruct &Palette::getPalette(int i)
{
    if (i < 0) {
        i = 0;
    } else if (i >= palettes.size()) {
        i = palettes.size() - 1;
    }

    return palettes.at(i);
}
