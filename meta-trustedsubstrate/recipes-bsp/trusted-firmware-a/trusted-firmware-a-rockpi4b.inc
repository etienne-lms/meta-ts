# Rock Pi 4B 64-bit machines specific TFA support

COMPATIBLE_MACHINE = "rockpi4b"

PV .= "+git${SRCREV_tfa}"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/rockpi4b:"

SRC_URI += " file://0001-rkk3399-use-default-uart-speed.patch"

TFA_DEBUG = "1"
TFA_UBOOT = "0"
TFA_MBEDTLS = "1"
TFA_BUILD_TARGET = "all bl32"
TFA_INSTALL_TARGET = "bl31"

TFA_TARGET_PLATFORM = "rk3399"

# Enabling Secure-EL1 Payload Dispatcher (SPD)
TFA_SPD = "opteed"
# Cortex-A35 supports Armv8.0-A (no S-EL2 execution state).
# So, the SPD SPMC component should run at the S-EL1 execution state
TFA_SPMD_SPM_AT_SEL2 = "0"

# BL2 loads BL32 (optee). So, optee needs to be built first:
DEPENDS += " optee-os gcc-arm-none-eabi-native"
DEPENDS:remove = "uboot"

# EXTRA_OEMAKE:append = ' PRELOADED_BL33_BASE=0x08200000 SQ_USE_SCMI_DRIVER=1'

EXTRA_OEMAKE:append = " \
                        ARCH=aarch64 \
                        TARGET_PLATFORM=${TFA_TARGET_PLATFORM} \
                        TRUSTED_BOARD_BOOT=1 \
                        ARM_ROTPK_LOCATION=devel_rsa  \
                        BL32=${RECIPE_SYSROOT}/lib/firmware/tee.elf \
                        LOG_LEVEL=30 \
			"

addtask deploy before do_build after do_compile

FILES:${PN} = "/boot /firmware"

TOOLCHAIN = "gcc"
