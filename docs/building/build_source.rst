####################
Getting the firmware
####################

Building from source
********************

The repository is using ``kas`` a setup tool for bitbake based projects.
Install the required packages with

.. code-block:: bash

    pip install kas

Compiling for different boards is straightforward.

.. warning::

   Since UEFI secure boot is enabled by default, boards that embed the UEFI keys
   in the firmware binary will use the predefined Linaro `certificates
   <https://git.codelinaro.org/linaro/dependable-boot/meta-ts/-/tree/master/meta-trustedsubstrate/uefi-certificates>`_.
   Those boards will only be allowed to boot images signed by the 
   afforementioned Linaro certificates.
   
   :ref:`Building with your own certificates` if you want to generate your own
   
   :ref:`Hardware and UEFI variable limitations` for hardware limitations

.. code-block:: bash

    git clone https://git.codelinaro.org/linaro/dependable-boot/meta-ts.git
    cd meta-ts
    kas build ci/<board>.yml

replace <board> with 

* qemuarm64-secureboot
* synquacer
* stm32mp157c-dk2
* stm32mp157c-ev1
* rockpi4b
* rpi4
* zynqmp-starter

The build output is in ``build/tmp/deploy/images/``

.. hint::

    The build directory contains a lot of artifacts.
    Look at :ref:`Installing Firmware` for the per board files
    you need

Downloading board binaries
**************************

We do produce daily builds for all the support boards 
`here <https://snapshots.linaro.org/components/ledge/ts/latest/>`_

Building with your own certificates
***********************************

.. warning:: 

   The default nightly builds we provide for devices that embed the keys are
   using a private key that is available at
   ``meta-trustedsubstrate/uefi-certificates/``.
   Anyone could sign and boot an EFI binary!
   **This is a mandatory step for a production firmware!**

You need to generate the following keys:

* PK  - Platform Key (Top-level key) 
* KEK - Key Exchange Keys (Keys used to sign Signatures Database and Forbidden Signatures Database updates)
* db  - Signature Database (Contains keys and/or hashes of allowed EFI binaries) 
* dbx - Forbidden Signature Database (Contains keys and/or hashes of forbidden EFI binaries)

Refer to :ref:`Create certificates and keys` for  generating certificates and
create tar.gz archive with the .esl files

.. code-block:: bash

    tar -czf uefi_certs.tgz db.esl dbx.esl KEK.esl PK.esl

Set up an environment variable ``UEFI_CERT_FILE: "<path>/uefi_certs.tgz"``
in your ``local.conf`` or in ``ci/base.yml`` and recompile your firmware.

.. note::
   This is **only** needed if the variables are built-in into the firmware binary.
   You don't need this if your board has an RPMB and OP-TEE support.
