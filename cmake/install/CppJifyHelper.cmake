# Create a target, which utilizes the CppJify library
function(create_jify_target target_name mapper_main path_to_jify_includes)
    
    find_package(fmt REQUIRED)
    find_package(JNI REQUIRED)
    include_directories(${JNI_INCLUDE_DIRS})

    add_executable(${target_name} ${mapper_main})
    target_link_libraries(${target_name} PUBLIC CppJify)
    target_link_libraries(${target_name} PUBLIC fmt::fmt)
    target_link_libraries(${target_name} PUBLIC ${JNI_LIBRARIES})

    target_include_directories(${target_name} PUBLIC ${path_to_jify_includes})

endfunction()

# Compile and generate a .jar file from the generated files
function(create_jify_jar target_name jar_name mapped_files_path)
    # set(link_targets ${ARGN})

    # file(GLOB_RECURSE JNI_SRC_FILES "${mapped_files_path}/*.jni.cpp")
    
    # add_library(${target_name} STATIC ${JNI_SRC_FILES})
    # target_link_libraries(${target_name} PUBLIC ${link_targets})

endfunction()