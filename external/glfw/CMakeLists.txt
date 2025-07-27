cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

project(GLFW VERSION 3.5.0)


string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" GLFW_STANDALONE)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" ${GLFW_STANDALONE})
option(GLFW_BUILD_TESTS "Build the GLFW test programs" ${GLFW_STANDALONE})
option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_INSTALL "Generate installation target" ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(CMakeDependentOption)

if (GLFW_USE_OSMESA)
    message(FATAL_ERROR "GLFW_USE_OSMESA has been removed; set the GLFW_PLATFORM init hint")
endif()

if (DEFINED GLFW_USE_WAYLAND AND UNIX AND NOT APPLE)
    message(FATAL_ERROR
        "GLFW_USE_WAYLAND has been removed; delete the CMake cache and set GLFW_BUILD_WAYLAND and GLFW_BUILD_X11 instead")
endif()

cmake_dependent_option(GLFW_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GLFW_BUILD_COCOA "Build support for Cocoa" ON "APPLE" OFF)
cmake_dependent_option(GLFW_BUILD_X11 "Build support for X11" ON "UNIX;NOT APPLE" OFF)
cmake_dependent_option(GLFW_BUILD_WAYLAND "Build support for Wayland" ON "UNIX;NOT APPLE" OFF)

cmake_dependent_option(GLFW_USE_HYBRID_HPG "Force use of high-performance GPU on hybrid systems" OFF
                       "WIN32" OFF)
cmake_dependent_option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON
                       "MSVC" OFF)

set(GLFW_LIBRARY_TYPE "${GLFW_LIBRARY_TYPE}" CACHE STRING
    "Library type override for GLFW (SHARED, STATIC, OBJECT, or empty to follow BUILD_SHARED_LIBS)")

if (GLFW_LIBRARY_TYPE)
    if (GLFW_LIBRARY_TYPE STREQUAL "SHARED")
        set(GLFW_BUILD_SHARED_LIBRARY TRUE)
    else()
        set(GLFW_BUILD_SHARED_LIBRARY FALSE)
    endif()
else()
    set(GLFW_BUILD_SHARED_LIBRARY ${BUILD_SHARED_LIBS})
endif()


find_package(Threads REQUIRED)

#--------------------------------------------------------------------
# Report backend selection
#--------------------------------------------------------------------
if (GLFW_BUILD_WIN32)
    message(STATUS "Including Win32 support")
endif()
if (GLFW_BUILD_COCOA)
    message(STATUS "Including Cocoa support")
endif()
if (GLFW_BUILD_WAYLAND)
    message(STATUS "Including Wayland support")
endif()
if (GLFW_BUILD_X11)
    message(STATUS "Including X11 support")
endif()

#--------------------------------------------------------------------
# Apply Microsoft C runtime library option
# This is here because it also applies to tests and examples
#--------------------------------------------------------------------
if (MSVC AND NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()


#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------
add_subdirectory(src)


