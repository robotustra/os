#!/bin/bash

sudo losetup /dev/loop0 floppy.img
sudo mount /dev/loop0 /mnt
sleep 1
sudo chmod o+rw /dev/loop0
sleep 1
sudo cp kernel /mnt/kernel
sleep 1
sudo umount /dev/loop0
sleep 1
sudo losetup -d /dev/loop0
