
#ifndef THE_INCLUDES_HPP_0
#define THE_INCLUDES_HPP_0

#ifndef NDEBUG
    #include <iostream>
#endif

constexpr struct {unsigned int x; unsigned int y;} windowSizeC{800,608};

constexpr float blockSize = 32.0f; //a block is 32 pixels
constexpr float borderThickness = 32.0f;

constexpr struct {
    float top = borderThickness;
    float right = windowSizeC.x - borderThickness;
    float bottom = windowSizeC.y - borderThickness;
    float left = borderThickness;
}gameBoundary;

constexpr struct {
    int x = (gameBoundary.right - gameBoundary.left)/blockSize;
    int y = (gameBoundary.bottom - gameBoundary.top)/blockSize;
} totalSectionN;

constexpr struct {
    float x = (gameBoundary.left + gameBoundary.right)/2.0f;
    float y = (gameBoundary.top + gameBoundary.bottom)/2.0f;
} theMiddle; //for convenience

constexpr float idealFPS = 64.0f;
constexpr unsigned int quadVertexN = 6; //number of vertices per quad

#include <cstddef>
using size_t = std::size_t; //pollution has already happened, just making sure
using ptrdiff_t = std::ptrdiff_t;

#include <cstdlib>
[[noreturn]]
inline bool exitNow() { //just wanted exit to return a bool (doesn't really return though)
    std::exit(-1);
    //return false;
}

typedef unsigned char byte;

#include <cassert>

#endif //THE_INCLUDES_HPP_0
