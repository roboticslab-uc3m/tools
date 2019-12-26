# Store the package in the user registry.
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)

# Create and install config and version files (YCM).
include(InstallBasicPackageFiles)

install_basic_package_files(ROBOTICSLAB_TOOLS
                            VERSION ${ROBOTICSLAB_TOOLS_VERSION_SHORT}
                            COMPATIBILITY AnyNewerVersion
                            NO_SET_AND_CHECK_MACRO
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO
                            NAMESPACE ROBOTICSLAB::)

# Configure and create uninstall target (YCM).
include(AddUninstallTarget)
