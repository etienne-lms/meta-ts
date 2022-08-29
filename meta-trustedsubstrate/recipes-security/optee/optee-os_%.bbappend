# Machine specific configurations

# 3.18.0
SRCREV = "1ee647035939e073a2e8dddb727c0f019cc035f1"
PV .= "+git${SRCREV}"

DEPENDS:append = " dtc-native"

MACHINE_OPTEE_OS_REQUIRE ?= ""
MACHINE_OPTEE_OS_REQUIRE:synquacer = "optee-os_synquacer.inc"
MACHINE_OPTEE_OS_REQUIRE:stm32mp157c-dk2 = "optee-os-stm32mp157c-dk2.inc"
MACHINE_OPTEE_OS_REQUIRE:stm32mp157c-ev1 = "optee-os-stm32mp157c-ev1.inc"
MACHINE_OPTEE_OS_REQUIRE:rockpi4b = "optee-os-rockpi4b.inc"
MACHINE_OPTEE_OS_REQUIRE:zynqmp-production = "optee-os-zynmp.inc"

require ${MACHINE_OPTEE_OS_REQUIRE}

# Add PKCS11 as early TA
DEPENDS += " python3-cryptography-native "
EXTRA_OEMAKE:append = " CFG_IN_TREE_EARLY_TAS=pkcs11/fd02c9da-306c-48c7-a49c-bbd827ae86ee "
EXTRA_OEMAKE:append = " CFG_CORE_HEAP_SIZE=131072 "
EXTRA_OEMAKE:append = " CFG_CORE_BGET_BESTFIT=y "
# OP-TEE log level 2 is INFO
EXTRA_OEMAKE:append = " CFG_TEE_CORE_LOG_LEVEL=2"
EXTRA_OEMAKE:append = " CFG_RPMB_FS_CACHE_ENTRIES=48 "
