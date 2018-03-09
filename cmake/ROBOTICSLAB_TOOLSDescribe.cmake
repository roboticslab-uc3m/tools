# Store the package in the user registry.
export(PACKAGE ROBOTICSLAB_TOOLS)

# Create and install config and version files (YCM).
include(InstallBasicPackageFiles)

install_basic_package_files(ROBOTICSLAB_TOOLS
                            VERSION ${ROBOTICSLAB_TOOLS_VERSION_SHORT}
                            COMPATIBILITY AnyNewerVersion
                            TARGETS_PROPERTY ROBOTICSLAB_TOOLS_TARGETS
                            NO_SET_AND_CHECK_MACRO
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO
                            NAMESPACE ROBOTICSLAB::
                            NO_COMPATIBILITY_VARS)

# Configure and create uninstall target (YCM).
include(AddUninstallTarget)
