add_subdirectory(classes)
add_subdirectory(primitives)
add_subdirectory(type_modifiers)
add_subdirectory(smart_ptrs)

target_sources(
        ${CPP_JIFY}
        PUBLIC FILE_SET
        HEADERS
        BASE_DIRS
        ${CMAKE_SOURCE_DIR}/include/
        FILES
        JifyMapper.hpp
        BasicMapper.hpp
)