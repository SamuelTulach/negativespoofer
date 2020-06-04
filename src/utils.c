#include "general.h"
#include "utils.h"

int lastRandom = 0;
int RandomNumber(int l, int h) 
{
    EFI_TIME time;
    EFI_TIME_CAPABILITIES cap;
    gRT->GetTime(&time, &cap); // hopefully this does not fail

    if (lastRandom == 0) 
    {
        lastRandom = time.Day + time.Hour + time.Minute + time.Second + time.Nanosecond;
    }
    lastRandom += time.Minute;
    
    int num = lastRandom % (h - l + 1);

    return num + l;
}

void RandomText(char* s, const int len) 
{
    for (int i = 0; i < len; i++) 
    {
        s[i] = RandomNumber(49, 90);
    }

    s[len] = 0;
}