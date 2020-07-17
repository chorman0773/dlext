cmake_minimum_required(VERSION 3.15)
project(libdl_ext C)

enable_testing()

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(dl-ext SHARED include/dlext.h fdlopen.c)

target_link_libraries(dl-ext PUBLIC dl)

find_program(DOXYGEN doxygen)

if(NOT DOXYGEN STREQUAL "DOXYGEN-NOTFOUND")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man)
    add_custom_target(man-pages ALL
            COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            DEPENDS dl-ext)
endif()

add_subdirectory(test)

install(TARGETS dl-ext)
install(DIRECTORY include/ TYPE INCLUDE)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man/ TYPE MAN)