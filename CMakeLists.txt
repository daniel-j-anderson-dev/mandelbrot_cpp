cmake_minimum_required(VERSION 3.16)

project(
    mandelbrot_generator
    VERSION 0.1
    LANGUAGES CXX
)

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    mandelbrot_lib
    STATIC
    source/mandelbrot.cpp
)
target_compile_features(
    mandelbrot_lib
    PRIVATE
    cxx_std_20
)
target_include_directories(
    mandelbrot_lib
    PUBLIC
    include
)
    
add_executable(
    mandelbrot
    source/main.cpp
)
target_compile_features(
    mandelbrot
    PRIVATE
    cxx_std_20
)
target_include_directories(
    mandelbrot
    PUBLIC
    include
)
target_link_libraries(
    mandelbrot
    mandelbrot_lib
)
