cmake_minimum_required(VERSION 3.27)
project(math_builder)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(math_builder main.cpp
        headers/FunctionInputField.h
        src/FunctionInputField.cpp
        headers/Screen.h
        main.h
        headers/Counter.h
        headers/Counter.h
        headers/CursorCoordinates.h
        headers/CoordinatesNetwork.h)

target_link_libraries(math_builder sfml-graphics sfml-audio)