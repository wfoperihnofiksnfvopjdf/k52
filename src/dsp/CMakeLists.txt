cmake_minimum_required(VERSION 2.8)
project(k52_dsp)

set(DSP_COMMON_INCLUDE ${k52_SOURCE_DIR}/include/k52/dsp)

# dsp library
set(DSP_HEADERS
    ${DSP_COMMON_INCLUDE}/akima_spline.h
    ${DSP_COMMON_INCLUDE}/akima_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/cwt.h
    ${DSP_COMMON_INCLUDE}/mhat_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/Imfcc.h
    ${DSP_COMMON_INCLUDE}/cosin_preobrasovanie.h
    ${DSP_COMMON_INCLUDE}/windows.h
    ${DSP_COMMON_INCLUDE}/haar_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/morlet_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/spline.h
    ${DSP_COMMON_INCLUDE}/spline_based_wavelet_function.h
    ${DSP_COMMON_INCLUDE}/wavelet.h
    ${DSP_COMMON_INCLUDE}/transform/fast_fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/i_fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/inverse_fourier_transform.h
    ${DSP_COMMON_INCLUDE}/transform/circular_convolution.h
    ${DSP_COMMON_INCLUDE}/transform/fourier_based_circular_convolution.h
    ${DSP_COMMON_INCLUDE}/transform/i_circular_convolution.h
    ${DSP_COMMON_INCLUDE}/transform/wavelet/fast_wavelet_transform.h
    ${DSP_COMMON_INCLUDE}/transform/wavelet/i_scale.h
    ${DSP_COMMON_INCLUDE}/transform/wavelet/i_wavelet.h
    ${DSP_COMMON_INCLUDE}/transform/wavelet/i_wavelet_transform.h
    ${DSP_COMMON_INCLUDE}/transform/wavelet/linear_scale.h
    ${DSP_COMMON_INCLUDE}/transform/wavelet/logarithmic_scale.h
)

# dsp source
set(DSP_SOURCE
    akima_spline.cpp
    akima_wavelet_function.cpp
    cwt.cpp
    mhat_wavelet_function.cpp
    Imfcc.cpp
    cosin_preobrasovanie.cpp
    windows.cpp
    haar_wavelet_function.cpp
    morlet_wavelet_function.cpp
    spline_based_wavelet_function.cpp
    wavelet.cpp
    transform/fast_fourier_transform.cpp
    transform/fourier_transform.cpp
    transform/inverse_fourier_transform.cpp
    transform/circular_convolution.cpp
    transform/fourier_based_circular_convolution.cpp
    transform/wavelet/fast_wavelet_transform.cpp
    transform/wavelet/linear_scale.cpp
    transform/wavelet/logarithmic_scale.cpp
)

include_directories(
    ${k52_SOURCE_DIR}/src
    ${k52_SOURCE_DIR}/include
    ${K52_BOOST_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIR}
)

set(k52_DSP_LIB k52_dsp)
add_library(
    ${k52_DSP_LIB}
    ${K52_LIBS_TYPE}
    ${DSP_SOURCE}
    ${DSP_HEADERS}
)

if(K52_LIindowsBS_TYPE_DYNAMIC)
    target_link_libraries(
        ${k52_DSP_LIB}
        ${FFTW3_LIBRARIES}
    )
endif()

install(TARGETS ${k52_DSP_LIB} DESTINATION ${k52_LIB_DESTINATION})
