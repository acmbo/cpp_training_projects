cmake_minimum_required(VERSION 3.9 FATAL_ERROR) 
project(footballdnd5leage)

set(SOURCES 
    src/main.cpp
    )

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED 20)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast \
        -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion \
        -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond \
        -Wduplicated-branches -Wlogical-op -Wnull-dereference \
        -Wuseless-cast -Wdouble-promotion -Wformat=2" )
        #-Wpadded -Wno-error=padded")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)  
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 12.9.9.9)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Weverything -Werror  -Wall -Wpedantic -Wunused -Wno-padded \
            -Wmissing-prototypes -Wno-c++98-compat -Wno-c++98-compat-pedantic \
            -Wno-unused-macros -Wno-newline-eof -Wno-exit-time-destructors \
            -Wno-global-constructors -Wno-gnu-zero-variadic-macro-arguments \
            -Wno-documentation -Wno-c99-extensions \
            -Wno-covered-switch-default \
            -Wno-zero-as-null-pointer-constant \
            -Wno-documentation-unknown-command ")
        else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Weverything -Werror  -Wall -Wpedantic -Wunused -Wno-padded \
            -Wmissing-prototypes -Wno-c++98-compat -Wno-c++98-compat-pedantic \
            -Wno-unused-macros -Wno-newline-eof -Wno-exit-time-destructors \
            -Wno-global-constructors -Wno-gnu-zero-variadic-macro-arguments \
            -Wno-return-std-move-in-c++11 \
            -Wno-documentation -Wno-c99-extensions \
            -Wno-covered-switch-default \
            -Wno-zero-as-null-pointer-constant \
            -Wno-documentation-unknown-command ")
    endif()
endif()

add_executable(footballdnd5leage ${SOURCES})