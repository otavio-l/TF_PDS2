#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
    constexpr int fps{15};
    // in PlayState the logic is between the first 192x160 and then scaled
    constexpr int xLogicPixels{192};
    constexpr int yLogicPixels{160};
    // the window has 768x640 pixels
    constexpr int xPixels{ xLogicPixels * 4 };
    constexpr int yPixels{ yLogicPixels * 4 };

    constexpr int mainCharacterVelocity{1};
    constexpr int mainHeight{20};
    constexpr int mainWidth{7};

    // Compatibility reasons
    constexpr int tileSizePixels{32};
    constexpr int xTiles{30};
    constexpr int yTiles{20};
} 

#endif
