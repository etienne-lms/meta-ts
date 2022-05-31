DEPENDS += "python3-pycryptodomex-native python3-cryptography-native edk2-firmware"

FILESEXTRAPATHS:prepend := "${THISDIR}/files/optee-os/zynqmp-production/:"

COMPATIBLE_MACHINE:zynqmp-production = "zynqmp-production"

OPTEEMACHINE = "zynqmp-ultra96"
EXTRA_OEMAKE += " ARCH=arm"
EXTRA_OEMAKE += " CFG_TZDRAM_START=0x7d000000 CFG_TZDRAM_SIZE=0x1c00000"
EXTRA_OEMAKE += " CFG_SHMEM_START=0x7ec00000 CFG_SHMEM_SIZE=0x400000"
EXTRA_OEMAKE += " CFG_DT_ADDR=0x100000 CFG_CRYPTO_WITH_CE=n"

# Uncoment to enable verbose logs
# EXTRA_OEMAKE += " CFG_TEE_CORE_LOG_LEVEL=4 CFG_EARLY_CONSOLE=1"

# default disable latency benchmarks (over all OP-TEE layers)
EXTRA_OEMAKE +=  " CFG_TEE_BENCHMARK=n"

EXTRA_OEMAKE += " CFG_ARM64_core=y"

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
