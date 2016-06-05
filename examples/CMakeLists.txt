cmake_minimum_required(VERSION 2.8)

project(k52_examples)
set(BOOST_ROOT "C:/k52/k52/boost_1_60_0")
set(FFTW3_ROOT "C:/k52/k52/libfftw3")
set(BOOST_LIBRARYDIR "C:/k52/k52/boost/lib32-msvc-14.0")
add_subdirectory(continuous_optimization)
add_subdirectory(genetic_algorithm)
add_subdirectory(dspImfcc)