# Set target name for later use
set(TARGET_NAME 3d-graphics-learning)

# Include project setup macro for grouping folders
include(${CMAKE_SOURCE_DIR}/cmake/ProjectSetup.cmake)

# Gather headers and src files
file(
    GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(
    GLOB_RECURSE HEADER_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# Add executable named TARGET_NAME
add_executable(${TARGET_NAME} ${SRC_FILES} ${HEADER_FILES})

# Dependencies

find_package(SDL2 CONFIG REQUIRED)

# Ugly SDL2 setup
if(TARGET SDL2::SDL2)
    set(SDL_TARGET SDL2::SDL2)
elseif(TARGET SDL2::SDL2-static)
    set(SDL_TARGET SDL2::SDL2-static)
else()
    message(FATAL_ERROR "Neither SDL2::SDL2 nor SDL2::SDL2-static found")
endif()

# Link the found library
target_link_libraries(${TARGET_NAME} PRIVATE ${SDL_TARGET})

# Ensure we can see the source and header files
target_include_directories(
    ${TARGET_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src
)

culprit_group_folders()

