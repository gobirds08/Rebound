cmake_minimum_required(VERSION 3.14)
project(Rebound VERSION 1.0 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically download SFML using FetchContent
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)
FetchContent_MakeAvailable(SFML)

# Add all source and header files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/headers/*.h
)

# Create executable
add_executable(Rebound ${SOURCES})

# Include the headers directory
target_include_directories(Rebound PRIVATE src/headers)

# Link SFML
target_link_libraries(Rebound PRIVATE sfml-graphics sfml-window sfml-system)

if (WIN32)
    add_custom_command(TARGET Rebound POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:sfml-graphics>
            $<TARGET_FILE_DIR:Rebound>
    )
endif()

# (Optional) Set working directory for assets like fonts or textures
set_target_properties(Rebound PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/fonts"
)
