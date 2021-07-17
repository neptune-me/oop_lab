#include <iostream>
#include "ObtainBonusAction.h"
#include <windows.h>

using namespace std;
//两次移动的时间差
int ObtainBonusAction::getDiff(SYSTEMTIME now, SYSTEMTIME last)
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

// ObtainBonusAction::ObtainBonusAction(User &player, SYSTEMTIME thistime, SYSTEMTIME lasttime) : PlayerAction(Bonus, player)
// {
//     duration = getDiff(thistime, lasttime);
// }
void ObtainBonusAction::execute(Board *board)
{

    //调试
    //cout << "millisecs:" << diffsecs << endl;
    if (duration != -1)
    { //有加分
        this->player.score += 1;
        this->thisRound = 1;
        board->mres.thisRound += 1;
    }
}

void ObtainBonusAction::undo(Board *board)
{
    //扣分
    this->player.score -= 1;
    this->thisRound = (-1);
}