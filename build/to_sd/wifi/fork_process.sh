export LD_LIBRARY_PATH=/lib:/home/lib:/home/rt/lib:/home/app/locallib:/var/tmp/sd/lib

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

if [ -f /var/tmp/sd/Factory/wpa_supplicant.conf ]; then
    wpa_supplicant -c/var/tmp/sd/Factory/wpa_supplicant.conf -g/var/tmp/wpa_supplicant-global -Dwext -iwlan0 -B
    sleep 3s
fi


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

