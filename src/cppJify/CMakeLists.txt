# create lib, add corresponding header files and include all dependencies.
add_library(${CPP_JIFY} CppJify.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/include include)

# Install target for CppJify
include(${CMAKE_SOURCE_DIR}/cmake/install/CppJifyInstall.cmake)

find_package(fmt REQUIRED)
find_package(Boost REQUIRED)
target_link_libraries(${CPP_JIFY} fmt::fmt)
target_link_libraries(${CPP_JIFY} Boost::boost)

add_subdirectory(mapper)
add_subdirectory(utils)
