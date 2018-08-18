#include "bindDevice.h"

static ssize_t show_temp(
        struct device *dev, 
        struct device_attribute *attr,
        char *buf)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct HuionWH1409DDDevice *gdev = usb_get_intfdata(intf);
    printk(KERN_ALERT "%d\n", gdev->temperature);
	return sprintf(buf, "%d\n", gdev->temperature);
} // registering as dev_attr_temperature
static DEVICE_ATTR(temperature, S_IRUGO, show_temp, NULL);


static void clean_huionWH1409DDDevice(
    struct usb_interface *interface,
    struct HuionWH1409DDDevice *gdev)
{
    usb_set_intfdata(interface, NULL);
    if (gdev) {
        usb_free_urb(gdev->int_in_urb);
    }
    kfree(gdev);
}

static int set_control_endpoint(
    struct usb_interface *interface,
    struct HuionWH1409DDDevice *gdev,
    struct usb_endpoint_descriptor *endpoint,
    size_t *buffer_size)
{
    int i = 0;
	struct usb_host_interface *iface_desc;
    /* find the one control endpoint of this device */
	iface_desc = interface->cur_altsetting;
	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (usb_endpoint_is_int_in(endpoint)) {
			buffer_size = le16_to_cpu(endpoint->wMaxPacketSize);
			gdev->int_in_endpointAddr = endpoint->bEndpointAddress;
			gdev->int_in_buffer = kmalloc(buffer_size, GFP_KERNEL);
			if (!gdev->int_in_buffer) {
                printk(KERN_ALERT, "Could not allocate buffer?\n");
				dev_err(&interface->dev, "Could not allocate buffer");
                return -ENOMEM;
			}
			break;
		}
	}
    if (!gdev->int_in_endpointAddr) {
        printk(KERN_ALERT, "Could not find int-in endpoint?\n");
		dev_err(&interface->dev, "Could not find int-in endpoint");
        return -ENODEV;
	}
    return 0;
}

int huionWH1409DDDevice_probe(
        struct usb_interface *interface,
        const struct usb_device_id *id)
{
    int retval = -ENOMEM;
    size_t buffer_size = 0;
    struct usb_device *udev = interface_to_usbdev(interface);
    struct HuionWH1409DDDevice *gdev = NULL;
    struct usb_endpoint_descriptor *endpoint = NULL;
    gdev = kmalloc(sizeof(struct HuionWH1409DDDevice), GFP_KERNEL);
    if (gdev == NULL) {
        printk(KERN_ALERT, "Out of memory\n");
        dev_err(&interface->dev, "Out of memory\n");
        clean_huionWH1409DDDevice(interface, gdev);
        return retval;
    }
    // memset(gdev, 0x00, sizeof(*gdev));
    gdev->udev = usb_get_dev(udev);
    retval = set_control_endpoint(interface, gdev, endpoint, &buffer_size);
    if (retval) {
        printk(KERN_ALERT, "WTF?\n");
        dev_err(&interface->dev, "WTF?\n");
        clean_huionWH1409DDDevice(interface, gdev);
        return retval;
    }
    gdev->int_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!gdev->int_in_urb) {
        printk(KERN_ALERT, "No free urbs available\n");
		dev_err(&interface->dev, "No free urbs available\n");
        clean_huionWH1409DDDevice(interface, gdev);
        return -ENOMEM;
	}
    usb_fill_int_urb(
        gdev->int_in_urb,
        udev,
        usb_rcvintpipe(udev, endpoint->bEndpointAddress),
        gdev->int_in_buffer,
        buffer_size,
        read_int_callback,
        gdev,
        endpoint->bInterval);
    usb_set_intfdata(interface, gdev);
    // device_create_file(&interface->dev, &dev_attr_temperature);
    retval = usb_submit_urb(gdev->int_in_urb, GFP_KERNEL);
	if (retval) {
        printk(KERN_ALERT, "Error submitting interrupt urb\n");
		dev_err(&gdev->udev->dev,
			"%s - Error %d submitting interrupt urb\n",
			__func__, retval);
        clean_huionWH1409DDDevice(interface, gdev);
        return retval;
    }
    // retval = device_create_file(&interface->dev, &dev_attr_temperature);
	// if (retval) {
    //     clean_huionWH1409DDDevice(interface, gdev);
    //     return retval;
    // }

    dev_info(&interface->dev, "USB huionWH1409DDDevice now attached\n");
    printk(KERN_ALERT, "USB huionWH1409DDDevice now attached\n");

    return 0;
}
 

void huionWH1409DDDevice_disconnect(
        struct usb_interface *interface)
{
    struct HuionWH1409DDDevice *gdev;
    gdev = usb_get_intfdata(interface);
    usb_set_intfdata(interface, NULL);
    // device_remove_file(&interface->dev, &dev_attr_temperature);
    usb_put_dev(gdev->udev);
    usb_kill_urb(gdev->int_in_urb);
	usb_free_urb(gdev->int_in_urb);
	kfree(gdev->int_in_buffer);
    kfree(gdev);

    dev_info(&interface->dev, "USB huionWH1409DDDevice now disconnected\n");
}

