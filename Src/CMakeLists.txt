cmake_minimum_required(VERSION 3.4)

#set compiler and linker to gcc 5.0
set(CMAKE_CXX_COMPILER "/boot/system/bin/g++-x86")

project(CMakeHelper)

set(CMAKE_LIBRARY_PATH $(CMAKE_LIBRARY_PATH) /boot/system/lib)

file(GLOB CMakeHelperSrc 
"*.h"
"*.cpp"
)

link_directories("/boot/system/lib/x86")

add_executable(CMakeHelper ${CMakeHelperSrc})
target_compile_features(CMakeHelper PRIVATE cxx_range_for)
target_link_libraries(CMakeHelper be translation tracker stdc++)

