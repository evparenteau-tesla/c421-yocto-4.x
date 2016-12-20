DESCRIPTION = "Install WLAN drivers for RedPine RS9113"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=4d92cd373abda3937c2bc47fbc49d690 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

#kmoddir = "/lib/modules/3.14.28-1.0.0_ga+g91cf351/kernel/drivers/net/wireless/redpine"

FILESEXTRAPATHS_prepend := "${THISDIR}:"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

SRC_URI_append = " \
    file://bbp_util \
    file://block.sh \
    file://common_insert.sh \
    file://dhcpd.conf \
    file://dhcp_server.sh \
    file://flash.sh \
    file://form_bridge.sh \
    file://hostapd_ccmp.conf \
    file://hostapd.conf \
    file://hostapd_eap.conf \
    file://hostapd_open.conf \
    file://hostapd_server.conf \
    file://hostapd_tkip.conf \
    file://hostapd_wep.conf \
    file://hostapd_wps.conf \
    file://host_ap.sh \
    file://install_bluez.sh \
    file://load_stack.sh \
    file://onebox_common_gpl.ko \
    file://onebox_gpl.ko \
    file://onebox_insert.sh \
    file://onebox_nongpl.ko \
    file://onebox_util \
    file://onebox_wlan_gpl.ko \
    file://onebox_wlan_nongpl.ko \
    file://p2pcommands.pl \
    file://p2p.conf \
    file://per_lpbk.sh \
    file://per_packet.txt \
    file://post_vap.sh \
    file://receive \
    file://remove_all.sh \
    file://sniffer_app \
    file://sniffer.sh \
    file://start_ap.sh \
    file://start_p2p.sh \
    file://start_per.sh \
    file://start_sta.sh \
    file://sta_settings.conf \
    file://transmit \
    file://transmit_packet \
    file://unblock.sh \
    file://upgrade.sh \
    file://wlan_acl.ko \
    file://wlan_bt_insert.sh \
    file://wlan_ccmp.ko \
    file://wlan_disable.sh \
    file://wlan_enable.sh \
    file://wlan.ko \
    file://wlan_scan_sta.ko \
    file://wlan_tkip.ko \
    file://wlan_wep.ko \
    file://wlan_xauth.ko \
    file://wlan_zigb_insert.sh \
    file://wme_broadcast.sh \
    file://wme_self.sh \
    file://wpa_cli \
    file://wpa_supplicant \
    file://wpa_supplicant_ccmp.conf \
    file://wpa_supplicant.conf \
    file://wpa_supplicant_open.conf \
    file://wpa_supplicant_tkip.conf \
    file://wpa_supplicant_wep128.conf \
    file://wpa_supplicant_wep64.conf \
    file://wps.conf \
    file://certs \
    file://firmware \
    file://flash \
"

do_install_append() {
    mkdir -p ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/bbp_util ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/block.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/common_insert.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/dhcp_server.sh ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/dhcpd.conf ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/flash.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/form_bridge.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/host_ap.sh ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_ccmp.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_eap.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_open.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_server.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_tkip.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_wep.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/hostapd_wps.conf ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/install_bluez.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/load_stack.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_insert.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_util ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/p2pcommands.pl ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/p2p.conf ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/per_lpbk.sh ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/per_packet.txt ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/post_vap.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/receive ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/remove_all.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/sniffer_app ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/sniffer.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/start_ap.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/start_p2p.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/start_per.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/start_sta.sh ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/sta_settings.conf ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/transmit ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/transmit_packet ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/unblock.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/upgrade.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_bt_insert.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_disable.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_enable.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_zigb_insert.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wme_broadcast.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wme_self.sh ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wpa_cli ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wpa_supplicant ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wpa_supplicant_ccmp.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wpa_supplicant.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wpa_supplicant_open.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wpa_supplicant_tkip.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wpa_supplicant_wep128.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wpa_supplicant_wep64.conf ${D}${sysconfdir}/redpine
    install -m 0644 ${WORKDIR}/wps.conf ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_common_gpl.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_gpl.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_nongpl.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_wlan_gpl.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/onebox_wlan_nongpl.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_acl.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_ccmp.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_scan_sta.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_tkip.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_wep.ko ${D}${sysconfdir}/redpine
    install -m 0755 ${WORKDIR}/wlan_xauth.ko ${D}${sysconfdir}/redpine

    mkdir -p ${D}${sysconfdir}/redpine/certs
    install -m 0644 ${WORKDIR}/certs/* ${D}${sysconfdir}/redpine/certs
    install -m 0755 ${WORKDIR}/certs/bootstrap ${D}${sysconfdir}/redpine/certs

    mkdir -p ${D}${sysconfdir}/redpine/firmware
    install -m 0644 ${WORKDIR}/firmware/* ${D}${sysconfdir}/redpine/firmware

    mkdir -p ${D}${sysconfdir}/redpine/flash
    install -m 0644 ${WORKDIR}/flash/RS9113_RS8111_calib_values.txt ${D}${sysconfdir}/redpine/flash
    install -m 0644 ${WORKDIR}/flash/RSI_Config.txt ${D}${sysconfdir}/redpine/flash
    install -m 0644 ${WORKDIR}/flash/RSI_LastMac.txt ${D}${sysconfdir}/redpine/flash
    install -m 0644 ${WORKDIR}/flash/rsi_api_routine.c ${D}${sysconfdir}/redpine/flash
    install -m 0644 ${WORKDIR}/flash/rsi_api_routine.h ${D}${sysconfdir}/redpine/flash
    install -m 0644 ${WORKDIR}/flash/rsi_calib_flash.c ${D}${sysconfdir}/redpine/flash
    install -m 0755 ${WORKDIR}/flash/run_calib.sh ${D}${sysconfdir}/redpine/flash
    install -m 0755 ${WORKDIR}/flash/run_calib_wc.sh ${D}${sysconfdir}/redpine/flash

    mkdir -p ${D}${sysconfdir}/redpine/flash/WC
    install -m 0755 ${WORKDIR}/flash/WC/RS9113_WC_BL_0_5_hex_8 ${D}${sysconfdir}/redpine/flash/WC
    install -m 0755 ${WORKDIR}/flash/WC/convert.sh ${D}${sysconfdir}/redpine/flash/WC
    install -m 0644 ${WORKDIR}/flash/WC/dump_zero.txt ${D}${sysconfdir}/redpine/flash/WC
    install -m 0755 ${WORKDIR}/flash/WC/mbr_hex_dump ${D}${sysconfdir}/redpine/flash/WC
}

FILES_${PN} += "${base_libdir}"
