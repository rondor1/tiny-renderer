set(sources src/point/Point.cpp
            src/Model.cpp)
set(headers inc/point/Point.hpp
            inc/Model.hpp)

add_library(model ${sources} ${headers})
add_library(${PROJECT_NAME}::model ALIAS model)

target_compile_features(model PUBLIC cxx_std_17)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
