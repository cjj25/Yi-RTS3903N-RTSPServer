# A fix for firmware that doesn't include the config.sh executation in the init.sh script
# Credit to @rage2dev https://github.com/rage2dev/YiOutdoor
# Credit to @fkoteam and @lordhaer for bringing this to my attention
# https://github.com/TheCrypt0/yi-hack-v4/issues/29#issuecomment-894222953
# https://github.com/cjj25/yi-hack-telnet-root/issues/1

# The calling init script has already loaded the camera firmware
# Fork our script to run in the background
/tmp/sd/wifi/fork_process.sh 2>&1 &
# Kill all cloud related services
killall init.sh
killall watch_process
killall watchdog
killall log_server
killall dispatch
killall cloud
killall p2p_tnp
killall mp4record
killall oss
killall rmm
