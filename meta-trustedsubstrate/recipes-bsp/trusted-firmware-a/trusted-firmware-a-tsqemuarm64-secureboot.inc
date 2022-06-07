# qemuarm64-secureboot  machines specific TFA support

COMPATIBLE_MACHINE = "tsqemuarm64-secureboot"

TFA_PLATFORM = "qemu"
TFA_SPD = "opteed"
TFA_UBOOT = "1"
TFA_BUILD_TARGET:aarch64:qemuall = "all fip"
TFA_INSTALL_TARGET = "flash.bin"

DEPENDS:append:aarch64:qemuall = " optee-os u-boot"

EXTRA_OEMAKE:append:aarch64:qemuall = " \
    BL32=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-header_v2.bin \
    BL32_EXTRA1=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-pager_v2.bin \
    BL32_EXTRA2=${STAGING_DIR_TARGET}${nonarch_base_libdir}/firmware/tee-pageable_v2.bin \
    BL32_RAM_LOCATION=tdram \
    "

do_compile:append() {
    # Create a secure flash image for booting AArch64 Qemu. See:
    # https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git/tree/docs/plat/qemu.rst
    dd if=/dev/zero of=${BUILD_DIR}/flash.bin bs=1M count=64
    dd if=${BUILD_DIR}/bl1.bin of=${BUILD_DIR}/flash.bin bs=4096 conv=notrunc
    dd if=${BUILD_DIR}/fip.bin of=${BUILD_DIR}/flash.bin seek=64 bs=4096 conv=notrunc
}
