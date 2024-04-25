# Use the patch file in the files directory to patch the source code 
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI:append = " file://fix-cmake-version.patch"
