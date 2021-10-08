
#ifndef HPP_UTIL_CORE_
#define HPP_UTIL_CORE_

#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>


/*For some core utilities (without making the header file too large), including:
 *
 * byte literal _B;  size_t literal _ZU;  ptrdiff_t literal _Z
 * Finally class for a scope guard
 * unreachable macro to indicate unreachable path
 * internal macro to indicate internal linkage
 * implicit macro to indicate implicit conversion
 * DumbPtr to indicate ownership, if smart pointers cannot be used
 *
 */

namespace Util
{


/*
 * A scope guard to make sure a function is called at the end of scope
 * E.g: Finally f = []{cleanup();};
 */
template<typename F>

class Finally {
public:
    /*[[implicit]]*/
    Finally( F&& lambda ) noexcept :
        func{ static_cast<F&&>( lambda ) }, valid{ true } {}

    // No move or copy
    Finally& operator=( Finally&& ) = delete;

    // func will be called once by the end of Finally's scope
    ~Finally() noexcept {
        if( valid )
            func();
    }

    // func can be called early
    void operator()() noexcept {
        if( valid ) {
            func();
            valid = false;
        }
    }

private:
    F func;
    bool valid;
};


// To indicate owning pointers and when smart pointers can't be used
template<typename T>
using DumbPtr = T*;


// std::byte should have had a literal
// E.g. x & 0xFF_B
[[nodiscard]] constexpr std::byte operator"" _B( unsigned long long int x ) noexcept {
    assert( x <= UINT8_MAX );
    return std::byte( x );
}

[[nodiscard]] constexpr std::ptrdiff_t operator"" _Z( unsigned long long int x ) noexcept {
    assert( x <= PTRDIFF_MAX );
    return static_cast<std::ptrdiff_t>( x );
}

[[nodiscard]] constexpr std::size_t operator"" _UZ( unsigned long long int x ) noexcept {
    assert( x <= SIZE_MAX );
    return x;
}

/*
 * To indicate that a code path should never be reached
 *
 * Used to silence false positive warnings in a fully handled enum switch
 *
 * although don't use default in that case, rather it should be after the switch statement
 * This is to prevent useful warnings (e.g. -Wswitch) from being silenced
 *
 * -Wcovered-switch-default is a good warning to have (only clang has it)
 * -Wswitch-enum is very bad (just use -Wswitch)
 *
 */
#if defined( __GNUG__ )
#define UNREACHABLE() \
    do{ \
        assert( not "reachable" ); \
        __builtin_unreachable();  \
    }while(0)
#elif defined( _MSC_VER )
#define UNREACHABLE() \
    do{ \
        assert( not "reachable" ); \
        __assume( 0 ); \
    }while( 0 )
#else
#define UNREACHABLE() \
    do{ \
        assert( not "reachable" ); \
    }while( 0 )
#endif    // if defined( __GNUG__ )


// To indicate internal linkage
// As static has too many unrelated meanings
#define INTERNAL static


// To explicitly state a constructor or conversion is implicit
// Since there's no [[implicit]] attribute
#define IMPLICIT    /*[[implicit]]*/


}// namespace Util


static_assert(CHAR_BIT == 8, "A byte is typically the same as an octet");

// These are already in the global namespace anyway, and should be
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::int_fast16_t;
using std::int_fast32_t;
using std::int_fast64_t;
using std::int_fast8_t;

using std::int_least16_t;
using std::int_least32_t;
using std::int_least64_t;
using std::int_least8_t;

using std::intmax_t;
using std::intptr_t;

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::uint_fast16_t;
using std::uint_fast32_t;
using std::uint_fast64_t;
using std::uint_fast8_t;

using std::uint_least16_t;
using std::uint_least32_t;
using std::uint_least64_t;
using std::uint_least8_t;

using std::uintmax_t;
using std::uintptr_t;

#endif    // HPP_UTIL_CORE_
