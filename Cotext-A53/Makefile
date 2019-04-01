

# Makefile for hellomodule.c

KDIR:= /home/fsa53/kernel-3.4.39
obj-m:= hellomodule.o
MDIR:= $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(MDIR) modules
	cp -f ./hellomodule.ko /nfsroot/rootfs/home/
	
clean:
	rm -rf  *.o  *.ko  *.mod.c   Module*  modules*

