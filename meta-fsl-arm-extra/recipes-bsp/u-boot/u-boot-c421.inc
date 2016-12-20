# Copyright (C) 2016 WinSystems, Inc.

require recipes-bsp/u-boot/u-boot.inc

inherit fsl-u-boot-localversion

DESCRIPTION = "Bootloader for WinSystems, Inc. imx6solo-c421 platform"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"
COMPATIBLE_MACHINE = "imx6soloc421"

DEPENDS_mxs += "elftosb-native openssl-native"

PROVIDES += "virtual/bootloader"
PROVIDES += "u-boot"

SRCBRANCH ??= "master"

SRC_URI = "git://git.freescale.com/imx/uboot-imx.git;protocol=git;branch=${SRCBRANCH} \
           file://0001-imx6soloc421-Add-c421-to-Kconfig.patch \
           file://mx6soloc421_spinor_defconfig \
           file://Kconfig \
           file://MAINTAINERS \
           file://Makefile \
           file://mx6solo.cfg \
           file://mx6soloc421.c \
           file://mx6soloc421.h \
"

S = "${WORKDIR}/git"

do_compile_prepend() {
         cp -p ${WORKDIR}/mx6soloc421_spinor_defconfig ${S}/configs
         cp -p ${WORKDIR}/mx6soloc421.h ${S}/include/configs
         mkdir -p ${S}/board/freescale/mx6soloc421
         cp -p ${WORKDIR}/Kconfig ${S}/board/freescale/mx6soloc421
         cp -p ${WORKDIR}/MAINTAINERS ${S}/board/freescale/mx6soloc421
         cp -p ${WORKDIR}/Makefile ${S}/board/freescale/mx6soloc421
         cp -p ${WORKDIR}/mx6solo.cfg ${S}/board/freescale/mx6soloc421
         cp -p ${WORKDIR}/mx6soloc421.c ${S}/board/freescale/mx6soloc421
}

PACKAGE_ARCH = "${MACHINE_ARCH}"
