cmake_minimum_required(VERSION 3.19)

project(Physeks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_EXAMPLES "Build test examples" ON)

find_package(SDL3 CONFIG REQUIRED)

file(GLOB PHYSEKS_PROJECT_FILES "src/*.cpp")
file(GLOB PHYSEKS_HEADER_FILES "include/physeks/*.hpp")

add_library(physeks STATIC ${PHYSEKS_HEADER_FILES} ${PHYSEKS_PROJECT_FILES})

if(BUILD_EXAMPLES)
    add_subdirectory("Example")
endif()

add_executable(scratch scratch.cpp)