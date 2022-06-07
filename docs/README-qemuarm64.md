QEMU AARCH64
============

Build
-----

To build trusted substrate firmware for rockpi4b issue the following commands.

```
$ pip install kas
$ git clone https://git.codelinaro.org/linaro/dependable-boot/meta-ts.git
$ cd meta-ts
$ kas build ci/qemuarm64-secureboot.yml
```

Upon a sucessful build a wic image that can be flashed to the SD card can be
found at meta-ts/build/tmp/deploy/images/tsqemuarm64-secureboot/ts-firmware-tsqemuarm64-secureboot.wic.gz

Run
---

1. Download LEDGE RP
http://releases.linaro.org/components/ledge/rp-0.3/ledge-multi-armv8/ledge-qemuarm64/ledge-gateway-ledge-qemuarm64-20211202114859.rootfs.wic.gz
gunzip ledge-gateway-ledge-qemuarm64-20211202114859.rootfs.wic.gz

2a. QEMU without TPM support
qemu-system-aarch64 -m 2048 -smp 8  -nographic -cpu cortex-a57 \
    -bios ts-firmware-tsqemuarm64-secureboot.wic -machine virt,secure=on \
    -drive id=os,if=none,file=ledge-iot-ledge-qemuarm64.rootfs.wic \
    -device virtio-blk-device,drive=os

2b. QEMU with TPM support
*NOTE* with TPM support enabled your filesystem will be encrypted on first boot

mkdir /tmp/mytpm1 -p
swtpm socket --tpmstate dir=/tmp/mytpm1 \
    --ctrl type=unixio,path=/tmp/mytpm1/swtpm-sock \
    --log level=0 --tpm2 -t -d

qemu-system-aarch64 -m 2048 -smp 2 -nographic -cpu cortex-a57 \
    -bios ts-firmware-tsqemuarm64-secureboot.wic -machine virt,secure=on  \
    -drive id=os,if=none,file=ledge-iot-ledge-qemuarm64.rootfs.wic \
    -device virtio-blk-device,drive=os \
    -chardev socket,id=chrtpm,path=/tmp/mytpm1/swtpm-sock \
    -tpmdev emulator,id=tpm0,chardev=chrtpm \
    -device tpm-tis-device,tpmdev=tpm0

3. On U-boot's console
efidebug boot add -b 1 BootLedge virtio 0:1 efi/boot/bootaa64.efi -i virtio 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttyAMA0,115200 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60'
efidebug boot order 1
bootefi bootmgr (or reboot)
