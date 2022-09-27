set(sources src/Point.cpp)
set(headers inc/point/Point.hpp)

add_library(mesh ${sources} ${headers})
add_library(${PROJECT_NAME}::mesh ALIAS mesh)

target_compile_features(mesh PUBLIC cxx_std_17)
target_include_directories(mesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
