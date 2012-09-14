cmake_minimum_required (VERSION 2.8)

project (sag)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_BUILD_TYPE Release)

include("preprocessing.cmake")

function(add_macro str)
    if(${MSVC})
        add_definitions("/D${str}")
    else()
        add_definitions("-D${str}")
    endif()
endfunction()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(Boost 1.50 REQUIRED COMPONENTS system thread chrono)
    add_macro("HAS_BOOST")
    add_macro("THREAD_NAMESPACE=boost")
else()
    add_macro("THREAD_NAMESPACE=std")
endif()

find_package(GTK2 2.20 REQUIRED gtk gtkmm)

set (INCLUDES
    ${GTK2_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)
set (LIBRARIES
    ${GTK2_LIBRARIES}
    ${Boost_LIBRARIES}
)

add_definitions("-std=c++0x")
add_definitions("-Wall" "-pedantic")

###############################################################

configure_file ("src/formulas/all.h.in" "src/formulas/all.h")
configure_file ("src/formulas/all.cpp.in" "src/formulas/all.cpp")

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
    add_definitions("-stdlib=libc++" "-DNO_THREADED_GENERATOR")
    set_target_properties(sag PROPERTIES LINK_FLAGS "-stdlib=libc++")
endif()