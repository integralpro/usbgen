include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(microphone
        microphone.cpp
        main.c
        )

add_dependencies(microphone usbgen)
