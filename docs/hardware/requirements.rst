#####################
Hardware Requirements
#####################

UEFI Secure Boot storage requirements
*************************************

[UEFI]_ (§ 32.3.6 Platform Firmware Key Storage Requirements) defines that the
Platform and Key exchange keys must be stored in a non-volatile storage which
is tamper protected.

On Arm servers this is usually tackled by having a dedicated flash which is
only accessible by the secure world. 

Hardware which was designed with security in mind has the following options.

======================== ================ ==============
Hardware                 UEFI Secure Boot Measured Boot
======================== ================ ==============
RPMB [1]_                        x              x
Discrete TPM                                    x
Flash in secure world            x
======================== ================ ==============

The reality on embedded boards is different though.  In the embedded case,
we don't have a dedicated flash.  What's becoming more common though is eMMC
devices with an RPMB partition.

If the board has a RPMB and OP-TEE support,  Trusted Substrate will use
that device to store all the EFI variables.  However for boards that
don't have an RPMB the keys are built-in into the firmware binary.

Bundling the keys comes with it's own set of limitations.  The most notable ones
being that in order to update any security related EFI variable, you need to
update the bootloader and you can only boot signed binaries by default.
Other, non security critical, EFI variables are stored in a file located in the
ESP.  

.. [1] Requires OP-TEE support and a way to program the RPMB with a unique per hardware key 
       (e.g a fuse accessible only from the secure world).
       Setting EFI variables at runtime (from the OS) not supported

Hardware and UEFI variable limitations
======================================

The firmware automatically enables and disables UEFI Secure Boot
based on the existence of the Platform Key (PK).  As a consequence
boards that embed the keys in the firmware will only be allowed to
boot signed binaries and you won't be able to change the UEFI keys.
See :ref:`Building with your own certificates`

On the other hand boards that store the variables in the RPMB come
with an empty PK and the user must provision one during the setup
process in order to enable Secure Boot.

.. uml::

    (*) --> if "Board has RPMB" then
                -->[Yes] "Board has OP-TEE"
                if "" then
                    -->[Yes] "EFI Variables in RPMB"
                    if "Provision PK" then
                        --> "Secure Boot enabled"
                    endif
                else
                    -left->[No] "EFI variables in ESP. PK, KEK, db and dbx built-in into the binary"
                    --> "Secure Boot enabled"
                endif
            else
                ->[No] "EFI variables in ESP. PK, KEK, db and dbx built-in into the binary"
            endif

Trusted Platform module
***********************

TPMs are microcontrollers designed for cryptographic tasks.
They contain a set of Platform Configuration Registers (PCRs) which are used to
measure the system configuration and software.

PCRs start zeroed out and can only reset with a system reboot.
Those can be extended by writing a SHA hash (typically SHA-1/256/384/512 for TPMv2)
into the PCR.  To store a new value in a PCR, the existing value is extended
with a new value as follows: PCR[N] = HASHalg( PCR[N] || ArgumentOfExtend )

Trusted Substrate is designed to work with either discrete TPMs or provide an
[fTPM]_ running in OP-TEE.

.. uml::

    (*) --> if "Board has discrete TPM" then
                -->[No] "Board has RPMB and OP-TEE"
                if "" then
                    ->[Yes, use fTPM] "Measured Boot enabled"
                else
                    -left->[No] "Measured boot disabled"
                endif
            else
                ->[Yes] "Measured Boot enabled"
            endif
