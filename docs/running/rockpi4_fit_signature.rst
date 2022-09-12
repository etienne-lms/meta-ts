#####################
RockPi4 FIT Signature
#####################

The RockPi4 build enables U-Boot's `CONFIG_FIT_SIGNATURE` in order to
provide authentication of the firmware binaries on boot, prior to UEFI
Secure Boot. The FIT image contains TF-A, OP-TEE and the main U-Boot
binary.

The RockPi4 boot sequence is as follows. The board boots from the micro SD
card which contains the firmware image (this project). Then it hands over
to the USB stick which contains the Linux distribution, for example the common
AArch64 EWAOL image (`ewaol-baremetal-image-ledge-secure-qemuarm64.wic.gz`).

.. code-block::

   ROM -> TPL -> ROM -> SPL -> TF-A BL31 -> OPTEE -> U-Boot -> Kernel -> initrd/rootfs
          ^^^           ^^^    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^    ^^^^^^
            idbloader.img             u-boot.itb               bootaa64.efi
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^               ^^^^^^^^^^^^^^^^^^^^^^^
            SD card (ts-firmware-rockpi4b.wic from meta-ts)    USB stick
                                                               (Linux distribution)

.. note::

   The FIT image is authenticated via the mechanism described here, and the
   Linux kernel is optionally authenticated via UEFI Secure Boot. However,
   the U-Boot TPL and SPL components are NOT authenticated.

.. note::

   This feature depends on local patches not in upstream U-Boot.
   See commit `392f2d92a186 <https://gitlab.com/Linaro/trustedsubstrate/meta-ts/-/commit/392f2d92a186b310725300dcece27c6678735918>`_.

The U-Boot recipe in `meta-trustedsubstrate/recipes-bsp/u-boot/u-boot-rockpi4b.inc`
uses an environment variable: `FIT_SIGN_KEY`, set to `dev` by default.
  - When undefined or empty, FIT signature is disabled
  - The value is the name of the key. For example if `FIT_SIGN_KEY=dev`
    then the private key is `keys/dev.key` in the U-Boot build directory
  - If the key file does not exist, a new key is generated (2048 bit RSA by
    default)

FIT signature verification can be seen during boot (`Checking hash(es)...`):

.. code-block::

   U-Boot TPL 2022.10-rc4 (Sep 06 2022 - 00:32:56)
   lpddr4_set_rate: change freq to 400MHz 0, 1
   Channel 0: LPDDR4, 400MHz
   BW=32 Col=10 Bk=8 CS0 Row=15 CS1 Row=15 CS=2 Die BW=16 Size=2048MB
   Channel 1: LPDDR4, 400MHz
   BW=32 Col=10 Bk=8 CS0 Row=15 CS1 Row=15 CS=2 Die BW=16 Size=2048MB
   256B stride
   lpddr4_set_rate: change freq to 800MHz 1, 0
   Trying to boot from BOOTROM
   Returning to boot ROM...

   U-Boot SPL 2022.10-rc4 (Sep 06 2022 - 00:32:56 +0000)
   Trying to boot from MMC1
   ## Checking hash(es) for config config_1 ... sha1,rsa2048:dev+ OK
   ## Checking hash(es) for Image atf_1 ... sha1+ sha1,rsa2048:dev+ OK
   ## Checking hash(es) for Image uboot ... sha1+ sha1,rsa2048:dev+ OK
   ## Checking hash(es) for Image fdt_1 ... sha1+ sha1,rsa2048:dev+ OK
   ## Checking hash(es) for Image atf_2 ... sha1+ sha1,rsa2048:dev+ OK
   ## Checking hash(es) for Image atf_3 ... sha1+ sha1,rsa2048:dev+ OK
   ## Checking hash(es) for Image atf_4 ... sha1+ sha1,rsa2048:dev+ OK
   NOTICE:  BL31: v2.6(debug):v2.6-879-gc3bdd3d3cf-dirty
   NOTICE:  BL31: Built : 09:30:50, May  9 2022
   WARNING: BL31: cortex_a53: CPU workaround for 1530924 was missing!
   I/TC:
   I/TC: No non-secure external DT
   I/TC: OP-TEE version: 3.18.0-dev (gcc version 11.2.0 (GCC)) #1 Fri Jul 15 09:06:00 UTC 2022 aarch64
   I/TC: WARNING: This OP-TEE configuration might be insecure!
   I/TC: WARNING: Please check https://optee.readthedocs.io/en/latest/architecture/porting_guidelines.html
   I/TC: Primary CPU initializing
   I/TC: Primary CPU switching to normal world boot


   U-Boot 2022.10-rc4 (Sep 06 2022 - 00:32:56 +0000)
   ...
