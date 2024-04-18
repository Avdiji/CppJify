add_library(${CPP_JIFY} CppJify.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/include include)

add_subdirectory(utils)
add_subdirectory(composer)
add_subdirectory(jbinder)