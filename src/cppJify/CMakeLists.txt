# create lib, add corresponding header files and include all dependencies.
add_library(${CPP_JIFY} CppJify.cpp)
target_compile_options(${CPP_JIFY} PUBLIC "/GR")
add_subdirectory(${PROJECT_SOURCE_DIR}/include include)
include(${CMAKE_SOURCE_DIR}/cmake/dependencies/FindAndLinkDeps.cmake)

# Install target for CppJify
include(${CMAKE_SOURCE_DIR}/cmake/install/CppJifyInstall.cmake)

add_subdirectory(mapper)
add_subdirectory(utils)
