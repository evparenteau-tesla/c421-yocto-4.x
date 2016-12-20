# Copyright (C) 2016 WinSystems, Inc.
# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Linux Kernel provided and supported by WinSystems, Inc."

require recipes-kernel/linux/linux-imx.inc
require recipes-kernel/linux/linux-dtb.inc

DEPENDS += "lzop-native bc-native"

#SRCBRANCH = "imx_4.1.15_1.0.0_ga"
#LOCALVERSION = "-1.0.0"
#SRCREV = "3924425928aab27283e4c635f61bd523f20a7168"

SRCBRANCH = "imx_4.1.15_1.0.0_ga"
LOCALVERSION = "-1.1.0"
SRCREV = "a4d2a08f3bfc57ff5d7d1307fb23f52f1e681aca"

#SRCBRANCH = "imx_4.1.15_1.0.0_ga"
#LOCALVERSION = "-1.2.0"
#SRCREV = "77f61547834c4f127b44b13e43c59133a35880dc"

#SRCBRANCH = "imx_4.1.15_2.0.0_ga"
#LOCALVERSION = "-2.0.0"
#SRCREV = "b63f3f52cb393e3287352cf63f0caef31a33ab63"

SRC_URI += " \
           file://0001-imx6solo-c421-Add-c421-device-tree-to-Makefile.patch \
           file://imx6solo-c421.dts \
"

DEFAULT_PREFERENCE = "1"

do_compile_prepend() {
         cp -p ${WORKDIR}/imx6solo-c421.dts ${S}/arch/arm/boot/dts
}

COMPATIBLE_MACHINE = "mx6"
COMPATIBLE_MACHINE = "imx6soloc421"
