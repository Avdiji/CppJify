target_sources(
        ${CPP_JIFY}
        PUBLIC FILE_SET
        HEADERS
        BASE_DIRS
        ${CMAKE_SOURCE_DIR}/include/
        FILES
        SharedPtrMapper.hpp
        UniquePtrMapper.hpp
)