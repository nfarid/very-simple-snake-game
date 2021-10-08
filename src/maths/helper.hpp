
#ifndef MATHS_HELPER_HPP_42
#define MATHS_HELPER_HPP_42

#include <SFML/System.hpp>
#include <cmath>
#include <limits>

namespace Maths
{
const float pi = 4*std::atan(1);

constexpr float epsilon = std::numeric_limits<float>::epsilon();
constexpr float maxFloat = std::numeric_limits<float>::max();
constexpr float minFloat = std::numeric_limits<float>::min();

constexpr bool nearlyEqual(float a, float b) {
		const float absA = std::abs(a);
		const float absB = std::abs(b);
		const float diff = std::abs(a - b);

		if( a == b ) // shortcut, handles infinities
			return true;
        else if (a == 0.0f || b == 0.0f || (absA + absB < minFloat) )
			// a or b is zero or both are extremely close to it
			// relative error is less meaningful here
			return diff < (epsilon * minFloat);
		else // use relative error
			return diff / std::min( (absA + absB), maxFloat) < epsilon;

}

template <typename T>
inline bool nearlyEqual(sf::Vector2<T> lhs, sf::Vector2<T> rhs) {
    return nearlyEqual(lhs.x,rhs.x) && nearlyEqual(lhs.y,rhs.y);
}

template <typename T, typename U>
inline auto dot( sf::Vector2<T> lhs, sf::Vector2<U> rhs ) {
    return (lhs.x*rhs.x) + (lhs.y*rhs.y);
}

constexpr inline float pythagoras(float x, float y) {
    return std::sqrt( x*x + y*y );
}

inline float pythagoras(sf::Vector2f vec) {
    return pythagoras(vec.x,vec.y);
}

//return in radians
inline float angleBetween(sf::Vector2f source, sf::Vector2f dest) {
    return std::atan2( dest.y-source.y, dest.x-source.x);
}

inline sf::Vector2f unitVector( float angle ) {
	return { std::cos(angle), std::sin(angle) };
}

template <typename T>
inline sf::Vector2<T> unitVector( sf::Vector2<T> vec) {
	return  vec/pythagoras(vec);
}

const inline float toRadian(float degree) {
    return pi*(degree/180.0f);
}

const inline float toDegree(float rad) {
	return 180.0f*(rad/pi);
}
} //end of namespace Maths

#endif // MATHS_HELPER_HPP_42
