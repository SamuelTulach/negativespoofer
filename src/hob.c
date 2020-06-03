#include "general.h"
#include "edk2/PiHob.h"

EFI_GUID HobGuid = { 0x7739f24c, 0x93d7, 0x11d4, {0x9a, 0x3a, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d } };
void* HobList = 0;

#define GET_HOB_TYPE(Hob) ((Hob).Header->HobType)
#define GET_HOB_LENGTH(Hob) ((Hob).Header->HobLength)
#define GET_NEXT_HOB(Hob) ((Hob).Raw + GET_HOB_LENGTH (Hob))
#define END_OF_HOB_LIST(Hob) (GET_HOB_TYPE (Hob) == EFI_HOB_TYPE_END_OF_HOB_LIST)

#define GET_GUID_HOB_DATA(GuidHob) ((VOID *) (((UINT8 *) &((GuidHob)->Name)) + sizeof (EFI_GUID)))
#define GET_GUID_HOB_DATA_SIZE(GuidHob) (((GuidHob)->Header).HobLength - sizeof (EFI_HOB_GUID_TYPE))

void* GetHobList() 
{
    if (!HobList) 
    {
        LibGetSystemConfigurationTable(&HobGuid, &HobList);
    }
    
    return HobList;
}

void* GetNextHob(UINT16 type, void* start) 
{
    EFI_PEI_HOB_POINTERS hob;

    hob.Raw = (UINT8*)start;

    while (!END_OF_HOB_LIST(hob)) 
    {
        if (hob.Header->HobType == type) 
        {
            return hob.Raw;
        }
        
        hob.Raw = GET_NEXT_HOB(hob);
    }

    return 0;
}

void* GetFirstHob(UINT16 type) 
{
    void* list = GetHobList();
    return GetNextHob(type, list);
}

void* GetNextGuidHob(EFI_GUID* guid, void* start) 
{
    EFI_PEI_HOB_POINTERS guidHob;

    guidHob.Raw = (UINT8*)start;

    while ((guidHob.Raw = GetNextHob(EFI_HOB_TYPE_GUID_EXTENSION, guidHob.Raw)) != 0)
    {
        if (CompareGuid(guid, &guidHob.Guid->Name))
        {
            break;
        }

        guidHob.Raw = GET_NEXT_HOB(guidHob);
    }

    return guidHob.Raw;
}

void* GetFirstGuidHob(EFI_GUID* guid) 
{
    void* list = GetHobList();
    return GetNextGuidHob(guid, list);
}