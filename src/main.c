#include "general.h"
#include "finder.h"
#include "patch.h"
#include "smbios.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) 
{
    InitializeLib(ImageHandle, SystemTable);
    
    Print(L"[WORK] Searching for SMBIOS table entry...\n");
    SMBIOS_STRUCTURE_TABLE* smbiosEntry = FindEntry();
    if (!smbiosEntry) 
    {
        Print(L"[FAIL] Failed to locate SMBIOS table entry\n");
        return EFI_NOT_FOUND;
    }
    Print(L"[INFO] SMBIOS table entry found on 0x%08x\n", smbiosEntry->TableAddress);  

    PatchAll(smbiosEntry);

    return EFI_SUCCESS;
}