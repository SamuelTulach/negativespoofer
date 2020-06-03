# Run in build folder
dd if=/dev/zero of=fat.img bs=1k count=1440
mformat -i fat.img -f 1440 ::
mmd -i fat.img ::/EFI
mmd -i fat.img ::/EFI/BOOT
echo "\hwid.efi" > startup.nsh
mcopy -i fat.img startup.nsh ::/
mcopy -oi fat.img hwid.efi ::/hwid.efi
mcopy -oi fat.img ../pkg/Shell.efi ::/EFI/BOOT/BOOTX64.EFI