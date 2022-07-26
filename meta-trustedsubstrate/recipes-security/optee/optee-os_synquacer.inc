DEPENDS += "python3-pycryptodomex-native edk2-firmware"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/optee-os/synquacer:"

SRC_URI:append = " \
		  file://0001-plat-synquacer-add-whole-DRAM-region-for-u-boot-supp.patch"

COMPATIBLE_MACHINE = "synquacer"

OPTEEMACHINE = "synquacer"
OPTEEOUTPUTMACHINE = "synquacer"

# Uncoment to enable verbose logs
#EXTRA_OEMAKE:remove = "CFG_TEE_CORE_LOG_LEVEL=2"
#EXTRA_OEMAKE += " CFG_TEE_CORE_LOG_LEVEL=4"

# default disable latency benchmarks (over all OP-TEE layers)
EXTRA_OEMAKE += " CFG_TEE_BENCHMARK=n"

EXTRA_OEMAKE += ' CFG_RPMB_FS=y CFG_RPMB_FS_DEV_ID=0 CFG_RPMB_WRITE_KEY=y'
EXTRA_OEMAKE += ' CFG_CORE_HEAP_SIZE=524288 CFG_CORE_DYN_SHM=y CFG_RPMB_TESTKEY=y'
EXTRA_OEMAKE += ' CFG_REE_FS=n CFG_CORE_ARM64_PA_BITS=48 CFG_SCTLR_ALIGNMENT_CHECK=n'

EXTRA_OEMAKE += " HOST_PREFIX=${HOST_PREFIX}"
EXTRA_OEMAKE += " CROSS_COMPILE64=${HOST_PREFIX}"

# Include StandAloneMM
EXTRA_OEMAKE += " CFG_STMM_PATH=${DEPLOY_DIR_IMAGE}/uefi.bin "
