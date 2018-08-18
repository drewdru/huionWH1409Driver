#ifndef HUIONWH1409DDDRIVER_H
#define HUIONWH1409DDDRIVER_H


#define MODULE
#define LINUX
#define __KERNEL__

#include "imports.h"
#include "moduleInfo.h"
#include "moduleParams.h"
#include "device/UsbDriver.h"

static int __init huionWH1409DDDriver_init(void);
static void __exit huionWH1409DDDriver_exit(void);


#endif // HUIONWH1409DDDRIVER_H
