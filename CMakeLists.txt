cmake_minimum_required (VERSION 3.6)
set(PROJ "usbgen")
project (${PROJ} C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(OUTPUT usbgen/usbgen.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/usbgen)

add_custom_command(
        OUTPUT ${OUTPUT}
        OUTPUT .phony
        COMMAND ${CMAKE_C_COMPILER} -P -C -E ${CMAKE_CURRENT_SOURCE_DIR}/usbgen_src.h -o usbgen.h.in -I${CMAKE_CURRENT_SOURCE_DIR}/include -DAMALGAMATION
        COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/include/Std.h > ${OUTPUT}
        COMMAND cat usbgen.h.in >> ${OUTPUT}
        COMMAND clang-format -i ${OUTPUT}
        MAIN_DEPENDENCY usbgen_src.h
        COMMENT "Preprocessing usbgen.h"
        VERBATIM)

add_custom_target(
        usbgen ALL
        DEPENDS ${OUTPUT}
        DEPENDS .phony
        VERBATIM)

add_subdirectory(examples)