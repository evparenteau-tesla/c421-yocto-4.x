DESCRIPTION = "PPP append to add support for Telit 3G Module"

#LICENSE = "MIT"
#LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=4d92cd373abda3937c2bc47fbc49d690 \
#                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
LICENSE = "BSD & GPLv2+ & LGPLv2+ & PD"
LIC_FILES_CHKSUM = "file://pppd/ccp.c;beginline=1;endline=29;md5=e2c43fe6e81ff77d87dc9c290a424dea \
                    file://pppd/plugins/passprompt.c;beginline=1;endline=10;md5=3bcbcdbf0e369c9a3e0b8c8275b065d8 \
                    file://pppd/tdb.c;beginline=1;endline=27;md5=4ca3a9991b011038d085d6675ae7c4e6 \
                    file://chat/chat.c;beginline=1;endline=15;md5=0d374b8545ee5c62d7aff1acbd38add2"

homedir = "/home/root"

FILESEXTRAPATHS_prepend := "${THISDIR}:"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

SRC_URI_append = " \
    file://etc/ppp/chap-secrets \
    file://etc/ppp/ip-down \
    file://etc/ppp/ip-up \
    file://etc/ppp/options \
    file://etc/ppp/pap-secrets \
    file://etc/ppp/ppp_on_boot \
    file://etc/ppp/reset_modem \
    file://etc/ppp/chatscripts/telit.chat \
    file://etc/ppp/ip-down.d/92removedns \
    file://etc/ppp/ip-up.d/08setupdns \
    file://etc/ppp/peers/provider \
    file://etc/ppp/peers/wvdial \
    file://etc/ppp/peers/wvdial-pipe \
    file://home/root/ppp_up \
"

do_install_append() {
    install -m 0644 ${WORKDIR}/etc/ppp/chap-secrets ${D}${sysconfdir}/ppp/chap-secrets
    install -m 0755 ${WORKDIR}/etc/ppp/ip-down ${D}${sysconfdir}/ppp/ip-down
    install -m 0755 ${WORKDIR}/etc/ppp/ip-up ${D}${sysconfdir}/ppp/ip-up
    install -m 0644 ${WORKDIR}/etc/ppp/options ${D}${sysconfdir}/ppp/options
    install -m 0644 ${WORKDIR}/etc/ppp/pap-secrets ${D}${sysconfdir}/ppp/pap-secrets
    install -m 0755 ${WORKDIR}/etc/ppp/ip-up ${D}${sysconfdir}/ppp/ppp_on_boot
    install -m 0755 ${WORKDIR}/etc/ppp/ip-up ${D}${sysconfdir}/ppp/reset_modem
    install -m 0755 ${WORKDIR}/home/root/ppp_up ${D}${sysconfdir}/ppp/ppp_up
    mkdir -p ${D}${sysconfdir}/ppp/chatscripts
    install -m 0755 ${WORKDIR}/etc/ppp/chatscripts/telit.chat ${D}${sysconfdir}/ppp/chatscripts/telit.chat
    mkdir -p ${D}${sysconfdir}/ppp/ip-down.d
    install -m 0755 ${WORKDIR}/etc/ppp/ip-down.d/92removedns ${D}${sysconfdir}/ppp/ip-down.d/92removedns
    mkdir -p ${D}${sysconfdir}/ppp/ip-up.d
    install -m 0755 ${WORKDIR}/etc/ppp/ip-up.d/08setupdns ${D}${sysconfdir}/ppp/ip-up.d/08setupdns
    mkdir -p ${D}${sysconfdir}/ppp/peers
    install -m 0755 ${WORKDIR}/etc/ppp/peers/provider ${D}${sysconfdir}/ppp/peers/provider
    install -m 0755 ${WORKDIR}/etc/ppp/peers/wvdial ${D}${sysconfdir}/ppp/peers/wvdial
    install -m 0755 ${WORKDIR}/etc/ppp/peers/wvdial-pipe ${D}${sysconfdir}/ppp/peers/wvdial-pipe
}

FILES_${PN} += "${base_libdir}"
