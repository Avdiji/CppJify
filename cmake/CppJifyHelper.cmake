function(create_jbind_api jbind_target_name jbind_interface_file)
    
    # find_package(JNI REQUIRED)
    # include_directories(${JNI_INCLUDE_DIRS})

    # add_executable(${jbind_target_name} ${jbind_interface_file})

    # target_link_libraries(${jbind_target_name} CppJBind::JBind)
    # target_link_libraries(${jbind_target_name} ${JNI_LIBRARIES})

    # add_custom_command(
    #     TARGET ${jbind_target_name}
    #     POST_BUILD
    #     COMMAND ${jbind_target_name}
    #     COMMENT "Generating Java-API"
    # )
endfunction()