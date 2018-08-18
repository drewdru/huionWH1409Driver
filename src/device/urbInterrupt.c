#include "urbInterrupt.h"

void read_int_callback(struct urb *urb)
{
	struct HuionWH1409DDDevice *gdev = urb->context;
	unsigned char *data = urb->transfer_buffer;
	struct measurement_packet *measurement = urb->transfer_buffer;
	int retval = -ENOMEM;
	int i = 0;
    bool isSucces = true;

	switch (urb->status) {
	case 0:
		/* success */
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this urb is terminated, clean up */
		printk(KERN_ALERT "%s - urb shutting down with status: %d",
		    __func__, urb->status);
		return;
	default:
		printk(KERN_ALERT "%s - nonzero urb status received: %d",
		    __func__, urb->status);
		// goto exit;
        isSucces = false;
	}
    if (isSucces) {
        dev_info(&urb->dev->dev, "int read data: ");
        for (i = 0; i < urb->actual_length; ++i)
            printk("%02x ", data[i]);
        printk("\n");

        dev_dbg(&urb->dev->dev, "counter %d, temperature=%d\n",
            measurement->rolling_counter,
            measurement->measurement0);
        gdev->temperature = le16_to_cpu(measurement->measurement0);
    }
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval) {
		dev_err(&urb->dev->dev,
			"%s - Error %d submitting interrupt urb\n",
			__func__, retval);
    }
}