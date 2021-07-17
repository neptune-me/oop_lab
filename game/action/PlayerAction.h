#pragma once
#include <iostream>
#include <windows.h>
#include "../component/User.h"
#include "../component/Board.h"
using namespace std;

class PlayerAction
{
    //int score;
public:
    enum ActionType
    {
        Move = 1,
        Bonus
    };
    enum ActionType actionType;
    virtual void execute(Board *board){};
    virtual void undo(Board *board) { cout << "enter PA"; };
    PlayerAction(ActionType action, User &currentUser) : actionType(action), player(currentUser){}; //初始化const一定要在初始化列表
    //这一轮加分
    int thisRound;
    User &player;
    SYSTEMTIME ActionTime;
};

// PlayerAction::PlayerAction(ActionType action, User &currentUser)
// {
//     actionType = action;
//     player = currentUser;
// };