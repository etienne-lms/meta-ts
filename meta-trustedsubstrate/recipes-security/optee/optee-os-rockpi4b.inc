SRC_URI = "git://git.trustedfirmware.org/OP-TEE/optee_os.git;protocol=https;branch=master"

DEPENDS += "python3-pycryptodomex-native python3-cryptography-native edk2-firmware"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/optee-os/rockpi4b:"

SRC_URI:append = " \
                  file://0001-plat-rockchip-register-nsec-ddr.patch"

COMPATIBLE_MACHINE = "rockpi4b"

OPTEEMACHINE = "rockchip"
OPTEEOUTPUTMACHINE = "rockchip"
EXTRA_OEMAKE += " PLATFORM_FLAVOR=rk3399 ARCH=arm"

# Uncoment to enable verbose logs
#EXTRA_OEMAKE:remove = "CFG_TEE_CORE_LOG_LEVEL=2"
#EXTRA_OEMAKE += " CFG_TEE_CORE_LOG_LEVEL=4 "

# default disable latency benchmarks (over all OP-TEE layers)
EXTRA_OEMAKE +=  " CFG_TEE_BENCHMARK=n"

EXTRA_OEMAKE += " CFG_ARM64_core=y"

EXTRA_OEMAKE += " CFG_CRYPTO_WITH_CE=y"

EXTRA_OEMAKE += " HOST_PREFIX=${HOST_PREFIX}"
EXTRA_OEMAKE += " CROSS_COMPILE64=${HOST_PREFIX}"

FILES:${PN} = "/lib/firmware"
SYSROOT_DIRS += "/lib/firmware"

FILES:${PN}-dbg = "/lib/firmware/*.elf"
# Skip QA check for relocations in .text of elf binaries
INSANE_SKIP:${PN}-dbg = "textrel"


# Include StandAloneMM
EXTRA_OEMAKE += ' CFG_RPMB_FS=y CFG_RPMB_FS_DEV_ID=0 CFG_RPMB_WRITE_KEY=y'
EXTRA_OEMAKE += ' CFG_CORE_HEAP_SIZE=65536 CFG_CORE_DYN_SHM=y CFG_RPMB_TESTKEY=y'
EXTRA_OEMAKE += ' CFG_REE_FS=n CFG_SCTLR_ALIGNMENT_CHECK=n'
EXTRA_OEMAKE += " CFG_STMM_PATH=${DEPLOY_DIR_IMAGE}/uefi.bin "
