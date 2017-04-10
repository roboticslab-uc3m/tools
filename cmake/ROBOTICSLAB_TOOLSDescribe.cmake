# Store the package in the user registry.
export(PACKAGE ROBOTICSLAB_TOOLS)

# Retrieve global properties.
get_property(ROBOTICSLAB_TOOLS_INCLUDE_DIRS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)
get_property(ROBOTICSLAB_TOOLS_TARGETS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_TARGETS)
get_property(_ROBOTICSLAB_TOOLS_LIBRARIES GLOBAL PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES)

# Append namespace prefix to exported libraries.
set(ROBOTICSLAB_TOOLS_LIBRARIES)
foreach(lib ${_ROBOTICSLAB_TOOLS_LIBRARIES})
  list(APPEND ROBOTICSLAB_TOOLS_LIBRARIES ROBOTICSLAB_TOOLS::${lib})
endforeach()
unset(_ROBOTICSLAB_TOOLS_LIBRARIES) # just in case

# Set build/install pairs of paths for each exported property.
set(ROBOTICSLAB_TOOLS_BUILD_INCLUDE_DIRS ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})
set(ROBOTICSLAB_TOOLS_INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR})

# Create and install config and version files (YCM).
include(InstallBasicPackageFiles)

install_basic_package_files(ROBOTICSLAB_TOOLS
                            VERSION ${ROBOTICSLAB_TOOLS_VERSION_SHORT}
                            COMPATIBILITY AnyNewerVersion
                            TARGETS_PROPERTY ROBOTICSLAB_TOOLS_TARGETS
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO
                            EXTRA_PATH_VARS_SUFFIX INCLUDE_DIRS)

# Configure and create uninstall target (YCM).
include(AddUninstallTarget)

