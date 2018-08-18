#ifndef BINDDEVICE_H
#define BINDDEVICE_H


#include "../imports.h"

#include "HuionWH1409DDDevice.h"
#include "urbInterrupt.h"

int huionWH1409DDDevice_probe(
        struct usb_interface *interface,
        const struct usb_device_id *id);

void huionWH1409DDDevice_disconnect(
        struct usb_interface *interface);


#endif // BINDDEVICE_H
