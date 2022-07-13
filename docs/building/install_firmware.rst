###################
Installing firmware
###################

If your hardware can boot of an SD-card meta-ts will generate a 
`WIC <https://www.yoctoproject.org/docs/2.4.2/dev-manual/dev-manual.html#creating-partitioned-images-using-wic>`_
image which you can ``dd`` to your target.  Otherwise the firmware must be
flashed in a board specific way.

Since the firmware provides a [UEFI]_ interface you are free to choose the
distro you prefer.

.. todo::
    Add TRS links for instructions

QEMU arm64
**********

QEMU just needs the build file containing all the firmware binaries.

.. note::

   Files needed from build directory **flash.bin**

SynQuacer
*********

The SynQuacer can't boot from an SD card.  You need to download and install the
firmware via ``xmodem``.  You can find detailed instructions
`here <https://www.96boards.org/documentation/enterprise/developerbox/installation/board-recovery.md.html#update-using-serial-flasher>`_

The short version is flip DSW2-7 to enable the serial flasher, open your 
minicom and use ``xmodem`` to send and update the files.

.. code-block:: bash

    flash write cm3 ->  Control-A S   (send scp_romramfw_release.bin)
    flash write arm-tf -> Control-A S (send fip_all_arm_tf_optee.bin)
    flash rawwrite 0x500000 0x100000  (Control-A S -> send optee/tee-pager_v2.bin)
    flash rawwrite 0x200000 0x100000  (Control-A S -> send u-boot.bin)


.. note::

   Files needed from build directory **scp_romramfw_release.bin**,
   **fip_all_arm_tf_optee.bin**, **optee/tee-pager_v2.bin**, **u-boot.bin**

stm32mp157c dk2 or ev1
**********************

.. code-block:: bash

    zcat ts-firmware-stm32mp157c-<ev1|dk2>.wic.gz > /dev/sdX

.. note::

   Files needed from build directory **ts-firmware-stm32mp157c-dk2.wic.gz** or
   **ts-firmware-stm32mp157c-ev1.wic.gz**

rockpi4b
********

.. code-block:: bash

   zcat ts-firmware-rockpi4b.rootfs.wic.gz > /dev/sdX

.. note::

   Files needed from build directory **ts-firmware-rockpi4b.rootfs.wic.gz**

Raspberry Pi4
*************

.. code-block:: bash

   zcat ts-firmware-rpi4.wic.gz > /dev/sdX

.. note::

   Files needed from build directory **ts-firmware-rpi4.wic.gz**

Xilinx KV260 AI Starter kit
***************************

This board uses an internal SPI flash.  You need to reset the board while 
pressing ``FWUEN`` switch.  This will launch an HTTP server at ``192.168.0.111``

Connect to the web Interface and update ImageA and ImageB

.. note::

   Files needed from build directory **ImageA.bin**, **ImageB.bin**

