FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/synquacer:"

SRC_URI += "file://0001-tee-optee-bind-ftpm-optee-driver.patch"
SRC_URI += "file://synquacer_developerbox_defconfig"
