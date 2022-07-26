# Generate zynqmp-starter kit style loader binaries
inherit deploy

SRCREV="4fe629d2e8bbda5f265e870d771b92be26e885f6"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"

SRC_URI:append = " file://xilinx_zynqmp_starter_defconfig"
SRC_URI:append = " file://pmu_obj.bin"
SRC_URI:append = " file://pmufw.bin"
SRC_URI:append = " file://0001-som-Kria-specific-setting-configurations.patch"

COMPATIBLE_MACHINE = "zynqmp-starter"

DEPENDS:append = " trusted-firmware-a"
DEPENDS:append = " xxd-native"
DEPENDS:append = " u-boot-mkimage-native "

do_compile:prepend() {
    cp ${S}/../pmufw.bin ${S}/
    cp ${S}/../pmufw.bin ${B}/xilinx_zynqmp_starter_defconfig/
    cp ${S}/../pmu_obj.bin ${S}/
    cp ${S}/../pmu_obj.bin ${B}/xilinx_zynqmp_starter_defconfig/
    cp ${S}/som.its ${B}/xilinx_zynqmp_starter_defconfig/
    export BL31="${RECIPE_SYSROOT}/firmware/bl31.bin"
}

do_deploy:append() {
    mkdir -p ${DEPLOYDIR}
    cd ${B}/xilinx_zynqmp_starter_defconfig/
	
    # temporary dtb resolution until it gets upstreamed
    # Build overlays
    fdtoverlay -o zynqmp-smk-k26-revA-sck-kv-g-revA.dtb -i arch/arm/dts/zynqmp-smk-k26-revA.dtb arch/arm/dts/zynqmp-sck-kv-g-revA.dtbo
    fdtoverlay -o zynqmp-smk-k26-revA-sck-kv-g-revB.dtb -i arch/arm/dts/zynqmp-smk-k26-revA.dtb arch/arm/dts/zynqmp-sck-kv-g-revB.dtbo
    fdtoverlay -o zynqmp-sm-k26-revA-sck-kv-g-revA.dtb -i arch/arm/dts/zynqmp-sm-k26-revA.dtb arch/arm/dts/zynqmp-sck-kv-g-revA.dtbo
    fdtoverlay -o zynqmp-sm-k26-revA-sck-kv-g-revB.dtb -i arch/arm/dts/zynqmp-sm-k26-revA.dtb arch/arm/dts/zynqmp-sck-kv-g-revB.dtbo
    # Pack all combinations together
    mkimage -E -f som.its -B 0x8 fit-dtb.blob
    # Add new fit-dtb.blob back to u-boot.its
    mkimage -E -f u-boot.its -B 0x8  u-boot.itb
    cd -
    cp ${B}/xilinx_zynqmp_starter_defconfig/spl/boot.bin ${DEPLOYDIR}/ImageA.bin
    cp ${B}/xilinx_zynqmp_starter_defconfig/u-boot.itb ${DEPLOYDIR}/ImageB.bin
}

ATF_DEPENDS = " trusted-firmware-a:do_deploy"
do_compile[depends] .= "${ATF_DEPENDS}"
