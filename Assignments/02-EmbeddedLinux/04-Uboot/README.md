# U-Boot
U-Boot, or to give its full name, Das U-Boot, began life as an open source
bootloader for embedded PowerPC boards. Then, it was ported to ARM-based
boards and later to other architectures, including MIPS and SH. It is hosted and
maintained by Denx Software Engineering. There is plenty of information
available, and a good place to start is http://www.denx.de/wiki/U-Boot.


## 1- Installing U-Boot
> Refer to the official docs: https://docs.u-boot.org/en/latest/build/gcc.html

``` bash
ls configs/     # List Available pre configured targets

# Apply your configuration
make ARCH=<target_arch> CROSS_COMPILE=<your_cross_toolchain> <pre_configuration>    

# Open menuconfig to further customize your bootloader
make ARCH=<target_arch> CROSS_COMPILE=<your_cross_toolchain> menuconfig

# Build U-Boot

make ARCH=<target_arch> CROSS_COMPILE=<your_cross_toolchain> 
```

The results of the compilation are:

- **u-boot**: U-Boot in ELF object format, suitable for use with a debugger

- **u-boot.map**: The symbol table

- **u-boot.bin**: U-Boot in raw binary format, suitable for running on your device

- **u-boot.img**: This is u-boot.bin with a U-Boot header added, suitable for
uploading to a running copy of U-Boot

- **u-boot.srec**: U-Boot in Motorola S-record (SRECORD or SRE) format,
suitable for transferring over a serial connection


## 2- Using U-Boot

U-Boot uses environment variables to tailor its operation. The environment variables configure
settings such as the baud rate of the serial connection, the seconds to wait before auto boot, the
default boot command, and so on.

The factory default variables and their values also are stored in the U-Boot binary image itself. In
this way, you can recover the variables and their values at any time with the **envreset** command.

### A- Usefull Commands

- **setenv** & **printenv**
``` bash
setenv myEnv 12345
printenv myEnv
# myEnv=12345

```
> You can use ${env_var} to expand the variable
``` bash
setenv myNumber 123456
setenv var This is my number: ${myNumber}
printenv var
# var=This is my number: 123456
```

Recursive variables (or scripts) contain one or more variables within their own value. The inner
variables are not expanded in the new variable. Instead, they are expanded when the recursive
variable is run as a command

``` bash
setenv dumpaddr md.b \${addr} \${bytes}
printenv dumpaddr
# dumpaddr=md.b ${addr} ${bytes}
setenv addr 2C000
setenv bytes 5
run dumpaddr
0002c000: 00 00 00 00 00 .....
```

> You must use the back slash '\\' before '$' to prevent variables from being expanded into other
variables’ values


- **run** command:

Create an environment variable called cmd1 which contain multiple commands
``` bash
setenv cmd1 "setenv var 123; printenv var; saveenv"
# OR: setenv cmd1 setenv var 123\; printenv var\; saveenv
# Both is the same


run cmd1 
# var=123
# Saving Environment to FAT... OK
```

- **fatload** command:

To read an image from an MMC card formatted in FAT

``` bash
fatload mmc <dev>[:partition] <loadAddress> <bootfilename>

# In our example we used vexpress target
fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
```

- **bootz** command:

This command will boot the kernel and fdt after loading it using **fatload command**

``` bash
# This will load boot the kernel and Flattened Device Tree
bootz $kernel_addr_r - $fdt_addr_r
```
---

### B- Common System Variables

- **bootcmd**: Defines a command string that is automatically executed when the
initial countdown is not interrupted.
Executed only when the bootdelay variable is also defined.

- **bootdelay**: Seconds to wait before running the automatic boot process in
bootcmd.



# Bootscript
The bootscript is an script that is automatically executed when the boot loader starts, and before
the OS auto boot process.
The bootscript allows the user to execute a set of predefined U-Boot commands automatically
before proceeding with normal OS boot. This is especially useful for production environments and
targets which don’t have an available serial port for showing the U-Boot monitor


