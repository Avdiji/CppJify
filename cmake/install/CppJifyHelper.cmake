# Create a target, which utilizes the CppJify library
function(create_jify_target target_name mapper_main output_dir)
    set(link_targets ${ARGN})    

    find_package(fmt REQUIRED)
    find_package(JNI REQUIRED)
    include_directories(${JNI_INCLUDE_DIRS})

    add_executable(${target_name} ${mapper_main})
    target_link_libraries(${target_name} PUBLIC CppJify)
    target_link_libraries(${target_name} PUBLIC fmt::fmt)
    target_link_libraries(${target_name} PUBLIC ${JNI_LIBRARIES})
    target_link_libraries(${target_name} PUBLIC ${link_targets})

    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
        OUTPUT_NAME "${target_name}"
    )
endfunction()



# Compile and generate a .jar file from the generated files
function(create_jify_jar target_name jar_name output_dir)
    set(link_targets ${ARGN})

    file(GLOB_RECURSE JNI_SRC_FILES "${CMAKE_BINARY_DIR}/${output_dir}/*.cppjify.cpp")
    file(GLOB_RECURSE JAVA_SRC_FILES "${CMAKE_BINARY_DIR}/${output_dir}/*.java")

    # Generate Library, which creates a static lib from the generated Cpp files
    if(JNI_SRC_FILES AND JAVA_SRC_FILES)
        add_library(${target_name} SHARED ${JNI_SRC_FILES})
        target_link_libraries(${target_name} PRIVATE ${link_targets})

        set_target_properties(${target_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
            OUTPUT_NAME "${target_name}"
        )

        file(WRITE "${CMAKE_BINARY_DIR}/${output_dir}/jsources.txt" "")
        foreach(java_file ${JAVA_SRC_FILES})
            file(APPEND "${CMAKE_BINARY_DIR}/${output_dir}/jsources.txt" "${java_file}\n")
        endforeach()

        execute_process(
            COMMAND javac -d bin @jsources.txt
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}"
        )
        execute_process(
            COMMAND jar cf ${jar_name}.jar *
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${output_dir}/bin"
        )

    else()
        message(WARNING "No CppJify-mapped files have been generated yet, make sure to first run a CppJify target")
    endif()
endfunction()