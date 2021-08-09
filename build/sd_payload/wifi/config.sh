# A fix for firmware that doesn't include the config.sh executation in the init.sh script
# Credit to @rage2dev https://github.com/rage2dev/YiOutdoor
# Credit to @fkoteam and @lordhaer for bringing this to my attention
# https://github.com/TheCrypt0/yi-hack-v4/issues/29#issuecomment-894222953
# https://github.com/cjj25/yi-hack-telnet-root/issues/1

# The calling init script has already loaded the camera firmware
kill_cloud () {
	# Kill all cloud related services
	killall watch_process
	killall watchdog
	killall log_server
	killall cloud
	killall p2p_tnp
	killall mp4record
	killall oss
	killall rmm
	killall arp_test
}
# Check if we've made a backup of this device
if [ ! -f /var/tmp/sd/backup/mtdblock0.bin  ]; then
     /var/tmp/sd/wifi/make_backup.sh 2>&1 &
     kill_cloud
fi

# Fork our script to run in the background
/var/tmp/sd/wifi/fork_process.sh 2>&1 &
kill_cloud

# Allow PTZ to finish its cyle
sleep 30s
killall dispatch
killall init.sh
