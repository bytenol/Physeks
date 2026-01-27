cmake_minimum_required(VERSION 3.19)

project(Physeks_Example)

include_directories("../include")

add_executable(particles "particles.cpp")
target_link_libraries(particles PRIVATE physeks SDL3::SDL3)