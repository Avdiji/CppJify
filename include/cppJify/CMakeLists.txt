add_subdirectory(mapper)
add_subdirectory(generator)
add_subdirectory(utils)

target_sources(
        ${CPP_JIFY}
        PUBLIC FILE_SET
        HEADERS
        BASE_DIRS
        ${CMAKE_SOURCE_DIR}/include/
        FILES
        CppJify.hpp
)