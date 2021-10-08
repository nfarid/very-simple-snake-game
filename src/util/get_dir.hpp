
#ifndef HPP_UTIL_GET_DIR_
#define HPP_UTIL_GET_DIR_

#include <string>


namespace Util
{


// Get the directory that contains the executable
[[nodiscard]] std::string get_exe_dir();




// Get the directory that contains the assets
[[nodiscard]] std::string get_resource_dir();


}    // namespace Util

#endif    // HPP_UTIL_GET_DIR_
