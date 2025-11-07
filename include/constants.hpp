#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
    constexpr int fps = 60;
    constexpr int tileSizeBits = 32;
    constexpr int xTiles = 30;
    constexpr int yTiles = 20;
    constexpr int xPixels = xTiles * tileSizeBits;
    constexpr int yPixels = yTiles * tileSizeBits;
} 

#endif
