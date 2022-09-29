LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

inherit deploy

ALLOW_EMPTY:${PN} = "1"

DEPENDS += "ovmf-native u-boot trusted-firmware-a"
DEPENDS += "python3-pyopenssl-native"

SRC_URI  += "file://${MACHINE}-images.json"

do_deploy() {
	if [ -e "${UEFI_CAPSULE_CERT_FILE}" ]; then
		mkdir -p uefi_capsule_certs
		tar xpvfz ${UEFI_CAPSULE_CERT_FILE} -C uefi_capsule_certs

		cp uefi_capsule_certs/CRT.pem CRT.pem
		cp uefi_capsule_certs/CRT.pub.pem CRT.pub.pem

		if [ -e ${DEPLOY_DIR_IMAGE}/fip_all_arm_tf_optee.bin ]; then cp ${DEPLOY_DIR_IMAGE}/fip_all_arm_tf_optee.bin . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/fip.bin ]; then cp ${DEPLOY_DIR_IMAGE}/fip.bin . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/u-boot.bin ]; then cp ${DEPLOY_DIR_IMAGE}/u-boot.bin . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/optee/tee-pager_v2.bin ]; then cp ${DEPLOY_DIR_IMAGE}/optee/tee-pager_v2.bin . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/idbloader.img ]; then cp ${DEPLOY_DIR_IMAGE}/idbloader.img . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/u-boot.itb ]; then cp ${DEPLOY_DIR_IMAGE}/u-boot.itb . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/ImageA.bin ]; then cp ${DEPLOY_DIR_IMAGE}/ImageA.bin . ; fi
		if [ -e ${DEPLOY_DIR_IMAGE}/ImageB.bin ]; then cp ${DEPLOY_DIR_IMAGE}/ImageB.bin . ; fi

		cp ${S}/../${MACHINE}-images.json  .
		export PYTHONPATH="${STAGING_DIR_NATIVE}/usr/bin/edk2_basetools/BaseTools/Source/Python"
		${HOSTTOOLS_DIR}/python3 ${STAGING_DIR_NATIVE}/usr/bin/edk2_basetools/BaseTools/Source/Python/Capsule/GenerateCapsule.py -j ${MACHINE}-images.json \
			-e -o ${MACHINE}_fw.capsule \
			--verbose

		mkdir -p ${DEPLOYDIR}
		cp ${MACHINE}_fw.capsule ${DEPLOYDIR}/
	fi
}

addtask deploy before do_build after do_compile

CAPSULE_DEPENDS = " trusted-firmware-a:do_deploy u-boot:do_deploy"
do_compile[deploy] .= "${CAPSULE_DEPENDS}"
