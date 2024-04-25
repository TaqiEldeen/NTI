DESCRIPTION = "This is a demo application recipe that is fetched from a remote git repository"
LICENSE = "MIT"

# The LIC_FILES_CHKSUM is the checksum of the license file that is included in the source code
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# The SRC_URI is the remote git repository that you want to fetch the source code from
SRC_URI = "git://github.com/FadyKhalil/DemoApp.git;protocol=https;branch=main"

# The SRCREV is the commit hash that you want to build
SRCREV = "ac436984c286715dd55a883930a8db56a96cdfb3"


inherit cmake
S = "${WORKDIR}/git"

do_configure(){
	mkdir -p ${S}/build
	cmake ${S} -B${S}/build
}

do_compile(){
	oe_runmake -C ${S}/build
}

do_install(){
	install -d ${D}${bindir}
	install -m 0755 ${S}/build/calculator ${D}${bindir}
}

LDFLAGS_append = " -pthread"