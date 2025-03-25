# Define a function to create a new target and execute it
function(create_jify_target target_name mapper_main)
    
    find_package(fmt REQUIRED)
    find_package(JNI REQUIRED)
    include_directories(${JNI_INCLUDE_DIRS})
    include_directories(${CPP_JIFY_INCLUDE_DIRS})

    add_executable(${target_name} ${mapper_main})
    target_link_libraries(${target_name} PUBLIC ${CPP_JIFY})
    target_link_libraries(${target_name} PUBLIC fmt::fmt)
    target_link_libraries(${target_name} PUBLIC ${JNI_LIBRARIES})


endfunction()


function(create_jify_jar target_name jar_name mapped_files_path)
    set(link_targets ${ARGN})

    file(GLOB_RECURSE JNI_SRC_FILES "${mapped_files_path}/*.jni.cpp")
    
    add_library(${target_name} STATIC ${JNI_SRC_FILES})
    target_link_libraries(${target_name} PUBLIC ${link_targets})

endfunction()