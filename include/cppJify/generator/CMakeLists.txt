add_subdirectory(blueprints)

target_sources(
        ${CPP_JIFY}
        PUBLIC FILE_SET
        HEADERS
        BASE_DIRS
        ${CMAKE_SOURCE_DIR}/include/
        FILES
        Generator.hpp
        JniGenerator.hpp
        JavaGenerator.hpp
        Placeholder.hpp
)