DESCRIPTION = "PPP support for Telit 3G Module"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=4d92cd373abda3937c2bc47fbc49d690 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

etcdir = "/etc/ppp"
homedir = "/home/root"

#FILESEXTRAPATHS_prepend := "${THISDIR}:"
#INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
#INHIBIT_PACKAGE_STRIP = "1"

SRC_URI_append = " \
    file://etc \
    file://home \
"

do_install_append() {
    mkdir -p ${D}${etcdir}
    cp -r ${WORKDIR}/etc/ppp/* ${D}${etcdir}
    cp ${WORKDIR}/home/root/* ${D}${etcdir}

#    mkdir -p ${D}${homedir}
#    cp -p ${WORKDIR}/home/root/* ${D}${homedir}
}

FILES_${PN} += "${base_libdir}"
