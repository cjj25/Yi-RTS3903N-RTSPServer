echo "############## Starting Firmware Dump ##############"

mkdir -p /tmp/sd/backup

cat /proc/mtd > /tmp/sd/backup/mtd.txt

dd if=/dev/mtdblock0 of=/tmp/sd/backup/mtdblock0.bin
dd if=/dev/mtdblock1 of=/tmp/sd/backup/mtdblock1.bin
dd if=/dev/mtdblock2 of=/tmp/sd/backup/mtdblock2.bin
dd if=/dev/mtdblock3 of=/tmp/sd/backup/mtdblock3.bin
dd if=/dev/mtdblock4 of=/tmp/sd/backup/mtdblock4.bin
dd if=/dev/mtdblock5 of=/tmp/sd/backup/mtdblock5.bin
dd if=/dev/mtdblock6 of=/tmp/sd/backup/mtdblock6.bin
dd if=/dev/mtdblock7 of=/tmp/sd/backup/mtdblock7.bin

if [ -e /tmp/sd/Factory ]; then
    mv /tmp/sd/Factory /tmp/sd/Factory.done
fi

reboot
