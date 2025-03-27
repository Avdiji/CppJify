# Enable Clang-Tidy only if the environment variable is set
if(DEFINED ENV{ENABLE_JIFY_LINTING} )

    # Find the clang-tidy executable
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    set(CMAKE_CXX_CLANG_TIDY 
        clang-tidy
        -checks=*,-llvmlibc-*,-modernize-use-trailing-return-type,-altera-unroll-loops,-readability-convert-member-functions-to-static,-clang-diagnostic-c++17-extensions,-bugprone-easily-swappable-parameters,-fuchsia-default-arguments-calls
        -p ${CMAKE_BINARY_DIR}/compile_commands.json
        -header-filter=${CMAKE_SOURCE_DIR}
        
        -system-headers=false
        -warnings-as-errors=*,-*
        --extra-arg=-std=c++17
        --extra-arg=/EHsc
    )


else()
    message("Clang-Tidy is not enabled")
endif()
