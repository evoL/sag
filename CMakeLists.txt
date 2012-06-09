cmake_minimum_required (VERSION 2.8)

project (sag)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_package(GTK2 2.20 REQUIRED gtk gtkmm)

set (INCLUDES
    ${GTK2_INCLUDE_DIRS}
)
set (LIBRARIES
    ${GTK2_LIBRARIES}
)

add_definitions("-std=c++11")

###############################################################

include_directories (
    src
    ${INCLUDES}
)

file (GLOB_RECURSE SRCS "src/*/*.cpp")
file (GLOB_RECURSE HDRS "src/*.h")

add_executable (
    sag
    src/main.cpp
    ${SRCS}
    ${HDRS}
)

target_link_libraries (
    sag
    ${LIBRARIES}
)

#################

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions("-stdlib=libc++")
    set_target_properties(sag PROPERTIES LINK_FLAGS "-stdlib=libc++")
endif()