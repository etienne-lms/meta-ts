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

- `U-Boot <https://source.denx.de/u-boot/u-boot>`
- `OP-TEE <https://github.com/OP-TEE>`
- `TF-A <https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git/>`
- `firmware TPM <https://github.com/microsoft/ms-tpm-20-ref>`
- `StandAloneMM from EDK2 <https://github.com/tianocore/edk2-platforms.git>`
- `SCP <https://github.com/ARM-software/SCP-firmware>`


Board Support
=============

* QEMU (arm64)
* `SynQuacer DeveloperBox <https://www.96boards.org/product/developerbox/>`_
* `stm32mp157c-dk2 <https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html>`_
* `stm32mp157c-ev1 <https://www.st.com/en/evaluation-tools/stm32mp157c-ev1.html>`_
* `Rockpi4 <https://rockpi.org/rockpi4>`_
* `Raspberry Pi4 <https://www.raspberrypi.com/products/raspberry-pi-4-model-b/specifications/>`_
* `Xilinx kv260 starter kit <https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit.html>`_

Supported platform features and software components
===================================================

======================== ===========  =================== ======================== ===========
Board                    FSBL         Secure Boot         Measured Boot            A/B updates
======================== ===========  =================== ======================== ===========
QEMU                     TF-A         Yes (Built in vars) Yes                      No
DeveloperBox             SCP + TF-A   Yes                 Yes [fTPM]_              WIP
stm32mp157c-dk2          TF-A         Yes                 No                       WIP
stm32mp157c-ev1          TF-A         Yes                 No                       WIP
Rockpi4                  U-Boot SPL   Yes                 Yes [fTPM]_              No
Raspberry Pi4            Proprietary  Yes                 Yes (needs SPI TPM)      No
Xilinx kv260 starter kit U-Boot SPL   Yes                 Yes                      WIP
======================== ===========  =================== ======================== ===========
