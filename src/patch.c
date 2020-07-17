#include "general.h"
#include "patch.h"
#include "smbios.h"
#include "utils.h"

void EditRandom(SMBIOS_STRUCTURE_POINTER table, SMBIOS_STRING* field) 
{
    char buffer[258];
    RandomText(buffer, 257);

    if (field) 
    {
        EditString(table, field, buffer);
    } 
}

void PatchType0(SMBIOS_STRUCTURE_TABLE* entry) 
{
    SMBIOS_STRUCTURE_POINTER table = FindTableByType(entry, SMBIOS_TYPE_BIOS_INFORMATION, 0);
    Print(L"[WORK] Patching type0 table at 0x%08x...\n", table);

    if (!table.Type0) 
    {
        Print(L"[FAIL] Table is non existent\n");
        return;
    }

    EditRandom(table, &table.Type0->Vendor);
    EditRandom(table, &table.Type0->BiosVersion);
    EditRandom(table, &table.Type0->BiosReleaseDate);

    Print(L"[INFO] Patched type0 table\n");
}

void PatchType1(SMBIOS_STRUCTURE_TABLE* entry) 
{
    SMBIOS_STRUCTURE_POINTER table = FindTableByType(entry, SMBIOS_TYPE_SYSTEM_INFORMATION, 0);
    Print(L"[WORK] Patching type1 table at 0x%08x...\n", table);

    if (!table.Type1) 
    {
        Print(L"[FAIL] Table is non existent\n");
        return;
    }

    EditRandom(table, &table.Type1->Manufacturer);
    EditRandom(table, &table.Type1->ProductName);
    EditRandom(table, &table.Type1->Version);
    EditRandom(table, &table.Type1->SerialNumber);

    Print(L"[INFO] Patched type1 table\n");
}

void PatchType2(SMBIOS_STRUCTURE_TABLE* entry) 
{
    SMBIOS_STRUCTURE_POINTER table = FindTableByType(entry, SMBIOS_TYPE_BASEBOARD_INFORMATION, 0);
    Print(L"[WORK] Patching type2 table at 0x%08x...\n", table);

    if (!table.Type2) 
    {
        Print(L"[FAIL] Table is non existent\n");
        return;
    }

    EditRandom(table, &table.Type2->Manufacturer);
    EditRandom(table, &table.Type2->ProductName);
    EditRandom(table, &table.Type2->Version);
    EditRandom(table, &table.Type2->SerialNumber);

    Print(L"[INFO] Patched type2 table\n");
}

void PatchType3(SMBIOS_STRUCTURE_TABLE* entry) 
{
    SMBIOS_STRUCTURE_POINTER table = FindTableByType(entry, SMBIOS_TYPE_SYSTEM_ENCLOSURE, 0);
    Print(L"[WORK] Patching type3 table at 0x%08x...\n", table);

    if (!table.Type3) 
    {
        Print(L"[FAIL] Table is non existent\n");
        return;
    }

    EditRandom(table, &table.Type3->Manufacturer);
    EditRandom(table, &table.Type3->Version);
    EditRandom(table, &table.Type3->SerialNumber);
    EditRandom(table, &table.Type3->AssetTag);

    Print(L"[INFO] Patched type3 table\n");
}

void PatchAll(SMBIOS_STRUCTURE_TABLE* entry) 
{
    PatchType0(entry);
    PatchType1(entry);
    PatchType2(entry);
    PatchType3(entry);
}