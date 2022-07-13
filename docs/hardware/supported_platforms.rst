###################
Supported Platforms
###################

Trusted Substrate supports a variety of armv8 and armv7 boards.  It's important
to understand that the hardware characteristics dictate the supported features
as well as the level of the device security


Board Support
=============

* QEMU (arm64)
* `SynQuacer DeveloperBox <https://www.96boards.org/product/developerbox/>`_
* `stm32mp157c-dk2 <https://www.st.com/en/evaluation-tools/stm32mp157c-dk2.html>`_
* `stm32mp157c-ev1 <https://www.st.com/en/evaluation-tools/stm32mp157c-ev1.html>`_
* `Rockpi4 <https://rockpi.org/rockpi4>`_
* `Raspberry Pi4 <https://www.raspberrypi.com/products/raspberry-pi-4-model-b/specifications/>`_
* `Xilinx kv260 starter kit <https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit.html>`_

Supported platform features
===========================

======================== ============ ======================== ===========
Board                     Secure Boot   Measured Boot          A/B updates
======================== ============ ======================== ===========
QEMU                         Yes           Yes                       No
DeveloperBox                 Yes           Yes                       WIP
stm32mp157c-dk2              Yes           No                        WIP
stm32mp157c-ev1              No            No                        WIP
Rockpi4                      Yes           Yes                       No
Raspberry Pi4                Yes           Yes (needs SPI TPM)       No
Xilinx kv260 starter kit     Yes           Yes                       No
======================== ============ ======================== ===========
