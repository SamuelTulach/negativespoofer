#include "general.h"
#include "finder.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) 
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"[WORK] Searching for SMBIOS table entry...\n");
    SMBIOS_STRUCTURE_TABLE* smbiosEntry = FindEntry();
    if (!smbiosEntry) 
    {
        Print(L"[FAIL] Failed to locate SMBIOS table entry\n", smbiosEntry);
        return EFI_NOT_FOUND;
    }
    Print(L"[INFO] SMBIOS table entry found on 0x%08x 0x%08x\n", smbiosEntry, smbiosEntry->TableAddress);  

    Print(L"test: 0x%08x\n", FindTableByType(smbiosEntry, SMBIOS_TYPE_BIOS_INFORMATION, 0));

    return EFI_SUCCESS;
}