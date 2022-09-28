FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:${THISDIR}/u-boot/common:"

# Always increment PR on u-boot config change or patches
PR = "r1.ts"

# Overwrite poky side SRC_URI to remove all security etc patches
# since we update to a newer version anyway and the patches don't apply
SRC_URI = "git://git.denx.de/u-boot.git;branch=master"

SRC_URI += "file://0001-tee-optee-rework-TA-bus-scanning-code.patch"
SRC_URI += "file://0002-fix-smbios-tables.patch"

PV = "2022.10-rc5"
SRCREV = "f76f3e3b44328fe6229650540109af93750fd5f0"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"

do_configure:prepend() {
	cp -r ${WORKDIR}/*_defconfig ${S}/configs/ || true
}

MACHINE_UBOOT_REQUIRE ?= ""

MACHINE_UBOOT_REQUIRE:rockpi4b = "u-boot-rockpi4b.inc"
MACHINE_UBOOT_REQUIRE:rpi4 = "u-boot-rpi4.inc"
MACHINE_UBOOT_REQUIRE:synquacer = "u-boot-synquacer.inc"
MACHINE_UBOOT_REQUIRE:tsqemuarm64-secureboot = "u-boot-qemuarm64-secureboot.inc"
MACHINE_UBOOT_REQUIRE:stm32mp157c-dk2 = "u-boot-stm32mp157c-dk2.inc"
MACHINE_UBOOT_REQUIRE:stm32mp157c-ev1 = "u-boot-stm32mp157c-ev1.inc"
MACHINE_UBOOT_REQUIRE:zynqmp-starter = "u-boot-zynqmp-starter.inc"
MACHINE_UBOOT_REQUIRE:zynqmp-production = "u-boot-zynqmp-production.inc"

require ${MACHINE_UBOOT_REQUIRE}

require u-boot-certs.inc
