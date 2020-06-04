#include "general.h"
#include "utils.h"

int RandomNumber(int l, int h) 
{
    EFI_TIME time;
    EFI_TIME_CAPABILITIES cap;
    gRT->GetTime(&time, &cap); // hopefully this does not fail
    
    int moment = time.Day + time.Hour + time.Minute + time.Second + time.Nanosecond;
    
    int num = moment % (h - l + 1);
    return num + l;
}

void RandomText(char* s, const int len) 
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) 
    {
        s[i] = alphanum[RandomNumber(0, sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}