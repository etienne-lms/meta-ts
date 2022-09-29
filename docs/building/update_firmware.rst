#####################
Updating the firmware
#####################

Generating capsules
*******************

Capsules will automatically be built along with the firmware files.
You can find them in the boards build directory
`build/tmp/deploy/images/<machine>/<machine>_fw.capsule`

Applying capsules from the command line
***************************************

- Copy the capsules in the ESP in the ``\EFI\UpdateCapsule`` directory
- Since the ``\EFI\UpdateCapsule`` is only checked for capsules within
  the device that an active boot option is specified,  make sure your
  ``BootOrder`` variables are correctly set.  Alternatively tou can set
  ``BootNext`` variable with (assumin the capsule is on your mmc)
  ``efidebug boot add -b 1001 cap mmc 1:1 EFI/UpdateCapsule && efidebug boot next 1001``
- In U-Boot console issue
  ``setenv -e -nv -bs -rt -v OsIndications =0x0000000000000004``
- Reboot the board the capsules should be detected and applied.
  Alternatively you can manually apply the capsules with
  ``efidebug capsule disk-update`` using the U-Boot console.

If processing the capsule is sucessful you should see something like
the following in the log.

.. code-block:: bash

  Applying capsule <capsule file> succeeded
  Reboot after firmware update
  resetting ...

More information about capsules and uefi in U-Boot can be found
`here <https://u-boot.readthedocs.io/en/latest/develop/uefi/uefi.html>`_


Applying capsules from the OS
*****************************

Capsule update-on-disk is supported via ``fwupd``.  When ``fwupd`` runs,  it
will copy the firmware files to ``\EFI\UpdateCapsule`` of the ESP.  Once the
board reboots capsule will be applied automatically.
More information can be found
`here <https://github.com/fwupd/fwupd/blob/main/plugins/uefi-capsule/README.md>`_

.. note::
   The EFI Spec mandates: 
   *The directory EFI\UpdateCapsule is checked for capsules only within the EFI
   system partition on the device specified in the active boot option determined
   by reference to BootNext variable or BootOrder variable processing.
   The active Boot Variable is the variable with highest priority BootNext or
   within BootOrder that refers to a device found to be present. Boot 
   variables in BootOrder but referring to devices not present are ignored 
   when determining active boot variable.*

   Since SetVariable at runtime is not yet supported, the only available option
   is place the \EFI\UpdateCapsule within the ESP partition indicated by the 
   current BootOrder.
