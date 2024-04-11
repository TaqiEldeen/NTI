# Initramfs
>Source: Mastering Embedded Linux Programming 3rd edition

An initial RAM filesystem, or initramfs, is a compressed cpio archive. c*pio is an old
Unix archive format, similar to TAR and ZIP but easier to decode and so requiring less
code in the kernel*. You need to configure your kernel with CONFIG_BLK_DEV_INITRD
to support initramfs.

```bash
$ cd ~/rootfs
$ find . | cpio -H newc -ov --owner root:root > ../initramfs.cpio
$ cd ..
$ gzip initramfs.cpio
$ mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz
uRamdisk
```

## Booting with QEMU

```bash
$ QEMU_AUDIO_DRV=none \
qemu-system-arm -m 256M -nographic -M versatilepb \
-kernel zImage
-append "console=ttyAMA0 rdinit=/bin/sh" \
-dtb versatile-pb.dtb
-initrd initramfs.cpio.gz
```

or you can load initramfs from u-boot

1. open qemu running u-boot
2. load kernel, fdt, and initramfs (Make sure addresses not overlaping)
3. `bootz $kernel_addr_r $initramfs $fdt_addr_r`
