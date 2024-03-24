# Linux Kernel

The Linux kernel is the core component of the Linux operating system, responsible for managing system resources such as memory, processes, input/output (I/O), and device drivers. It is an open-source software project that was initially developed by Linus Torvalds in 1991 and is now maintained by a large community of developers around the world.


``` bash
# Clone the Linux Kernel
git clone https://github.com/torvalds/linux.git --depth=1

#configure the kernel to vexpress
make ARCH=arm CROSS_COMPILE=<Yours> vexpress_defconfig

# To indentify your kernel version 
make ARCH=arm ROSS_COMPILE=<Yours> 
kernelversion

#configure the kernel with the configuration discuss above
make menuconfig

#build the kernel
make -j4 zImage modules dtbs

```
> Output will be in arch/arm/boot 

**NOTE:** Kernel Will Panic since you didnt create the rootfs

## Configure Kernel

For all the next board this configuration must be checked

- [ ] Enable **devtmpfs**
- [ ] Change kernel compression to **XZ**
- [ ] Change your kernel local version to your name and append on it **yourName**-v1.0