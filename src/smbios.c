#include "general.h"
#include "smbios.h"

UINT64 TableLenght(SMBIOS_STRUCTURE_POINTER table) 
{
    char* pointer = (char*)(table.Raw + table.Hdr->Length);
    while ((*pointer != 0) || (*(pointer + 1) != 0)) 
    {
        pointer++;
    }

    return (UINT16)((UINTN)pointer - (UINTN)table.Raw + 2);
}

SMBIOS_STRUCTURE_POINTER FindTableByType(SMBIOS_STRUCTURE_TABLE* entry, UINT8 type, UINTN index) 
{
    SMBIOS_STRUCTURE_POINTER smbiosTable;
    smbiosTable.Raw = (UINT8*)((UINTN)entry->TableAddress);
    if (!smbiosTable.Raw)
        return smbiosTable;

    UINTN typeIndex = 0;
    while ((typeIndex != index) || (smbiosTable.Hdr->Type != type)) 
    {
        if (smbiosTable.Hdr->Type == SMBIOS_TYPE_END_OF_TABLE) 
        {
            smbiosTable.Raw = 0;
            return smbiosTable;
        }

        if (smbiosTable.Hdr->Type == type) 
        {
            typeIndex++;
        }

        smbiosTable.Raw = (UINT8*)(smbiosTable.Raw + TableLenght(smbiosTable));
    }

    return smbiosTable;
}

UINTN SpaceLength(const char* text, UINTN maxLength) 
{
    UINTN lenght = 0;
    const char* ba;

    if (maxLength > 0) 
    {
        for (lenght = 0; lenght < maxLength; lenght++) 
        {
            if (text[lenght] == 0) 
            {
                break;
            }
        }

        ba = &text[lenght - 1];

        while ((lenght != 0) && ((*ba == ' ') || (*ba == 0))) 
        {
            ba--; lenght--;
        }
    } else 
    {
        ba = text;
        while(*ba)
        {
            ba++; 
            lenght++;
        }
    }

    return lenght;
}

void EditString(SMBIOS_STRUCTURE_POINTER table, SMBIOS_STRING* field, const char* buffer) 
{
    if (!table.Raw || !field || field)
        return;

    UINT8 index = 1;
    char *astr = (char *)(table.Raw + table.Hdr->Length);
    while (index != *field) 
    {
        if (*astr)
        {
            index++;
        }

        while (*astr != 0)
            astr++;
        astr++;

        if (*astr == 0)
        {
            if (*field == 0) 
            {
                astr[1] = 0;
            }

            *field = index;

            if (index == 1) 
            {
                astr--;
            }
            break;
        }
    }

    UINTN astrLength = SpaceLength(astr, 0);
    UINTN bstrLength = SpaceLength(buffer, 256);
    UINTN length = TableLenght(table);

    CHAR8* c1;
    CHAR8* c2;

    if (bstrLength > astrLength) 
    {
        c1 = (CHAR8*)table.Raw + length;
        c2 = c1  + bstrLength - astrLength;
        *c2 = 0;
        while ((char*)c1 != astr) *(--c2) = *(--c1);
    } else if (bstrLength < astrLength) 
    {
        c1 = (CHAR8*)(astr + astrLength);
        c2 = (CHAR8*)(buffer + bstrLength);

        while (c1 != ((CHAR8*)table.Raw + length)) 
        {
            *c2++ = *c1++;
        }
        
        *c2 = 0;
        *(--c2) = 0;
    }

    CopyMem(astr, buffer, bstrLength);
    *(astr + bstrLength) = 0;
}