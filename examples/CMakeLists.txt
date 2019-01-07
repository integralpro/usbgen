add_executable(microphone
        microphone.cpp
        main.c
        )

add_dependencies(microphone usbgen)

