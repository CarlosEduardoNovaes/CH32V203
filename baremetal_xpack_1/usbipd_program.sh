#!/bin/bash

usbipd.exe list
read -p "Enter the busid of the USB device to attach: " usb_busid

echo $usb_busid

sudo usbipd.exe bind --busid $usb_busid
sudo usbipd.exe attach --wsl --busid $usb_busid
