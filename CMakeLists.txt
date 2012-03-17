cmake_minimum_required (VERSION 2.8)

project (sag)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set (INCLUDES
    # include directories
)
set (LIBRARIES
    # libraries
)

###############################################################

include_directories (
    src
    ${INCLUDES}
)

file (GLOB_RECURSE SRCS "src/*.cpp")
file (GLOB_RECURSE HDRS "src/*.h")

add_executable (
    sag
    ${SRCS}
    ${HDRS}
)

target_link_libraries (
    sag
    ${LIBRARIES}
)