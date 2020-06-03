# Run in build folder
# Open gdb and type "target remote :1234" to start debbuging
qemu-system-x86_64 -smp 2 -debugcon file:debug.log -global isa-debugcon.iobase=0x402 -L /usr/share/edk2-ovmf/x64/ -bios OVMF.fd -drive file=fat.img,if=ide,id=drive-ide0-0-0,format=raw #-s -S