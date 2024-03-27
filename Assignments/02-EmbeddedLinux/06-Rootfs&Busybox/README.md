# Busybox

> source: https://github.com/Gnurou/busybox

 BusyBox combines tiny versions of many common UNIX utilities into a single
  small executable.  It provides minimalist replacements for most of the
  utilities you usually find in bzip2, coreutils, dhcp, diffutils, e2fsprogs,
  file, findutils, gawk, grep, inetutils, less, modutils, net-tools, procps,
  sed, shadow, sysklogd, sysvinit, tar, util-linux, and vim.  The utilities
  in BusyBox often have fewer options than their full-featured cousins;
  however, the options that are included provide the expected functionality
  and behave very much like their larger counterparts.

  BusyBox has been written with size-optimization and limited resources in
  mind, both to produce small binaries and to reduce run-time memory usage.
  Busybox is also extremely modular so you can easily include or exclude
  commands (or features) at compile time.  This makes it easy to customize
  embedded systems; to create a working system, just add /dev, /etc, and a
  Linux kernel.  Busybox (usually together with uClibc) has also been used as
  a component of "thin client" desktop systems, live-CD distributions, rescue
  disks, installers, and so on.

  BusyBox provides a fairly complete POSIX environment for any small system,
  both embedded environments and more full featured systems concerned about
  space.  Busybox is slowly working towards implementing the full Single Unix
  Specification V3 (http://www.opengroup.org/onlinepubs/009695399/), but isn't
  there yet (and for size reasons will probably support at most UTF-8 for
  internationalization).  We are also interested in passing the Linux Test
  Project (http://ltp.sourceforge.net).


## Compile Busybox

``` bash
# export the compiler on the system
# chose the right compiler that corespond to your board
export CROSS_COMPILE=arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm

# Configure busybox to be static build from menuconfig
make menuconfig

#build the busybox to get the minimal command
make

# generate the rootfs
make install
# this will create folder name _install has all binary

```

## Making the rootfs for the virtual SD

1. You will need to copy all generated files from _install after building busybox

2. You will need to copy the generated files from your cross toolchain's sysroot

> Use rsync command to prevent any overwrite that may occure 

``` bash
rsync -a <toolchain_sysroot> <SD_rootfs>
```

**NOTE**: Create other directories such as dev, proc, sys, etc....

> Change the ownership of the rootfs directories to root:root

## Busybox Init process

> Source: https://www.halolinux.us/embedded-systems/busybox-init.html

Among the commands it supports by default, BusyBox provides init-like capabilities. As with the original mainstream init, BusyBox can handle the system's startup. BusyBox init is particularly well adapted to embedded systems, because it provides most of the init functionality an embedded system typically needs without dragging the weight of the extra features found in System V init. Also, because BusyBox is a single package, there is no need to keep track of an additional software package when developing or maintaining your system. There are cases, however, where BusyBox init may not be sufficient for your system. BusyBox init, for example, does not provide runlevel support.

Since I already described how to obtain, configure, and build BusyBox, I will limit this discussion to the setup of the init configuration files.

Because /sbin/init is a symbolic link to /bin/busybox, BusyBox is the first application to run on the target system. BusyBox identifies that the command being invoked is init and immediately jumps to the init routine.

The init routine of BusyBox carries out the following main tasks in order:

1. Sets up signal handlers for init.

2. Initializes the console(s).

3. Parses the inittab file, /etc/inittab.

4. Runs the system initialization script. /etc/init.d/rcS is the default for BusyBox.

5. Runs all the inittab commands that block (action type: wait).

6. Runs all the inittab commands that run only once (action type: once).

Once it has done this, the init routine loops forever carrying out the following tasks:

1. Runs all the inittab commands that have to be respawned (action type: respawn).

2. Runs all the inittab commands that have to be asked for first (action type: askfirst).

> If an /etc/inittab file is found, it is parsed and the commands. It contains are recorded inside internal structures to be carried out at the appropriate time

``` bash
#Each line in the inittab file follows this format:

id:runlevel:action:process
```

| Action | Effect|
| :------------: | :--------------: |
|    `sysinit`    |     `Provide init with the path to the initialization script.`     |
|    `respawn`    |     `Restart the process every time it terminates.`      |
|`askfirst`|`Similar to respawn, but is mainly useful for reducing the number of terminal applications running on the system. It prompts init to display "Please press Enter to activate this console." at the console and wait for the user to press Enter before restarting the process.`|
|`wait`|`Tell init that it has to wait for the process to complete before continuing.`|
|`once`|`Run process only once without waiting for them.`|
|`ctrlaltdel`|`Run process when the Ctrl-Alt-Delete key combination is pressed.`|
|`shutdown`|`Run process when the system is shutting down.`|
|`restart`|`Run process when init restarts. Usually, the process to be run here is init itself.`|


# The kernel command line

The kernel command line is a string that is passed to the kernel by the bootloader, via the
bootargs variable in the case of U-Boot; it can also be defined in the device tree or set as
part of the kernel configuration in CONFIG_CMDLINE.


## Uboot kernel command line
Uboot passes bootargs variable to the kernel 

``` bash
setenv bootargs=console=tty0 console=ttyAMA0,38400n8 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=sbin/init
```


## Pseudo filesystem
Linux makes system & kernel information availble in user space through pseudo filesytem (Virtual filesystem)

- Pseudo filesystems allow apps to see directories and files that do not exist on any real storage **They are created and updated on the fly by the kernel**

- Most important pseudo filesystems
- - Proc: OS related info `mounted on /proc`
- - sysfs: Representation of the system as a tree of devices `mounted on /sys`


### Making use of busybox init

since busybox init will us `inittab` file as configuration, we can add the following:

```bash
::sysinit:/etc/init.d/rcS
ttyAMA0::askfirst:/bin/sh
```
> This will indicate the rcS file location and the shell 


Now in the rcS script mount the Pseudo filesystem 
``` bash
#!/bin/sh

mount -t proc comment /proc
mount -t sysfs comment /sys
```

