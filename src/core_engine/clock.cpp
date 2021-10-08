
#include <cmath>
#include "clock.hpp"

namespace Core {
microseconds Time::getElapsedTime() {
    return std::chrono::duration_cast<microseconds>(std::chrono::high_resolution_clock::now() - beginTimePointM) - stoppedDurationM;
}

void Time::stop() {
    startOfStoppedTimeM = std::chrono::high_resolution_clock::now();
}

void Time::resume() {
    stoppedDurationM += std::chrono::duration_cast<microseconds>(std::chrono::high_resolution_clock::now() - startOfStoppedTimeM);
}

Time::Time() :
    beginTimePointM{std::chrono::high_resolution_clock::now()} {
}

fSeconds fmod(fSeconds num, fSeconds den) {
    return fSeconds{std::fmod(num.count(), den.count() )};
}

}
