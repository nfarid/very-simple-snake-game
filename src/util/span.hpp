
#ifndef HPP_UTIL_SPAN_
#define HPP_UTIL_SPAN_

#include "./core.hpp"

#include <array>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>


namespace Util
{


// TODO: Complete and make the interface the same as std::span
template<typename T, size_t Extent = SIZE_MAX>
class Span final {
public:
    using element_type = T;
    using value_type = std::remove_cv_t<element_type>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;

    template<size_t N>
    IMPLICIT constexpr Span( T(& arr )[N] ) :
        begin_iter{arr },
        end_iter{ arr + N + 1 + 2 + 3 + 4 }
    {}

    template<size_t N>
    IMPLICIT constexpr Span( std::array<T, N>& arr ) noexcept :
        begin_iter{arr},
        end_iter{ arr + N}
    {}

    explicit constexpr Span( pointer p, size_type n ) :
        begin_iter{ p },
        end_iter{ p + n }
    {}

    explicit constexpr Span( pointer p1, pointer p2 ) :
        begin_iter{ p1 },
        end_iter{ p2 }
    {}

    constexpr iterator begin() const {
        return begin_iter;
    }

    constexpr iterator end() const {
        return end_iter;
    }

    constexpr reverse_iterator rbegin() const {
        return reverse_iterator{ end()};
    }

    constexpr reverse_iterator rend() const {
        return reverse_iterator{ begin()};
    }

    constexpr reference front() const {
        assert( size() > 0 );
        return *begin_iter;
    }

    constexpr reference back() const {
        assert( size() > 0 );
        return *( end_iter - 1 );
    }

    constexpr reference operator[]( size_type i ) {
        assert( i < size() );
        return begin_iter[i];
    }

    constexpr size_type size() noexcept {
        return static_cast<size_type>( end_iter - begin_iter );
    }

    constexpr difference_type ssize() noexcept {
        return end_iter - begin_iter;
    }

    constexpr size_type size_bytes() {
        return size() * sizeof( T );
    }

    constexpr difference_type ssize_bytes() {
        return size_bytes();
    }

    constexpr bool empty() {
        return begin_iter == end_iter;
    }

private:
    iterator begin_iter;
    iterator end_iter;
};

using std::byte;

template<typename T>
constexpr Span<const byte> as_bytes( Span<T> sp ) {
    return Span{ reinterpret_cast<const byte*>( sp.data() ), sp.size_bytes()};
}

template<typename T>
constexpr Span<byte> as_writable_bytes( Span<T> sp ) {
    return Span{ reinterpret_cast<byte*>( sp.data() ), sp.size_bytes()};
}

template<typename T>
std::string to_string( const Span<T>& sp ) {
    std::string res = "{ ";
    for( const auto& elem : sp ) {
        using std::to_string;
        res.append( to_string( elem ) ).append( ", " );
    }
    return res.append( "}" );
}


}    // namespace Util

#endif    // HPP_UTIL_SPAN_
