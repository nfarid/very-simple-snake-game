
#ifndef HPP_UTIL_ENUM_
#define HPP_UTIL_ENUM_

#include <type_traits>


// Some basic enum utilities
// TODO: A non-hacky way to get the enum count

namespace Util
{


// To convert an enum to its underlying type
template<typename Enum, typename E_ = std::enable_if_t<std::is_enum_v<Enum> > >
[[nodiscard]] constexpr auto unbox( Enum e ) noexcept {
    return static_cast<typename std::underlying_type<Enum>::type>( e );
}

// To convert an enum to its underlying type
template<typename Enum, typename E_ = std::enable_if_t<std::is_enum_v<Enum> > >
[[nodiscard]] constexpr auto operator+( Enum e ) noexcept {
    return unbox( e );
}


}    // namespace Util

#endif    // HPP_UTIL_ENUM_
