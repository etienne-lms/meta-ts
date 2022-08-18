################
Running a distro
################

Since the firmware provides a [UEFI]_ interface you are free to choose the
distro you prefer. However boards that embed the UEFI keys in the U-Boot binary
:ref:`UEFI Secure Boot storage requirements` will only be able to boot signed
binaries.  Look at :ref:`Building with your own certificates` if you want to
build and your own vertical distro and sign your binaries.  If you use the
precompiled firmware binaries you can test that with our LEDGE Reference Platform.

Download LEDGE-RP
*****************

Download a .wic.gz image from `here <https://snapshots.linaro.org/components/ledge/oe/ledge-multi-armv8/latest/>`_
extract and rename it


.. code-block:: bash

   unxz ledge-iot-ledge-qemuarm64-<date>.rootfs.wic.gz
   mv ledge-iot-ledge-qemuarm64-<date>.rootfs.wic ledge-iot.wic

Running LEDGE-RP
****************

Throughout the examples we will be using a USB disk.  You can prepare one with

.. code-block:: bash

    cat ledge-iot.wic > /dev/sdX

.. note::

   LEDGE RP will automatically encrypt your root filesystems if measured
   boot is enabled.  Since it also enables SELinux by default it will reboot
   once due to filesystem relabeling.  Be patient this only happens on 
   first boot.

   Before first boot you need to prepare the firmware EFI variables accordingly.
   You only need to interrupt the bootloader and issue the ``efidebug``
   commands once.

QEMU arm64
==========

QEMU can provide a TPM implementation via `Software TPM <https://github.com/stefanberger/swtpm>`_

[SWTPM]_ provides a memory mapped device which adheres to the
`TCG TPM Interface Specification <https://trustedcomputinggroup.org/wp-content/uploads/TCG_PCClientTPMInterfaceSpecification_TIS__1-3_27_03212013.pdf>`_

.. code-block:: bash

    sudo apt install swtpm

    mkdir /tmp/mytpm1 -p swtpm socket --tpmstate dir=/tmp/mytpm1 \
        --ctrl type=unixio,path=/tmp/mytpm1/swtpm-sock
        --log level=0 --tpm2 -t -d

.. code-block:: bash

    qemu-system-aarch64 -m 2048 -smp 2 -nographic -cpu cortex-a57 \
        -bios flash.bin -machine virt,secure=on \
        -drive id=os,if=none,file=ledge-iot.wic \
        -device virtio-blk-device,drive=os \
        -chardev socket,id=chrtpm,path=/tmp/mytpm1/swtpm-sock \
        -tpmdev emulator,id=tpm0,chardev=chrtpm \
        -device tpm-tis-device,tpmdev=tpm0

.. code-block:: bash

    => efidebug boot add -b 1 BootLedge virtio 0:1 efi/boot/bootaa64.efi -i virtio 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttyAMA0,115200 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60'
    => efidebug boot order 1
    => bootefi bootmgr


SynQuacer
=========

.. code-block:: bash

    => usb reset
    => efidebug boot add -b 1 BootLedge usb 0:1 efi/boot/bootaa64.efi -i usb 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttyAMA0,115200 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60'
    => efidebug boot order 1
    => bootefi bootmgr

stm32mp157c dk2 or ev1
======================

.. code-block:: bash

    => efidebug boot add -b 1 BootLedge usb 0:1 efi/boot/bootarm.efi -i usb 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttySTM0,115200 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60' 
    => efidebug boot order 1
    => bootefi bootmgr

rockpi4b
========

.. code-block:: bash

    => efidebug boot add -b 1 BootLedge usb 0:1 efi/boot/bootaa64.efi -i usb 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttyS2,1500000 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60'
    => efidebug boot order 1
    => bootefi bootmgr

Raspberry Pi4
=============

.. code-block:: bash

    => efidebug boot add -b 1 BootLedge usb 0:1 efi/boot/bootaa64.efi -i usb 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttyAMA0,115200 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60'
    => efidebug boot order 1
    => bootefi bootmgr

Xilinx KV260 AI Starter kit
===========================

.. code-block:: bash

    => efidebug boot add -b 1 BootLedge usb 0:1 efi/boot/bootaa64.efi -i usb 0:1 ledge-initramfs.rootfs.cpio.gz -s 'console=ttyPS1,115200 console=tty0 root=UUID=6091b3a4-ce08-3020-93a6-f755a22ef03b rootwait panic=60'
    => efidebug boot order 1
    => bootefi bootmgr
