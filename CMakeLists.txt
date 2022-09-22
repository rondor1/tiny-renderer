cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(tiny-renderer VERSION 0.0.1 LANGUAGES CXX)

include(cmake/settings.cmake)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(dependencies/image-loader)
add_subdirectory(tr)