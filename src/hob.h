#ifndef HOB_H
#define HOB_H

#include "general.h"

void* GetHobList();
void* GetNextHob(UINT16 type, void* start);
void* GetFirstHob(UINT16 type);
void* GetNextGuidHob(EFI_GUID* guid, void* start);
void* GetFirstGuidHob(EFI_GUID* guid);

#endif
