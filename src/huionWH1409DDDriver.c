/*  huionWH1409Driver.c - The kernel module: 
 *      Driver for Huion WH1409 graphic tablet keyboard.
 *  
 */

#include "huionWH1409DDDriver.h"

int huionWH1409DDDriver_init(void)
{
    // printk(KERN_ALERT "Hello, new World!\n");
    // // printk(KERN_ALERT "myshort is a short integer: %hd\n", myshort);
    // // printk(KERN_ALERT "myint is an integer: %d\n", myint);
    // // printk(KERN_ALERT "mylong is a long integer: %ld\n", mylong);
    // // printk(KERN_ALERT "mystring is a string: %s\n", mystring);
    // return 0;
    int retval = 0;
	retval = usb_register(&huionWH1409DDDevice_driver);
	if (retval)
		printk(KERN_ALERT "usb_register failed. Error number %d", retval);
	return retval;
}

void huionWH1409DDDriver_exit(void)
{
    // printk(KERN_ALERT "Goodbye, cruel World!\n");
    usb_deregister(&huionWH1409DDDevice_driver);
}  

module_init(huionWH1409DDDriver_init);
module_exit(huionWH1409DDDriver_exit);
