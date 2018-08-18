#ifndef USBDRIVER_H
#define USBDRIVER_H


#include "../imports.h"

#include "bindDevice.h"
#include "DeviceTable.h"

static struct usb_driver huionWH1409DDDevice_driver = {
    .name =       "huionWH1409DDDevice",
    .probe =      huionWH1409DDDevice_probe,
    .disconnect = huionWH1409DDDevice_disconnect,
    .id_table =   huionWH1409DDDevice_table,
};


#endif // USBDRIVER_H