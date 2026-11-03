cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING
        "Vcpkg toolchain file"
    )
endif()

project(3d-graphics-learning VERSION 1.0.0 LANGUAGES C CXX)

add_subdirectory(3d-graphics-learning)
