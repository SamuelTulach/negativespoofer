heavilly inspired by https://github.com/CloverHackyColor/CloverBootloader/blob/22f9adcbc97e1291bc2361d69b66f96a29af0d05/rEFIt_UEFI/Platform/smbios.cpp erfind smbios spooofing

blah blah here

name negative because it's in efi get it?

useful pages
- how to use
- how to compile
- some other crap

# negativespoofer
The name *negative* was my genious idea, because the spoofer runs before the system even boots, that means the time when it's running is negative relatively to system boot time. It fills SMBIOS tables (currently types 0 to 4) with random generated junk. It is heavilly based on [Clover bootloader's SMBIOS patching implementation](https://github.com/CloverHackyColor/CloverBootloader/blob/22f9adcbc97e1291bc2361d69b66f96a29af0d05/rEFIt_UEFI/Platform/smbios.cpp).

<p align="center">
  <img src="img/all.png">
</p>

## Useful links
To make this repo more readable, I made different pages for different topics.
- How to compile (Linux)
- How to compile (Windows)
- How to use
- Reporting issue