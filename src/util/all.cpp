
#include "./all.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <windows.h>
#elif defined(__unix__) || defined(linux)
#include <libgen.h>         // dirname
#include <linux/limits.h>    // PATH_MAX
#include <unistd.h>         // readlink
#endif    // #if OS


// Contains utilities that shouldn't be in header files

namespace Util
{


// Get the directory that contains the executable
[[nodiscard]] std::string get_exe_dir() {
#if defined(__unix__) || defined(linux)
    std::string dir_name( PATH_MAX, '\0' );
    // readlink gets executable path
    if( readlink( "/proc/self/exe", dir_name.data(), PATH_MAX ) == -1 )
        return "";
    // remove everything after the last '/'
    dir_name.erase( dir_name.rfind( '/' ) );
    dir_name.append( "/" ).shrink_to_fit();
    return dir_name;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    std::array<CHAR, MAX_PATH> path;
    GetModuleFileName( nullptr, path.data(), size( path ) );
    std::string dir_name = path.data();
    const auto end_pos = dir_name.rfind( '\\' );
    dir_name.erase( end_pos );
    return dir_name + "\\";
#endif    // #if OS
}

// Get the directory that contains the assets
[[nodiscard]] std::string get_resource_dir() {
    return get_exe_dir() + "../share/" + PROJECT_NAME + "/";
}

// To prevent weak vtable
Cloneable::~Cloneable() = default;


}    // namespace Util
