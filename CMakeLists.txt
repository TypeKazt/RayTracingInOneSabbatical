# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(RayTracing)

# Add source to this project's executable.
add_library(PPMLib ./src/PPMFormatRender.cpp ./src/PPMFormatRender.h)
include_directories("./src")

add_executable (RayTracingInOneSabbatical ./src/main.cpp)
target_link_libraries(RayTracingInOneSabbatical PPMLib)

# TODO: Add tests and install targets if needed.