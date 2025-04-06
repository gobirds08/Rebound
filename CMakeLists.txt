cmake_minimum_required(VERSION 3.14)
project(Rebound VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    Rebound/src/main.cpp
    Rebound/src/Ball.cpp
    Rebound/src/Basket.cpp
    Rebound/src/Button.cpp
    Rebound/src/Game.cpp

    Rebound/src/headers/Ball.h
    Rebound/src/headers/Basket.h
    Rebound/src/headers/Button.h
    Rebound/src/headers/CollisionResult.h
    Rebound/src/headers/Game.h
    Rebound/src/headers/Utility.h
)

add_executable(Rebound ${SOURCES})

target_include_directories(Rebound PRIVATE "${CMAKE_SOURCE_DIR}/Rebound/src/headers")

target_include_directories(Rebound PRIVATE "${CMAKE_SOURCE_DIR}/Dependencies/SFML/include")
target_link_directories(Rebound PRIVATE "${CMAKE_SOURCE_DIR}/Dependencies/SFML/lib")
target_link_libraries(Rebound sfml-graphics sfml-window sfml-system)

set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/bin")

add_custom_command(TARGET Rebound POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_DLL_DIR}"
    "$<TARGET_FILE_DIR:Rebound>"
)

set_target_properties(Rebound PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Rebound/fonts"
)
