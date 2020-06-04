# How to compile (Linux)
Compiling this EFI application is incredibly simple. All you need is a working rolling Linux distro.

First download and install gcc, gnu-efi.
```
sudo pacman -S gcc gnu-efi-libs cmake git
```
This should install all required packages that you will need to build.

Clone this repo.
```
git clone https://github.com/SamuelTulach/negativespoofer
```

Change directory to the repo root folder.
```
cd hwid
```

Build the application.
```
./scripts/build.sh
```

Now you should see hwid.efi in the build folder. Congrats!