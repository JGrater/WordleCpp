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

# Copy assets next to the built executable so relative paths like
# "assets/words.txt" resolve correctly regardless of working directory.
add_custom_command(TARGET Wordle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Wordle>/assets
)