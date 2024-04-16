# INSTALL
install(
    TARGETS ${CPP_JIFY}
    EXPORT ${CPP_JIFY}Targets

    FILE_SET HEADERS
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(
    EXPORT ${CPP_JIFY}Targets
    FILE ${CPP_JIFY}Targets.cmake
    # NAMESPACE ${CPP_JIFY}:: no namespace for this package
    DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_INSTALL_PREFIX}/cmake/${CPP_JIFY}ConfigVersion.cmake
    VERSION 1.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in
    ${CMAKE_INSTALL_PREFIX}/cmake/${CPP_JIFY}Config.cmake
    INSTALL_DESTINATION lib/cmake/Project${CPP_JIFY}
)

install(
    FILES
    ${CMAKE_INSTALL_PREFIX}/cmake/${CPP_JIFY}Config.cmake
    ${CMAKE_INSTALL_PREFIX}/cmake/${CPP_JIFY}ConfigVersion.cmake
    ${PROJECT_SOURCE_DIR}/cmake/CppJifyHelper.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
)