## Bootscript process
he bootscript works in the following way:
1. U-Boot checks the variable loadbootsc. If set to “no”, it continues normal execution.
2. If the variable loadbootsc is set to “yes” (factory default value) U-Boot tries to download
the bootscript file with the filename stored in variable bootscript from the TFTP server IP
address defined at variable serverip (by default 192.168.42.1).
The default value of the bootscript variable is **platformname**-bootscript.
3. If the bootscript file is successfully downloaded, it is executed.
4. If any of the commands in the bootscript fails, the rest of script is cancelled.
5. When the bootscript has been fully executed (or cancelled) U-Boot continues normal
execution.


``` bash
# mkimage is in tools directory
mkimage -T script -n "Bootscript" -C none -d <input_file> <output_file>
```

# QEMU

To use QEMU with Uboot you will need to make and mount virtual SD-Card

``` bash
# Create a file with 1 GB filled with zeros
dd if=/dev/zero of=sd.img bs=1M count=1024

# To show where your sd card is mounted
lsblk 

# for the VIRTUAL SD card
cfdisk sd.img
```

| Partition Size | Partition Format | Bootable  |
| :------------: | :--------------: | :-------: |
|    `200 MB`    |     `FAT 16`     | ***Yes*** |
|    `300 MB`    |     `Linux`      | ***No***  |

``` bash
# attach the sd.img to be treated as block storage
sudo losetup -f --show --partscan sd.img

# Formating the first partition as FAT (This is only done single time)
sudo mkfs.vfat -F 16 -n boot /dev/loopxxp1

# format the created partition by ext4 (This is only done single time)
sudo mkfs.ext4 -L rootfs /dev/loopxxp2

```
---
Now to start QEMU with your Uboot and Virtual SD

``` bash
qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel u-boot/u-boot \
-sd sd.img
```

## U-boot and TFTP

- Trivial File Transfer Protocol
-  Somewhat similar to FTP, but without authentication and over UDP

``` bash
sudo apt install tftpd-hpa
```

> All files in /srv/tftp is exposed by default to TFTP

- You can edit this default location in the config file of the tftp which is in **/etc/default/tftpd-hpa**

- You will need also to change the ownership of the **/srv/tftp** directory to **tftp:tftp** to make this service user able to access it

- Also change TFTP_OPTIONS="--secure --create"

### Uboot environment for TFTP

#### Prerequisit
``` bash
#Switch to root
sudo su
#Make sure you are connected to internet
ping google.com
#Download tftp protocol
sudo apt-get install tftpd-hpa
#Check the tftp ip address
ip addr `will be needed`
#Change the configuration of tftp
nano /etc/default/tftpd-hpa
	#write inside the file
    tftf_option = “--secure –-create”
#Restart the protocal
Systemctl restart tftpd-hpa
#Make sure the tftp protocol is running
Systemctl status tftpd-hpa
#Change the file owner
cd /srv
chown tftp:tftp tftp 
#Move your image or file to the server
cp [File name] /srv/tftp
```

1. First when running in QEMU we will need to create a virtual interface *tap* to be able to use the physicalinterface of the machine.

``` bash
# This command will run the next script to make virtual interface to be used in QEMU

sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic \
-kernel ~/u-boot/u-boot \
-sd sd.img \
-net tap,script=./qemu-ifup -net nic'   
```


``` bash
# This script will make a tap and assign it IP
#!/bin/sh
ip a add 192.168.0.1/24 dev $1
ip link set $1 up

```

2. Uboot variables

``` bash
# Assign IP for the QEMU (UBOOT) and assign the server (tap)
setenv ipaddr 192.168.0.5; setenv serverip 192.168.0.1

# Load using TFTP
tftp 0x60100000 zImage; tftp 0x60000000 vexpress-v2p-ca9.dtb
```

3. Boot the KERNEL

```bash
bootz $kernel_addr_r - $fdt_addr_r
```


## Useful variables 

``` bash
LoadTFTP=echo Loading From TFTP; setenv ipaddr 192.168.0.5; setenv serverip 192.168.0.1; run FATLOAD_TFTP

FATLOAD_TFTP=tftp $kernel_addr_r zImage; tftp $fdt_addr_r vexpress-v2p-ca9.dtb


LoadSD=if mmc dev; then run FATLOAD_SD; else echo SD Not Found; fi

FATLOAD_SD=fatload mmc 0:1 $kernel_addr_r zimage; fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb


KERNEL_RUN=bootz $kernel_addr_r - $fdt_addr_r

```