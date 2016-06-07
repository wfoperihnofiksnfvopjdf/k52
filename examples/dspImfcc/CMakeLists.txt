cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME dspImfcc)
project(${PROJECT_NAME})

set(dsp_HEADERS
    windows.h
    cosin_preobrasovanie.h
    Imfcc.h
)

set(dsp_SOURCE
    main.cpp
    cosin_preobrasovanie.cpp
    Imfcc.cpp
    windows.cpp
)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(k52 REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/../../install")

include_directories(${k52_INCLUDE_DIRS})
link_directories(${k52_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${dsp_SOURCE} ${dsp_HEADERS})

target_link_libraries(${PROJECT_NAME} ${k52_LIBRARIES})

