cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_C_COMPILER /usr/bin/gcc)

project(hwid)

set(EFIBIN "hwid.efi")

include_directories(/usr/include/efi)
include_directories(/usr/include/efi/x86_64)
include_directories(/usr/include/efi/protocol)

link_directories(/usr/lib)

set(COMMONFLAGS "-DGNU_EFI_USE_MS_ABI -fno-stack-protector -fpic -fshort-wchar -mno-red-zone -Wall -Werror")
set(LDFLAGS "-Wl,-nostdlib -Wl,-znocombreloc -Wl,-T,/usr/lib/elf_x86_64_efi.lds -Wl,-shared -Wl,-Bsymbolic,/usr/lib/crt0-efi-x86_64.o -Wl,-lefi -Wl,-lgnuefi") 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 ${COMMONFLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11 ${COMMONFLAGS}")

file(GLOB_RECURSE sourcefiles
    "*.h"
    "*.c"
)

add_library(hwid SHARED ${sourcefiles})
target_link_libraries(hwid ${LDFLAGS})

add_custom_command(
    TARGET hwid POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .reloc --target=efi-app-x86_64 libhwid.so ${EFIBIN} # efi-rtdrv for runtime driver
)
