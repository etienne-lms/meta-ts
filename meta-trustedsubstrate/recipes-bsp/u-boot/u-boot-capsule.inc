FILESEXTRAPATHS:prepend := "${THISDIR}/u-boot/capsule:"

DEPENDS += "ovmf-native"

# SRC_URI += "file://uefi-certificates/db.key"
# SRC_URI += "file://uefi-certificates/db.crt"

do_compile:append() {
	export PYTHONPATH="${STAGING_DIR_NATIVE}/usr/bin/edk2_basetools/BaseTools/Source/Python"

	cd ${B}/${MACHINE}_defconfig
	cp ${S}/../${MACHINE}/images.json .
	${HOSTTOOLS_DIR}/python3 ${STAGING_DIR_NATIVE}/usr/bin/edk2_basetools/BaseTools/Source/Python/Capsule/GenerateCapsule.py -j images.json \
		-e -o ${MACHINE}_fw.capsule \
		--verbose
	cd -
}

do_deploy:append() {
	mkdir -p ${DEPLOYDIR}
	cp ${B}/rockpi4b_defconfig/${MACHINE}_fw.capsule ${DEPLOYDIR}/
}
