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

include(${CMAKE_SOURCE_DIR}/cmake/checker/clang-tidy.cmake)

add_subdirectory(src)
target_link_libraries(${CPP_JIFY} ${JNI_LIBRARIES})
