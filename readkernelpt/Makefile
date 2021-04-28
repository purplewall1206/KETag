obj-m += readkernelpt.o
CFLAGS = -Wall -g -std=c99
# Set the path to the Kernel build utils.
KBUILD=/lib/modules/$(shell uname -r)/build/

FLAGS=-std=gnu99
 
modules:
	$(MAKE)  -C $(KBUILD) M=$(PWD) modules

clean:
	$(MAKE) -C $(KBUILD) M=$(PWD) clean

menuconfig:
	$(MAKE) -C $(KBUILD) M=$(PWD) menuconfig

ins:
	sudo dmesg -C
	sudo insmod readkernelpt.ko
	sudo rmmod readkernelpt
	sudo dmesg

.PHNOY:
	modules
	ins
