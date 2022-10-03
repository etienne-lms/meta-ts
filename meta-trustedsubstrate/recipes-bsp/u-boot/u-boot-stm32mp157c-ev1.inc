inherit deploy
NO_DTB_UBOOT="u-boot-nodtb.bin"

COMPATIBLE_MACHINE = "stm32mp157c-ev1"
SRC_URI += "file://stm32mp157c_ev1_trusted_defconfig"

SRC_URI:append = " file://0001-dts-arm-stm32mp15-locate-env-in-u-boot-env-labeled-partitiion.patch"

SRC_URI:append = " file://0001-dt-bindings-Add-bindings-for-GPT-based-FWU-Metadata-.patch"
SRC_URI:append = " file://0002-FWU-Add-FWU-metadata-structure-and-driver-for-access.patch"
SRC_URI:append = " file://0003-FWU-Add-FWU-metadata-access-driver-for-GPT-partition.patch"
SRC_URI:append = " file://0004-stm32mp1-dk2-Add-a-node-for-the-FWU-metadata-device.patch"
SRC_URI:append = " file://0005-stm32mp1-dk2-Add-image-information-for-capsule-updat.patch"
SRC_URI:append = " file://0006-FWU-Add-helper-functions-for-accessing-FWU-metadata.patch"
SRC_URI:append = " file://0007-FWU-STM32MP1-Add-support-to-read-boot-index-from-bac.patch"
SRC_URI:append = " file://0008-event-Add-an-event-for-main_loop.patch"
SRC_URI:append = " file://0009-FWU-Add-boot-time-checks-as-highlighted-by-the-FWU-s.patch"
SRC_URI:append = " file://0010-FWU-Add-support-for-the-FWU-Multi-Bank-Update-featur.patch"
SRC_URI:append = " file://0011-FWU-cmd-Add-a-command-to-read-FWU-metadata.patch"
SRC_URI:append = " file://0012-test-dm-Add-test-cases-for-FWU-Metadata-uclass.patch"
SRC_URI:append = " file://0013-mkeficapsule-Add-support-for-generating-empty-capsul.patch"
SRC_URI:append = " file://0014-mkeficapsule-Add-support-for-setting-OEM-flags-in-ca.patch"
SRC_URI:append = " file://0015-FWU-doc-Add-documentation-for-the-FWU-feature.patch"
SRC_URI:append = " file://0016-fixup-test-dm-Add-test-cases-for-FWU-Metadata-uclass.patch"
SRC_URI:append = " file://0017-stm32mp1-ev1-Add-a-node-for-the-FWU-metadata-device.patch"
SRC_URI:append = " file://0018-fixup-efi_update_capsule-for-fwu.patch"

do_deploy () {
	mkdir -p ${DEPLOYDIR}
	cp ${B}/stm32mp157c_ev1_trusted_defconfig/arch/arm/dts/stm32mp157c-ev1.dtb  ${DEPLOYDIR}/
	cp ${B}/stm32mp157c_ev1_trusted_defconfig/${NO_DTB_UBOOT} ${DEPLOYDIR}/
}
