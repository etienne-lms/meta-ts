# Xilinx kv260 and SOMs

COMPATIBLE_MACHINE:zynqmp-starter = "zynqmp-starter"
COMPATIBLE_MACHINE:zynqmp-production = "zynqmp-production"

PV .= "+git${SRCREV_tfa}"

FILESEXTRAPATHS:prepend:zynqmp-starter := "${THISDIR}/files/zynqmp-starter:"
FILESEXTRAPATHS:prepend:zynqmp-production := "${THISDIR}/files/zynqmp-production:"

TFA_DEBUG = "0"
TFA_UBOOT = "0"
#TFA_MBEDTLS = "1"
TFA_BUILD_TARGET = "all"
TFA_INSTALL_TARGET = "bl31"

TFA_TARGET_PLATFORM = "zynqmp"

# Enabling Secure-EL1 Payload Dispatcher (SPD)
#TFA_SPD:zynqmp-production = "opteed"

EXTRA_OEMAKE:append = " ZYNQMP_CONSOLE=cadence1 RESET_TO_BL31=1 PLAT=zynqmp \
                        bl31 ZYNQMP_ATF_MEM_BASE=0xFFFE9000 \
						ZYNQMP_ATF_MEM_SIZE=0x17000"

# Production SOM will run op-tee for EFI variables once OP-TEE is fixed
#EXTRA_OEMAKE:append:zynqmp-production = " ZYNQMP_BL32_MEM_BASE=0x7d000000 \
#ZYNQMP_BL32_MEM_SIZE=0x2000000"

do_deploy:append() {
    cp ${D}/firmware/bl31.bin ${DEPLOYDIR}
}

addtask deploy before do_build after do_compile
