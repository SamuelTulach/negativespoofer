# How to use
First, obtain a copy of hwid.efi ([compile it](pages/LINUX.md) or [download it from release section](https://github.com/SamuelTulach/negativespoofer/releases)) and a copy of [EDK2 efi shell](https://github.com/tianocore/edk2/releases). Now follow these steps:

1. Extract downloaded efi shell and rename file Shell.efi (should be in folder UefiShell/X64) to bootx64.efi
2. Format some USB drive to FAT32
3. Create following folder structure:
```
USB:.
 │   hwid.efi
 │
 └───EFI
      └───Boot
              bootx64.efi
```
4. Boot from the USB drive
5. An UEFI shell should start, change directory to your USB (FS0 should be the USB since we are booting from it) and list files:
```
FS0:
ls
```
6. You should see file hwid.efi, if you do, run it:
```
hwid.efi
```
7. Now you should see a log of the spoofer. If you do and there are no error, it means that it works!
8. Boot the os. Try typing exit and if your OS starts booting without the PC doing a full reboot, you should be fine. If not, you will need to locate bootx64.efi and run it to boot your system.