#ifndef MODULEPARAMS_H
#define MODULEPARAMS_H


#include <linux/moduleparam.h>
#include <linux/stat.h>

#include "imports.h"

// static short int myshort = 1;
// static int myint = 420;
// static long int mylong = 9999;
// static char *mystring = "blah";

// module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
// MODULE_PARM_DESC(myshort, "A short integer");

// module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// MODULE_PARM_DESC(myint, "An integer");

// module_param(mylong, long, S_IRUSR);
// MODULE_PARM_DESC(mylong, "A long integer");

// module_param(mystring, charp, 0000);
// MODULE_PARM_DESC(mystring, "A character string");


#endif // MODULEPARAMS_H