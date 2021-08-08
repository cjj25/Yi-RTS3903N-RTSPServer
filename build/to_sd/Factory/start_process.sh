export LD_LIBRARY_PATH=/lib:/home/lib:/home/rt/lib:/home/app/locallib:/var/tmp/sd/lib

# Use original sensor detect code from Yi

#echo -n "/home/lib/sc2230/isp_jin.fw" > /sys/devices/platform/rts_soc_camera/loadfw
#multi sensor compatible
########################################################################
try_count=3
echo 1 > /sys/devices/platform/rts_soc_camera/loadfw
echo 2 > /sys/devices/platform/rts_soc_camera/loadfw
sensor_id=
#try 3 times
while ([ -z "$sensor_id" ] && [ $try_count -ge 0 ])
do
let try_count--
sensor_id=$(cat /sys/devices/platform/rts_soc_camera/sensor)
done

if [ -z "$sensor_id" ]
####old version, use system/lib/isp.fw
then
	echo -e "use default isp.fw=============== \n"
	echo 1 > /sys/devices/platform/rts_soc_camera/loadfw
else
####new version,load conrrespond isp.fw depend on sensor_id
	echo -e "Sensor ===============  $sensor_id\n"
	if [ "$sensor_id" == "SC1245" ]
	then
		echo -n "/home/lib/sc1245/isp.fw" > /sys/devices/platform/rts_soc_camera/loadfw
	elif [ "$sensor_id" == "SC2235" ]
	then
		echo -n "/home/lib/sc2235/isp.fw" > /sys/devices/platform/rts_soc_camera/loadfw
	elif [ "$sensor_id" == "SC2230" ]
	then
		echo -n "/home/lib/sc2230/isp_jin.fw" > /sys/devices/platform/rts_soc_camera/loadfw
	fi
fi
#######################################################################

# Check if telnet is running (older firmware already has it enabled)
ps | grep -v grep | grep telnetd > /dev/null
result=$?

if [ "${result}" -eq "0" ] ; then
    echo "Telnet already running"
else
    echo "Telnet not running... starting up"
    busybox telnetd &
fi

DEFAULT_SCRIPT=/backup/script/default.script 
if [ -f /home/app/script/default.script ]; then
    DEFAULT_SCRIPT=/home/app/script/default.script
fi

wpa_supplicant -c/var/tmp/sd/Factory/wpa_supplicant.conf -g/var/tmp/wpa_supplicant-global -Dwext -iwlan0 -B
sleep 3s


udhcpc -i wlan0 -b -s "${DEFAULT_SCRIPT}"
sleep 10s
cd /var/tmp/sd/


# Try load the load_cpld_ssp used in newer firmware to assist with IR CUT

rm -rf /var/tmp/sd/localko
cp -R /home/app/localko .
mkdir -p /home/app/localko # If it fails

cp /var/tmp/sd/Yi/ko/* /home/app/localko
mount --bind /var/tmp/sd/localko /home/app/localko
/var/tmp/sd/Yi/load_cpld_ssp

if test -f "/tmp/sd/invert_adc"; then
    ./stream 1 2>&1 &
else
    ./stream 2>&1 &
fi
./rRTSPServer -d >/var/tmp/sd/rtspServerLog 2>&1

