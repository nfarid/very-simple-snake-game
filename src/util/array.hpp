
#ifndef HPP_UTIL_ARRAY_

#define HPP_UTIL_ARRAY_

#include "./core.hpp"

#include <array>
#include <type_traits>
#include <utility>


// Some utility functions for 1D and 2D arrays
namespace Util
{


template<typename T, size_t H, size_t W>
using Matrix = std::array<std::array<T, W>, H>;

// Some functions to get the dimension of a matrix
template<typename T, size_t H, size_t W>
[[nodiscard]]
constexpr auto width( const Matrix<T, H, W>& ) noexcept -> typename Matrix<T, H, W>::size_type {
    return W;
}

template<typename T, size_t H, size_t W>
[[nodiscard]]
constexpr auto height( const Matrix<T, H, W>& ) noexcept -> typename Matrix<T, H, W>::size_type {
    return H;
}

template<typename T, ptrdiff_t H, ptrdiff_t W>
[[nodiscard]] constexpr
auto swidth(const Matrix<T, H, W>&)noexcept-> typename Matrix<T, H, W>::difference_type {
    return W;
}

template<typename T, ptrdiff_t H, ptrdiff_t W>
[[nodiscard]]
constexpr auto sheight(const Matrix<T, H, W>&)noexcept-> typename Matrix<T, H, W>::difference_type {
    return H;
}

template<typename T, size_t H, size_t W>
[[nodiscard]]
constexpr auto size2D( const Matrix<T, H, W>& )noexcept ->typename Matrix<T, H, W>::size_type {
    return H * W;
}

template<typename T, ptrdiff_t H, ptrdiff_t W>
[[nodiscard]] constexpr auto size2D( const Matrix<T, H, W>& ) noexcept ->
typename Matrix<T, H, W>::difference_type {
    return H * W;
}

template<typename T, size_t H, size_t W>
[[nodiscard]]
constexpr std::pair<size_t, size_t> dim( const Matrix<T, H, W>& ) noexcept {
    return{ H, W};
}

template<typename T, ptrdiff_t H, ptrdiff_t W>
[[nodiscard]]
constexpr std::pair<ptrdiff_t, ptrdiff_t> sdim( const Matrix<T, H, W>& ) noexcept {
    return{ H, W};
}

// to_array creates an array without needing size specification (but allows type specification)
// E.g. const auto arr = to_array<int16_t>({2,3,5,7});
// Since C++17 doesn't have to_array yet, let's use cppreference's implementation
#if __cplusplus < 202002L


namespace detail
{


template<class T, size_t N, size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array_impl( T ( & a )[N],
        std::index_sequence<I...> ) {
    return{ { a[I] ...} };
}

template<class T, size_t N, size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array_impl( T( &&a )[N],
        std::index_sequence<I...> ) {
    return{ { std::move( a[I] )...} };
}


}    // namespace detail


template<class T, size_t N>
[[nodiscard]] constexpr std::array<std::remove_cv_t<T>, N> to_array( T ( & a )[N] ) noexcept {
    return detail::to_array_impl( a, std::make_index_sequence<N>{} );
}

template<class T, size_t N>
[[nodiscard]] constexpr std::array<std::remove_cv_t<T>, N> to_array( T( &&a )[N] ) noexcept {
    return detail::to_array_impl( std::move( a ), std::make_index_sequence<N>{} );
}

#else
using std::to_array;
#endif    // __cplusplus < 202002L


}    // namespace Util


// May be confusing since these returns the height, use size2D instead
template<typename T, size_t H, size_t W> size_t size( const Util::Matrix<T, H, W>& ) = delete;
template<typename T, ptrdiff_t H, ptrdiff_t W>
ptrdiff_t ssize(const Util::Matrix<T, H, W>&) = delete;

#endif    // HPP_UTIL_ARRAY_
