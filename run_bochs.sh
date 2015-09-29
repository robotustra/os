#!/bin/bash

# run_bochs.sh
# mounts the correct loopback device, runs bochs, then unmounts.

sudo /sbin/losetup /dev/loop0 floppy.img
sudo chmod o+rw /dev/loop0
sleep 1
bochs -f bochsrc.txt
#sudo /sbin/losetup -d /dev/loop0
