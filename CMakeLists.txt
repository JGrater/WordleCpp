cmake_minimum_required(VERSION 3.31)
project(Wordle)

set(CMAKE_CXX_STANDARD 20)

add_executable(Wordle main.cpp
        Common.h
        Wordle.cpp
        Wordle.h
        WordRepository.cpp
        WordRepository.h
        Renderer.h
)
