# Set the install prefix to the desired root
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# Install the library
install(
    TARGETS ${CPP_JIFY}
    EXPORT ${CPP_JIFY}Targets
    FILE_SET HEADERS
    DESTINATION include
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install the export file
install(
    EXPORT ${CPP_JIFY}Targets
    FILE ${CPP_JIFY}Targets.cmake
    # NAMESPACE ${CPP_JIFY}:: no namespace for this package
    DESTINATION cmake
)

# Generate version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${CPP_JIFY}ConfigVersion.cmake
    VERSION 1.0
    COMPATIBILITY SameMajorVersion
)

# Configure the package config file
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/${CPP_JIFY}Config.cmake
    INSTALL_DESTINATION cmake
)

# Install the package config and version files
install(
    FILES
    ${CMAKE_BINARY_DIR}/cmake/${CPP_JIFY}Config.cmake
    ${CMAKE_BINARY_DIR}/cmake/${CPP_JIFY}ConfigVersion.cmake
    ${CMAKE_CURRENT_LIST_DIR}/CppJifyHelper.cmake
    DESTINATION cmake
)
