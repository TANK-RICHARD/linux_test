obj-m += gpio.o

KDIR = /lib/modules/$(shell uname -r)/build
ENV := ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

all:
	make $(ENV) -C $(KDIR) M=$(shell pwd) modules

clean:
	make $(ENV) -C $(KDIR) M=$(shell pwd) clean

