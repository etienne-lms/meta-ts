# Generate Rockchip style loader binaries
inherit deploy

FILESEXTRAPATHS:prepend := "${THISDIR}/u-boot/rockpi4b:"

SRC_URI:append = " file://rockpi4b_defconfig"
SRC_URI:append = " file://0004-phy-rockchip-inno-usb2-fix-hang-when-multiple-controllers-exit.patch"
SRC_URI:append = " file://0001-rk3399-rock-pi-4b-u-boot-add-optee-node.patch"
SRC_URI:append = " file://0001-rk3399-rock-pi-4b-u-boot.dtsi-reserve-optee-memory-t.patch"
SRC_URI:append = " file://0001-tee-optee-bind-ftpm-optee-driver.patch"
SRC_URI:append = " file://0001-rk3399_common-add-dfu_alt_info-for-rockpi4b.patch"
SRC_URI:append = " file://0001-spl-fit-add-config-option-for-temporary-buffer-when-.patch"
SRC_URI:append = " file://0002-rockchip-rk3399-enable-spl-fifo-mode-for-sdmmc-only-.patch"
SRC_URI:append = " file://0003-rockchip-make_fit_atf-generate-signed-conf-when-FIT_.patch"
SRC_URI:append = " file://0001-rockchip-rk3399-add-missing-structures-for-capsule-u.patch"

COMPATIBLE_MACHINE = "rockpi4b"

DEPENDS += "trusted-firmware-a gnutls-native"

do_compile:prepend() {
	export BL31="${RECIPE_SYSROOT}/firmware/bl31.elf"
	ls -l ${BL31}
	export TEE="${RECIPE_SYSROOT}/lib/firmware/tee.bin"
	ls -l ${TEE}
}

do_compile:append() {
	#${B}/rockpi4b_defconfig/tools/mkeficapsule -i 0x1 -r \
	#${B}/rockpi4b_defconfig/idbloader.img ${B}/rockpi4b_defconfig/idbloader.capsule

	#${B}/rockpi4b_defconfig/tools/mkeficapsule -i 0x2 -r \
	#${B}/rockpi4b_defconfig/u-boot.itb ${B}/rockpi4b_defconfig/u-boot.capsule

	export FIT_SIGN_KEY=dev
	if [ "${FIT_SIGN_KEY}" ]; then {
		cd ${B}/rockpi4b_defconfig
		KEY="keys/${FIT_SIGN_KEY}.key"
		CRT="keys/${FIT_SIGN_KEY}.crt"
		mkdir -p keys
		[ -e "${KEY}" ] || \
			openssl genpkey -algorithm RSA -out "${KEY}" \
				-pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537
		[ -e "${CRT}" ] || \
			openssl req -batch -new -x509 -key "${KEY}" -out "${CRT}"
		# Re-generate u-boot.its so that it contains signature nodes
		# make_fit_atf.py reads key name from ${FIT_SIGN_KEY}
		TEE=../../recipe-sysroot/lib/firmware/tee.bin BL31=../../recipe-sysroot/firmware/bl31.elf \
			../../git/arch/arm/mach-rockchip/make_fit_atf.py \
			arch/arm/dts/rk3399-rock-pi-4b.dtb > u-boot.its
		cp spl/dts/dt-spl.dtb spl/u-boot-spl.dtb
		# Generate signed u-boot.itb and add public key to spl/u-boot-spl.dtb
		./tools/mkimage -E -B 0x8 -p 0x0 -f u-boot.its -k keys \
			-r -K spl/u-boot-spl.dtb u-boot.itb
		# Generate idbloader.img which will authenticate u-boot.itb
		./tools/mkimage -n "rk3399" -T rksd -d tpl/u-boot-tpl.bin tpl/u-boot-tpl-rockchip.bin
		cat tpl/u-boot-tpl-rockchip.bin spl/u-boot-spl-nodtb.bin \
			spl/u-boot-spl.dtb > idbloader.img
	}; fi
}

do_deploy:append() {
	mkdir -p ${DEPLOYDIR}
	cp ${B}/rockpi4b_defconfig/idbloader.img  ${DEPLOYDIR}/idbloader.img
	cp ${B}/rockpi4b_defconfig/u-boot.itb ${DEPLOYDIR}/u-boot.itb
	#cp ${B}/rockpi4b_defconfig/idbloader.capsule ${DEPLOYDIR}/idbloader.capsule
	#cp ${B}/rockpi4b_defconfig/u-boot.capsule ${DEPLOYDIR}/u-boot.capsule
}

ATF_DEPENDS = " trusted-firmware-a:do_deploy"
do_compile[depends] .= "${ATF_DEPENDS}"
