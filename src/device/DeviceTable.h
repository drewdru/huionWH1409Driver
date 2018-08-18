#ifndef DEVICETABLE_H
#define DEVICETABLE_H


#include "../imports.h"

#define VENDOR_ID   0x256c
#define PRODUCT_ID  0x6e

/* table of devices that work with this driver */
const struct usb_device_id huionWH1409DDDevice_table[] = {
    { USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
    { },
}; 
MODULE_DEVICE_TABLE(usb, huionWH1409DDDevice_table); // identify a unique device


#endif // DEVICETABLE_H
