# Generate Rockchip style loader binaries
inherit deploy

FILESEXTRAPATHS:prepend := "${THISDIR}/u-boot/rockpi4b:"

SRC_URI:append = " file://rockpi4b_defconfig"
SRC_URI:append = " file://0004-phy-rockchip-inno-usb2-fix-hang-when-multiple-controllers-exit.patch"
SRC_URI:append = " file://0001-rk3399-rock-pi-4b-u-boot-add-optee-node.patch"
SRC_URI:append = " file://0001-rk3399-rock-pi-4b-u-boot.dtsi-reserve-optee-memory-t.patch"
SRC_URI:append = " file://0001-tee-optee-bind-ftpm-optee-driver.patch"
SRC_URI:append = " file://0001-mach-rockchip-make_fit_atf.py-support-OP-TEE-tee.bin.patch"
SRC_URI:append = " file://0001-rk3399_common-add-dfu_alt_info-for-rockpi4b.patch"

COMPATIBLE_MACHINE = "rockpi4b"

DEPENDS += "trusted-firmware-a gnutls-native"

do_compile:prepend() {
	export BL31="${RECIPE_SYSROOT}/firmware/bl31.elf"
	ls -l ${BL31}
	export TEE="${RECIPE_SYSROOT}/lib/firmware/tee.bin"
	ls -l ${TEE}
}

do_compile:append() {
	${B}/rockpi4b_defconfig/tools/mkeficapsule -i 0x1 -r \
	${B}/rockpi4b_defconfig/idbloader.img ${B}/rockpi4b_defconfig/idbloader.capsule

	${B}/rockpi4b_defconfig/tools/mkeficapsule -i 0x2 -r \
	${B}/rockpi4b_defconfig/u-boot.itb ${B}/rockpi4b_defconfig/u-boot.capsule
}

do_deploy:append() {
	mkdir -p ${DEPLOYDIR}
	cp ${B}/rockpi4b_defconfig/idbloader.img  ${DEPLOYDIR}/idbloader.img
	cp ${B}/rockpi4b_defconfig/u-boot.itb ${DEPLOYDIR}/u-boot.itb
	cp ${B}/rockpi4b_defconfig/idbloader.capsule ${DEPLOYDIR}/idbloader.capsule
	cp ${B}/rockpi4b_defconfig/u-boot.capsule ${DEPLOYDIR}/u-boot.capsule
}

ATF_DEPENDS = " trusted-firmware-a:do_deploy"
do_compile[depends] .= "${ATF_DEPENDS}"
