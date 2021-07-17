//把游戏中发生的关键事件暴露给所有GameObserver，
#pragma once
#include <iostream>
#include "Bonus.h"
#include "../action/PlayerAction.h"
using namespace std;

class GameObserver
{
    vector<PlayerAction> actions;

public:
    // virtual void onMove(Movement *move) = 0;
    // virtual void onBonus(Movement *move, double diff) = 0;
    // virtual void onUndo(int thisRound, string username) = 0;

    virtual void actionPerformed(PlayerAction &pa){};
    virtual void actionAccepted(PlayerAction &pa)
    {
        actions.push_back(pa);
    };
    virtual void actionUndo(PlayerAction &ma){};
};