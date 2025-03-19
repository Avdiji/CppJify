# Requirements
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
set(CPP_JIFY CppJify)
project(${CPP_JIFY})

# Find JNI
# find_package(JNI REQUIRED)
# include_directories(${JNI_INCLUDE_DIRS})

# target_link_libraries(${CPP_JIFY} ${JNI_LIBRARIES})

# Include Dirs
add_subdirectory(src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include include)

include(${CMAKE_SOURCE_DIR}/cmake/install/Install.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/FindAndLinkDeps.cmake)
