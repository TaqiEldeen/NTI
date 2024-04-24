obj-m   = chardevice.o
BDIR 	= /lib/modules/$(shell uname -r)/build	# Kernel build directory

all:
# Compile the module using the kernel build directory (-c option specifies the kernel build directory)
	make -C ${BDIR} M=$(PWD) modules	
clean:
# Clean the module using the kernel build directory (-c option specifies the kernel build directory)
	make -C ${BDIR} M=$(PWD) clean	




	