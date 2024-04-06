DESCRIPTION = "This is a simple Hello World recipe - uses a local source file"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hello-taqi-local.c"

S = "${WORKDIR}"

do_compile() {
	${CC} ${LDFLAGS} hello-taqi-local.c -o hello-taqi-local
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 hello-taqi-local ${D}${bindir}
}