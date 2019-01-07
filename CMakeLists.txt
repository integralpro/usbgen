cmake_minimum_required (VERSION 3.6)
set(PROJ "usbgen")
project (${PROJ} C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(include)

add_custom_command(
        OUTPUT usbgen.h
        COMMAND ${CMAKE_C_COMPILER} -P -C -E ${CMAKE_CURRENT_SOURCE_DIR}/usbgen_src.h -o usbgen.h.in -I${CMAKE_CURRENT_SOURCE_DIR}/include -DAMALGAMATION
        COMMAND
        COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/include/Std.h > usbgen.h
        COMMAND cat usbgen.h.in >> usbgen.h
        COMMAND clang-format -i usbgen.h
        MAIN_DEPENDENCY usbgen_src.h
        COMMENT "Preprocessing usbgen.h"
        VERBATIM)

add_custom_target(
        usbgen ALL
        DEPENDS usbgen.h
        COMMENT "Preprocessing usbgen.h.in"
        VERBATIM)

include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(examples)