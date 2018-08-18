#ifndef URBINTERRUPT_H
#define URBINTERRUPT_H


#include "../imports.h"

#include "HuionWH1409DDDevice.h"

struct measurement_packet {
	u8	measurements_in_packet;
	u8	rolling_counter;
	__le16	measurement0;
	__le16	measurement1;
	__le16	measurement2;
} __attribute__ ((packed));

void read_int_callback(struct urb *urb);


#endif // USBDRIVER_H