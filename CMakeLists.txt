cmake_minimum_required(VERSION 3.18)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "Use vcpkg as the package manager")
endif()


project(snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries("${PROJECT_NAME}" PRIVATE sfml-graphics sfml-audio ${OPENGL_LIBRARIES})


#Resource directory

set(RES_SRC ${CMAKE_CURRENT_SOURCE_DIR}/data)
if(EXISTS ${RES_SRC})
    set(RES_DEST ${CMAKE_CURRENT_BINARY_DIR}/share/${PROJECT_NAME})
    if(WINDOWS) #windows doesn't allow symlink for non-admins
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_SRC} ${RES_DEST}
            DEPENDS ${RES_DEST}
            COMMENT "copy resources folder from ${RES_SRC} => ${RES_DEST}"
        )
    else()
        file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/share/)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/share/)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${RES_SRC} ${RES_DEST}
            DEPENDS ${RES_DEST}
            COMMENT "symbolic link resources folder from ${RES_SRC} => ${RES_DEST}"
        )
    endif()
endif()


