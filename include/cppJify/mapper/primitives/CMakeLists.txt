target_sources(
        ${CPP_JIFY}
        PUBLIC FILE_SET
        HEADERS
        BASE_DIRS
        ${CMAKE_SOURCE_DIR}/include/
        FILES
        BoolMapper.hpp
        CharMapper.hpp
        DoubleMapper.hpp
        FloatMapper.hpp
        IntMapper.hpp
        LongMapper.hpp
        ShortMapper.hpp
        StringMapper.hpp
)