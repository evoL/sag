# Strange Attractor Generator

It's just awesome.

## How to build

First, get [CMake](http://www.cmake.org/).
This will allow you to generate custom projects for your favorite IDE.

Then generate a project using CMake. Consult the help (`cmake --help`) for information about which project types does CMake support.
The whole generation process is fairly straightforward - just type `cmake -G"Your Generator" .`. Don't forget about the dot at the end of the command!

**ECLIPSE USERS:** To enable debugging in Eclipse PDT you have to include the Debug build type in the `cmake` command. For instance: `cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug .`.

After you create a project, you can work with it just like with any standard project.

## Copyright info

This project is released under the [MIT license](http://www.opensource.org/licenses/MIT).

Copyright (c) 2012 Rafał Hirsz, Krzysztof Wróbel.