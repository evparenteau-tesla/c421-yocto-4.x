DESCRIPTION = "Application to configure UART for RS485 mode"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://rs485-config.c"

S = "${WORKDIR}"

do_compile() {
        ${CC} rs485-config.c -o rs485-config
}

do_install() {
        install -d ${D}${bindir}
        install -m 0755 rs485-config ${D}${bindir}
}
