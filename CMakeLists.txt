# Requirements
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
set(CPP_JIFY CppJify)
project(${CPP_JIFY})

# Prerequisites
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Crate target and with JNI
add_subdirectory(src)
target_link_libraries(${CPP_JIFY} ${JNI_LIBRARIES})

include(cmake/Install.cmake)
add_subdirectory(demo) # del this
