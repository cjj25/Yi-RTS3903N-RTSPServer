# Start our bespoke script
/var/tmp/sd/Factory/start_process.sh 2>&1 &

# Kill the original calling script from Yi
killall init.sh