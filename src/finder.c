#include "general.h"
#include "finder.h"
#include "smbios.h"
#include "edk2/PiHob.h"
#include "hob.h"

EFI_GUID SmbiosTableGuid = { 0xEB9D2D31, 0x2D88, 0x11D3, { 0x9A, 0x16, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D } };
EFI_GUID Smbios3TableGuid = { 0xF2FD1544, 0x9794, 0x4A2C, { 0x99, 0x2E, 0xE5, 0xBB, 0xCF, 0x20, 0xE3, 0x94 } };

#define GET_GUID_HOB_DATA(GuidHob) ((VOID*) (((UINT8*) &((GuidHob)->Name)) + sizeof (EFI_GUID)))

int CheckEntry(SMBIOS_STRUCTURE_TABLE* entry) 
{
    if (!entry)
        return 0;

    char* pointer = (char*)entry;
    int checksum = 0;
    int length = entry->EntryPointLength;
    for (int i = 0; i < length; i++) 
    {
        checksum = checksum + (int)pointer[i];
    }

    return (checksum == 0);
}

void* FindBySignature()
{
    int signature = EFI_SIGNATURE_32('_','S','M','_');
    
    for (long offset = 0xf0000; offset < 0xfffff; offset += 0x10) 
    {
        if (*(int*)(offset) == signature && CheckEntry((SMBIOS_STRUCTURE_TABLE*)offset)) 
        {
            return (void*)offset;
        }
    }

    return 0;
}

void* FindByHob() 
{
    EFI_PHYSICAL_ADDRESS* table;
    EFI_PEI_HOB_POINTERS guidHob;

    guidHob.Raw = GetFirstGuidHob(&SmbiosTableGuid);

    if (guidHob.Raw != 0) 
    {
        table = (EFI_PHYSICAL_ADDRESS*)GET_GUID_HOB_DATA(guidHob.Guid);
        if (table != 0) 
        {
            return (void*)table;
        }
    }

    guidHob.Raw = GetFirstGuidHob(&Smbios3TableGuid);

    if (guidHob.Raw != 0) 
    {
        table = (EFI_PHYSICAL_ADDRESS*)GET_GUID_HOB_DATA(guidHob.Guid);
        if (table != 0) 
        {
            return (void*)table;
        }
    }

    return 0;
}

void* FindByConfig() 
{
    EFI_PHYSICAL_ADDRESS* table;
    EFI_STATUS status = LibGetSystemConfigurationTable(&SmbiosTableGuid, (void**)&table);
    if (status == EFI_SUCCESS)
        return table;

    status = LibGetSystemConfigurationTable(&Smbios3TableGuid, (void**)&table);
    if (status == EFI_SUCCESS)
        return table;

    return 0;
}

SMBIOS_STRUCTURE_TABLE* FindEntry() 
{
    SMBIOS_STRUCTURE_TABLE* address = FindBySignature();
    if (address) 
        return address;      

    address = FindByConfig();
    if (address) 
        return address;

    address = FindByHob();
    if (address) 
        return address;
         
    return 0;
}