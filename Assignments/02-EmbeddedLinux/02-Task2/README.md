# Cross toolchains using crosstool-ng

### Installing

```bash
# 1- Clone the crosstool-ng repo

# 2- Checkout to the version needed

# 3- bootstrap
./bootsrap

# 4- configure with local directory
./configure --enable-local

# 5- build 
make
sudo make install

```

### Using the crosstool-ng

```bash
# Get available preconfigured samples
./ct-ng list-samples

# See what is configured
./ct-ng show-<sample_you_chosed>

# Edit configuration (menu is based on Linux Kernel menu config)
./ct-ng menuconfig

# After configuring, build the toolchain
./ct-ng build

```

### Notes
> The toolchain will be in x-tools directory in your home folder.

Naming convention for toolchains based on GNU is:

CPU-VENDOR-KERNEL-OS

- mipsel-unknown-linux-gnu
- arm-cortex_a8-linux-gnueabihf

> EABI: Extended Application Binary Interface

> HF: Hard-Float (Use hardware FPU)