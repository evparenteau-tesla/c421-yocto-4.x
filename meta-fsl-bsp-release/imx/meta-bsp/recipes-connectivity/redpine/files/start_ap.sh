sh wlan_enable.sh
./onebox_util rpine0 create_vap wifi1 ap
#iwpriv wifi1 set_htconf 1
sleep 1
if [ "$1" == "" ]; then
	echo "please specify a config file"
	echo "example: sh start_ap.sh  wpa_supplicant_open.conf"
else
	./wpa_supplicant -i wifi1 -D bsd -c $1 -dddddt > wpa_log &
fi
