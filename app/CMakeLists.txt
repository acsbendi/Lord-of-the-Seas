cmake_minimum_required(VERSION 3.4.1)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

set(REQUIRED_SFML_LIBRARIES graphics network window system audio main activity)

set(SFML_DIR "${ANDROID_NDK}/sources/third_party/sfml/lib/${ANDROID_ABI}/cmake/SFML")
find_package(SFML COMPONENTS ${REQUIRED_SFML_LIBRARIES} REQUIRED)

set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_STANDARD 11)
add_library(sfml-test SHARED src/main/cpp/main.cpp)

if(SFML_FOUND)
    foreach(SFML_LIBRARY ${REQUIRED_SFML_LIBRARIES})
        set(SFML_LIBRARY_FULL_NAME "sfml-${SFML_LIBRARY}")
        target_link_libraries(sfml-test ${SFML_LIBRARY_FULL_NAME})
    endforeach(SFML_LIBRARY)
endif()

# add lib dependencies
target_link_libraries(sfml-test
    android
    EGL
    GLESv1_CM
    log)

set(SFML_EXT_DIR "${ANDROID_NDK}/sources/third_party/sfml/extlibs/lib/${ANDROID_ABI}")

add_custom_command(TARGET sfml-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_EXT_DIR}
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    )

foreach(SFML_LIBRARY ${REQUIRED_SFML_LIBRARIES})
    if(NOT ${SFML_LIBRARY} MATCHES "main")
        set(SFML_LIBRARY_FILE_NAME "libsfml-${SFML_LIBRARY}-d.so")
        add_custom_command(TARGET sfml-test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_DIR}/../../${SFML_LIBRARY_FILE_NAME}
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
            )
    endif(NOT ${SFML_LIBRARY} MATCHES "main")
endforeach(SFML_LIBRARY)
