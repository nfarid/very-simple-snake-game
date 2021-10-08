
#ifndef HPP_UTIL_SIZE_
#define HPP_UTIL_SIZE_

#include "./core.hpp"

#include <cstddef>
#include <iterator>
#include <type_traits>

// Some functions to get the sizes of things at compile time
namespace Util
{
// Return the size in bytes of a type (e.g. ssizeof<int>() )
template<typename T>
[[nodiscard]] constexpr ptrdiff_t ssizeof() noexcept {
    return static_cast<ptrdiff_t>( sizeof( T ) );
}

// Return the size in bytes
template<typename T>
[[nodiscard]] constexpr ptrdiff_t ssizeof( const T& ) noexcept {
    return ssizeof<T>();
}

#if __cplusplus < 202002L
// Return the number of elements of a container
template<typename Container>
[[nodiscard]] constexpr auto ssize( const Container& con ) noexcept {
    using SSizeType = std::common_type_t<ptrdiff_t, std::make_signed_t<decltype( size( con ) )> >;
    return static_cast<SSizeType>( size( con ) );
}

// Return the number of elements of an array
template<typename T, ptrdiff_t N>
[[nodiscard]] constexpr auto ssize( const T ( & )[N] ) noexcept {
    return N;
}
#else
// Since C++20 already has ssize
using std::ssize;
#endif

// Return the total size of all the elements in bytes
template<typename Container>
[[nodiscard]] constexpr auto size_bytes( const Container& con ) noexcept {
    return size( con ) * sizeof( typename Container::value_type );
}

// Return the total size of an array in bytes
template<typename T, size_t N>
[[nodiscard]] constexpr auto size_bytes( const T ( & arr )[N] ) noexcept {
    return sizeof( arr );
}

// Return the total size of all the elements in bytes
template<typename Container>
[[nodiscard]] constexpr auto ssize_bytes( const Container& con ) noexcept {
    return Util::ssize( con ) * ssizeof<typename Container::value_type>();
}

// Return the total size of an array in bytes
template<typename T, ptrdiff_t N>
[[nodiscard]] constexpr auto ssize_bytes( const T ( & arr )[N] ) noexcept {
    return Util::ssizeof( arr );
}

}    // namespace Util

#endif    // HPP_UTIL_SIZE_
