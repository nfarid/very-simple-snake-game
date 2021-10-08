
#ifndef HPP_UTIL_READER_
#define HPP_UTIL_READER_

#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <type_traits>

namespace Util
{
/*
 * This function reads the input
 *
 * Throws std::ios_base::failure if it reaches EOF
 *
 * prompt is the output prompt before the input
 * out is the out-param to be used if T isn't default constructible
 * in is the input stream to read form
 *
 * E.g. const auto x = read<int>("input a number");
 * E.g. const auto bar = read("input something", Foo{1.2});
 */
template<typename T = std::string>
[[nodiscard]] T read( std::string_view prompt = {}, T&& out = {}, std::istream& in = std::cin ) {
    while( true ) {
        // Try to read the input
        std::cout << prompt << " ";
        if( in >> out )
            return static_cast<T&&>( out );

        // EOF reached, or the user hit ctrl-d
        if( in.eof() ) {
            throw std::ios_base::failure{ "Util::read: EOF reached" };
        }

        // If input is incorrect, clear error code and ignore rest of line
        in.clear();
        in.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        std::cout << "Incorrect input, please try again\n";
    }
}

template<typename T = std::string>
[[nodiscard]] T read( std::string_view prompt = {}, const T& out = {}, std::istream& in = std::cin ) = delete;

/*
 * Reader is a just a more consise way of using the above read function
 * Throws std::ios_base::failure if it reaches EOF
 * Can only be used for default constructible types
 * E.g. const int x = Reader{"Input a number"}
 */
struct [[nodiscard]] Reader {
    template<typename T>
    constexpr operator T() {
        static_assert( std::is_default_constructible_v<T>, "T must be default constructible" );
        return read<T>( prompt );
    }
    std::string_view prompt = "";
};

}    // namespace Util

#endif    // HPP_UTIL_READER_
