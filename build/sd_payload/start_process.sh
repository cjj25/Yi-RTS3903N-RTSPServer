busybox telnetd &&

export LD_LIBRARY_PATH=/lib:/home/lib:/home/rt/lib:/home/app/locallib:/var/tmp/sd/lib
echo -n "/home/lib/sc2230/isp_jin.fw" > /sys/devices/platform/rts_soc_camera/loadfw

wpa_supplicant -c/var/tmp/sd/Factory/wpa_supplicant.conf -g/tmp/wpa_supplicant-global -Dwext -iwlan0 -B
sleep 1s
udhcpc -i wlan0 -b -s /backup/script/default.script

/home/app/load_cpld_ssp
killall log_server
cd /var/tmp/sd/
if test -f "/var/tmp/sd/invert_adc"; then
    ./stream 1 &
else
    ./stream &
fi

./rRTSPServer -d &
