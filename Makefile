# CONFIG_MODULE_SIG=n # for error by samba:  Jul  3 12:19:54 smbsrv01 kernel: [16077.835470] huionWH1409Driver: module verification failed: signature and/or required key missing - tainting kernel
# # https://stackoverflow.com/questions/24975377/kvm-module-verification-failed-signature-and-or-required-key-missing-taintin/32194268#32194268

# WARN    := -W -Wall -Wstrict-prototypes -Wmissing-prototypes
# INCLUDE := -isystem /lib/modules/`uname -r`/build/include
# CFLAGS  := -O2 -DMODULE -D__KERNEL__ ${WARN} ${INCLUDE}
# CC      := gcc
# OBJS    := ${patsubst %.c, %.o, ${wildcard *.c}}

# all:
# 	make ${OBJS}
# .PHONY:
# 	clean
# clean:
# 	rm -rf *.o

KERNEL_PATH	:= /lib/modules/$(shell uname -r)/build

obj-m += huionWH1409DDDriver.o
huionWH1409DDDriver-objs	+= src/huionWH1409DDDriver.o
huionWH1409DDDriver-objs	+= src/device/bindDevice.o
huionWH1409DDDriver-objs	+= src/device/urbInterrupt.o

all:
	make -C $(KERNEL_PATH) M=$(PWD) modules

clean:
	make -C $(KERNEL_PATH) M=$(PWD) clean

# SOURCEDIR = src
# SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
# OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
# WARN    := -W -Wall -Wstrict-prototypes -Wmissing-prototypes
# INCLUDE := -isystem /lib/modules/`uname -r`/build/include
# FLAGS  := -O2 -DMODULE -D__KERNEL__ ${WARN} ${INCLUDE}
# CC      := g++

# all:                                                     
# 	$(CC) $(FLAGS) -o hello.o hello.cpp