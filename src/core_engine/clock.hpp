
#ifndef TIME_CLOCK_HPP_39
#define TIME_CLOCK_HPP_39

#include <SFML/System.hpp>
#include <chrono>
#include "../the_includes.hpp"
#include "../core_engine/no_copy_move.hpp"

namespace Core {

typedef std::chrono::duration<float> fSeconds;
typedef std::chrono::microseconds microseconds;

//ideal frame time is 15,625 microseconds
constexpr microseconds idealFrameTime{1000000/static_cast<int>(idealFPS)};

class Time : NoCopy, NoMove {
public:
    microseconds getElapsedTime();
    void stop();
    void resume();
    Time();
private:
    std::chrono::high_resolution_clock::time_point beginTimePointM{};
    std::chrono::high_resolution_clock::time_point startOfStoppedTimeM{};
    microseconds stoppedDurationM{};
};

inline unsigned long long seedNumber() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

fSeconds fmod(fSeconds num, fSeconds den);

inline bool atTimeInterval( fSeconds currentTime, fSeconds interval ) {
    return fmod(currentTime, interval) >= fmod(currentTime+idealFrameTime, interval);
}

} //end of namespace Core

constexpr Core::fSeconds operator ""_fs(long double x) {
    return Core::fSeconds(x);
}

constexpr Core::microseconds operator ""_us(unsigned long long int x) {
    return Core::microseconds(x);
}

#endif // TIME_CLOCK_HPP_39
