# Requirements
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
set(CPP_JIFY CppJify)
project(${CPP_JIFY})

# Find JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Include Dirs
add_subdirectory(src)
include(cmake/install/Install.cmake)
