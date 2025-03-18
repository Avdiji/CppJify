add_library(${CPP_JIFY} CppJify.cpp)
target_link_libraries(${CPP_JIFY} ${JNI_LIBRARIES})
add_subdirectory(${PROJECT_SOURCE_DIR}/include include)