obj-m += stacktest.o
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
	sudo insmod stacktest.ko
	sudo rmmod stacktest
	sudo dmesg

.PHNOY:
	modules
	ins

	# 0xffffffff8260aff0 <init_top_pgt+4080>: 0x0000000000000000      0x000000000260f067