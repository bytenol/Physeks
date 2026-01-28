cmake_minimum_required(VERSION 3.19)

project(Physeks_Example)

include_directories("../include")

add_executable(particles "particles.cpp")
target_link_libraries(particles PRIVATE SDL3::SDL3)

add_executable(gravity "gravity.cpp")
target_link_libraries(gravity PRIVATE SDL3::SDL3)