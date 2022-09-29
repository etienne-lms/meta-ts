###################
Supported Platforms
###################

Trusted Substrate supports a variety of armv8 and armv7 boards.  It's important
to understand that the hardware characteristics dictate the supported features
as well as the level of the device security

Software Components
*******************

Generally the following software components are used to boot up the boards
and setup the chain of trust

- `U-Boot <https://source.denx.de/u-boot/u-boot>`_
- `OP-TEE <https://github.com/OP-TEE>`_
- `TF-A <https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git/>`_
- `firmware TPM <https://github.com/microsoft/ms-tpm-20-ref>`_
- `StandAloneMM from EDK2 <https://github.com/tianocore/edk2-platforms.git>`_
- `SCP <https://github.com/ARM-software/SCP-firmware>`_

A high level overview of the boot chain looks will look like this

.. uml::

    object BL2 {
        U-Boot SPL
	    or
        TF-A BL2
    }
    object BL31 {
        Secure Monitor
    }
    object BL32 {
        OP-TEE
	    fTPM
	    StandAloneMM
    }
    object BL33 {
	    U-Boot
    }
    object OS {
        OS with UEFI
    }
    
    BL2 --> BL31
    BL2 --> BL32
    BL2 --> BL33
    BL33--> OS : UEFI Secure and Measured Boot

Board Support
=============

* QEMU (arm64)
* `SynQuacer DeveloperBox <https://www.96boards.org/product/developerbox/>`_
* `stm32mp157c-dk2 <https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html>`_
* `stm32mp157c-ev1 <https://www.st.com/en/evaluation-tools/stm32mp157c-ev1.html>`_
* `Rockpi4 <https://rockpi.org/rockpi4>`_
* `Raspberry Pi4 <https://www.raspberrypi.com/products/raspberry-pi-4-model-b/specifications/>`_
* `Xilinx kv260 starter kit <https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit.html>`_
* `Xilinx kv260 commercial <https://www.xilinx.com/products/som/kria/k26c-commercial.html>`_

Supported platform features
===========================

======================== ============  =================== ======================== ===========
Board                    FSBL          Secure Boot         Measured Boot            A/B updates
======================== ============  =================== ======================== ===========
QEMU                     TF-A          Yes (Built-in vars) Yes                      No
DeveloperBox             SCP + TF-A    Yes (RPMB vars)     Yes [fTPM]_              WIP
stm32mp157c-dk2          TF-A          Yes (Built-in vars) No                       WIP
stm32mp157c-ev1          TF-A          Yes (RPMB vars)     No                       WIP
Rockpi4                  U-Boot SPL    Yes (RPMB vars)     Yes [fTPM]_              No
Raspberry Pi4            Proprietary   Yes (Built-in vars) Yes (needs SPI TPM)      No
Xilinx kv260 starter kit U-Boot SPL    Yes (Built-in vars) Yes                      WIP
Xilinx kv260 commercial  U-Boot SPL    Yes (Built-in vars) Yes                      WIP
======================== ============  =================== ======================== ===========
