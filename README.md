# huionWH1409Driver 

Linux driver for Huion WH1409

## Unbind a device from a driver
Get device path id like "3-10.4:1.0" from sysfs
	
	cat /proc/bus/input/devices

usbhid path: /sys/bus/usb/drivers/usbhid

In order to unbind a device from a driver, simply write the bus id of the device to the unbind file:

    sudo sh -c 'echo -n "3-10.4:1.0" > /sys/bus/usb/drivers/usbhid/unbind'

## Build

	make
	insmod huionWH1409DDDriver.ko

## Get USB device specifications

	$ cat /proc/bus/input/devices
	$ lsusb
	$ find /dev/bus/
	$ sudo lsusb -D /dev/bus/usb/003/008 # Or just sudo lsusb -vvv
	
## Get device properties

	$ xinput --list
	$ xinput --list-props id



