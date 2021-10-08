
#ifndef MATHS_SPEED_HPP_10
#define MATHS_SPEED_HPP_10

#include "../core_engine/clock.hpp"
#include "helper.hpp"

namespace Maths
{

//For more strongly typed speed measurements
//Currently it's only measures in pixels per seconds
//Uses float seconds as its time unit
struct Speed
{
public:
    constexpr explicit Speed(float amount_) : amount{amount_} {}
    Speed() : amount{0} {}

    constexpr inline Speed operator+(Speed rhs) const {
        return Speed{amount + rhs.amount};
    }

    constexpr inline Speed& operator+=(Speed rhs) {
        *this = *this + rhs;
        return *this;
    }

    constexpr inline Speed operator-(Speed rhs) const {
        return Speed{amount - rhs.amount};
    }

    constexpr inline Speed& operator-=(Speed rhs) {
        *this = *this - rhs;
        return *this;
    }

    constexpr inline float operator*(Core::fSeconds time) const {
        return amount * time.count();
    }

    constexpr inline float operator*(Core::microseconds time) const {
        return amount * Core::fSeconds{time}.count();
    }

    constexpr inline Speed operator*(float scalar) const {
        return Speed{amount * scalar};
    }

    constexpr inline Speed& operator*=(float scalar) {
        *this = *this * scalar;
        return *this;
    }

    constexpr inline Speed operator/(float scalar) const {
        return Speed{amount / scalar};
    }

    constexpr inline Speed& operator/=(float scalar) {
        *this = *this / scalar;
        return *this;
    }

    constexpr inline Speed operator-() const {
        return Speed{-amount};
    }

    constexpr inline float count() const {
        return amount;
    }

    constexpr inline bool operator<(Speed rhs) {
        return amount < rhs.amount;
    }

    constexpr inline bool operator>(Speed rhs) {
        return rhs < *this;
    }

    constexpr inline bool operator==(Speed rhs) {
        return nearlyEqual(amount,rhs.amount);
    }

    constexpr inline bool operator!=(Speed rhs) {
        return !( *this == rhs);
    }

    constexpr inline bool operator<=(Speed rhs) {
        return (*this < rhs) || (*this == rhs);
    }

    constexpr inline bool operator>=(Speed rhs) {
        return (*this > rhs) || (*this == rhs);
    }

private:
    float amount;
};

typedef sf::Vector2<Speed> Velocity;

inline sf::Vector2f count(Velocity vel) {
    return {vel.x.count(), vel.y.count() };
}

inline Velocity toVelocity(sf::Vector2f vec) {
    return { Speed{vec.x}, Speed{vec.y} };
}


inline Speed pythagoras(Velocity vel) {
    return Speed{std::sqrt(vel.x.count()*vel.x.count() + vel.y.count()*vel.y.count() )};
}

constexpr inline Speed abs(Speed s) {
    return s < Speed{0.f} ? -s : s;
}

constexpr inline int dir(Speed s) {
    if( s == Speed{0.f} )
        return 0;
    return s.count() / std::abs(s.count() );
}

constexpr inline bool nearlyEqual(Speed lhs, Speed rhs) {
    return nearlyEqual(lhs.count(), rhs.count() );
}

} //end of namespace Maths


//Operators for Speed and Time
constexpr inline Maths::Speed operator/(float d, Core::fSeconds t) {
    return Maths::Speed{d / t.count() };
}

constexpr inline Maths::Speed operator*(float scalar,Maths::Speed speed) {
    return speed*scalar;
}

constexpr inline float operator*(Core::fSeconds t, Maths::Speed s) {
    return s*t;
}

constexpr inline float operator*(Core::microseconds t, Maths::Speed s) {
    return s*t;
}

inline sf::Vector2f operator*(Maths::Velocity lhs, Core::fSeconds rhs) {
    return {rhs*lhs.x, rhs*lhs.y};
}

inline sf::Vector2f operator*(Core::fSeconds lhs, Maths::Velocity rhs) {
    return rhs*lhs;
}


//pixels per seconds
constexpr Maths::Speed operator ""_pps (long double amount) {
    return Maths::Speed(amount);
}

constexpr Maths::Speed operator ""_pps (unsigned long long int amount) {
    return Maths::Speed(amount);
}

#endif // MATHS_SPEED_HPP_10
