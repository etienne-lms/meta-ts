# Machine specific TFAs
#

SRC_URI = "git://git.trustedfirmware.org/TF-A/trusted-firmware-a.git;protocol=https;name=tfa;branch=master"
SRCREV_tfa = "c3bdd3d3cf0f9cdf3be117e39386492e645a1bb5"
LIC_FILES_CHKSUM="file://docs/license.rst;md5=b2c740efedc159745b9b31f88ff03dde"

MACHINE_TFA_REQUIRE ?= ""

MACHINE_TFA_REQUIRE:synquacer = "trusted-firmware-a-synquacer.inc"
MACHINE_TFA_REQUIRE:stm32mp157c-dk2 = "trusted-firmware-a-stm32mp157c-dk2.inc"
MACHINE_TFA_REQUIRE:stm32mp157c-ev1 = "trusted-firmware-a-stm32mp157c-ev1.inc"
MACHINE_TFA_REQUIRE:rockpi4b = "trusted-firmware-a-rockpi4b.inc"
MACHINE_TFA_REQUIRE:zynqmp-starter = "trusted-firmware-a-zynqmp-starter.inc"
MACHINE_TFA_REQUIRE:qemuarm64-secureboot = "trusted-firmware-a-qemuarm64-secureboot.inc"

require ${MACHINE_TFA_REQUIRE}
