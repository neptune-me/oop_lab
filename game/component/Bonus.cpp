#include <iostream>
#include "Bonus.h"
using namespace std;

//两次移动的时间差
int getDiff(SYSTEMTIME now, SYSTEMTIME last)
{
    int diff_milli = now.wMilliseconds - last.wMilliseconds;
    int diff_secs = now.wSecond - last.wSecond;
    int diff_mins = now.wMinute - now.wMinute;
    if (diff_mins < 1)
    {
        if (diff_secs < 1)
        {
            if (diff_milli < 0)
            {
                return (1000 + diff_milli);
            }
            else
            {
                return diff_milli;
            }
        }
        else if (diff_secs == 1)
        {
            if (diff_milli < 0)
            {
                return (1000 + diff_milli);
            }
        }
    }

    return -1;
}