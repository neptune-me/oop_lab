#pragma once
#include <iostream>
#include "PlayerAction.h"

using namespace std;
// int getDiff(SYSTEMTIME now, SYSTEMTIME last)
// {
//     int diff_milli = now.wMilliseconds - last.wMilliseconds;
//     int diff_secs = now.wSecond - last.wSecond;
//     int diff_mins = now.wMinute - now.wMinute;
//     if (diff_mins < 1)
//     {
//         if (diff_secs < 1)
//         {
//             if (diff_milli < 0)
//             {
//                 return (1000 + diff_milli);
//             }
//             else
//             {
//                 return diff_milli;
//             }
//         }
//         else if (diff_secs == 1)
//         {
//             if (diff_milli < 0)
//             {
//                 return (1000 + diff_milli);
//             }
//         }
//     }

//     return -1;
// }
class ObtainBonusAction : public PlayerAction
{
    void addScore(int thisRound);

public:
    int getDiff(SYSTEMTIME now, SYSTEMTIME last);
    int duration;
    ObtainBonusAction(User &player, SYSTEMTIME thistime, int duration) : PlayerAction(Bonus, player), duration(duration)
    {
        this->ActionTime = thistime;
    };
    // ObtainBonusAction(User &player, SYSTEMTIME thistime, SYSTEMTIME lasttime) : PlayerAction(Bonus, player) { this->duration = getDiff(thistime, lasttime); };
    void execute(Board *board) override;
    void undo(Board *board) override;
};