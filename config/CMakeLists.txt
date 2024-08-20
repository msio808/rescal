cmake_minimum_required(VERSION 3.22)

project(rescal VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic -g")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main
        ../src/main.c
        ../src/helpers/src.c
        ../src/helpers/helpers.c
        ../include/src.h
        ../include/helpers.h
)

target_link_libraries(main PRIVATE m)