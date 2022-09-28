set(sources src/Renderer.cpp)
set(headers inc/Renderer.hpp)

add_library(renderer ${sources} ${headers})
target_link_libraries(renderer mesh loader utils)
add_library(${PROJECT_NAME}::renderer ALIAS renderer)

target_compile_features(renderer PUBLIC cxx_std_17)
target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
