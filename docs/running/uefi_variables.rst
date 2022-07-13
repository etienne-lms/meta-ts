##########################
Configuring UEFI variables
##########################

Boards that embed the UEFI keys in the U-Boot binary
:ref:`UEFI Secure Boot storage requirements` won't allow you to change
the EFI security related variables (PK, KEK, db and dbx) permanently.

That category of boards comes with a predefined set of keys.  For more details
look at :ref:`Building with your own certificates`

Enabling Secure Boot
********************

Secure Boot is enabled and disabled automatically based on the existence of a 
Platform Key (PK).  Enrolling one will enable UEFI Secure Boot and all the 
EFI binaries must to be signed.

For more details look at [UEFI]_ (§ 32.3.1  Enrolling The Platform Key)

Create certificates and keys
============================

Copy and run the script below.  The .auth files you need can be found in ``efi_keys/``
directory and the private certificates on ``priv_keys``.

.. note:: 

   This script is provided as sample.
   Always backup your SSL certificates directory!

.. code-block:: bash

   #!/bin/bash
   # sudo apt install efitools openssl uuid-runtime
   set -e
   CN='mytestCA'
   OUT_DIR=priv_keys/
   OUT_EFI_DIR=efi_keys/

   mkdir $OUT_DIR -p
   mkdir $OUT_EFI_DIR -p
   if [ ! -e "$OUT_DIR/GUID.txt" ]; then
       GUID=$(uuidgen)
       echo $GUID > $OUT_DIR/GUID.txt
   else    
       echo "Please remove '"$OUT_DIR"GUID.txt' to regenerate certs"
       echo "This will overwrite your private keys!"
       exit 1
   fi

   for cert in PK KEK db dbx; do
       # SSL certs
       openssl req -new -x509 -newkey rsa:2048 -subj "/CN=$CN $cert/" -keyout \
           $OUT_DIR/$cert.key -out $OUT_DIR/$cert.crt -days 3650 -nodes -sha256

       # EFI signature list certs
       # .esl certs can be concatenated if we want to support multiple signers
       cert-to-efi-sig-list -g $GUID $OUT_DIR/$cert.crt $OUT_EFI_DIR/$cert.esl
   done
   # Empty PK to reset secure boot
   rm -f $OUT_EFI_DIR/noPK.esl
   touch $OUT_EFI_DIR/noPK.esl

   sign-efi-sig-list -c $OUT_DIR/PK.crt -k $OUT_DIR/PK.key PK $OUT_EFI_DIR/noPK.esl $OUT_EFI_DIR/noPK.auth
   sign-efi-sig-list -c $OUT_DIR/PK.crt -k $OUT_DIR/PK.key PK $OUT_EFI_DIR/PK.esl $OUT_EFI_DIR/PK.auth
   sign-efi-sig-list -c $OUT_DIR/PK.crt -k $OUT_DIR/PK.key KEK $OUT_EFI_DIR/KEK.esl $OUT_EFI_DIR/KEK.auth
   sign-efi-sig-list -c $OUT_DIR/KEK.crt -k $OUT_DIR/KEK.key db $OUT_EFI_DIR/db.esl $OUT_EFI_DIR/db.auth
   sign-efi-sig-list -c $OUT_DIR/KEK.crt -k $OUT_DIR/KEK.key dbx $OUT_EFI_DIR/dbx.esl $OUT_EFI_DIR/dbx.auth
   chmod 0600 $OUT_DIR/*.key

Enable Secure Boot
==================

The commands below assume the keys are stored in the first partition of a usb
stick.

.. code-block:: bash

   load usb 0:1 90000000 PK.auth && setenv -e -nv -bs -rt -at -i 90000000:$filesize PK
   load usb 0:1 90000000 KEK.auth && setenv -e -nv -bs -rt -at -i 90000000:$filesize KEK
   load usb 0:1 90000000 db.auth && setenv -e -nv -bs -rt -at -i 90000000:$filesize db
   load usb 0:1 90000000 dbx.auth && setenv -e -nv -bs -rt -at -i 90000000:$filesize dbx

Disable Secure Boot
===================

The commands below assume the keys are stored in the first partition of a usb
stick.

.. code-block:: bash

   load usb 0:1 90000000 noPK.auth && setenv -e -nv -bs -rt -at -i 90000000:$filesize PK
