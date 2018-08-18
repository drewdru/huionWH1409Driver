#ifndef HUIONWH1409DDDEVICE_H
#define HUIONWH1409DDDEVICE_H


#include "../imports.h"

 struct HuionWH1409DDDevice {
    struct usb_device *udev;
	unsigned char *int_in_buffer;
    __u8 int_in_endpointAddr;
    struct urb *int_in_urb;
	int temperature;
 };


#endif // HUIONWH1409DDDEVICE_H