#pragma once

#include <iostream>
#include <windows.h>
#include "../action/PlayerAction.h"
using namespace std;
//记录用户名，获得加分的时刻，用时(一位小数)，移动棋盘所得分，加分的分数
// class Movement
// {
// public:
//     string username;
//     SYSTEMTIME MoveTime;
//     SYSTEMTIME LastMoveTime;
//     string str_MoveTime = "";
//     string direc;
//     int score;
//     Movement(const string &name, SYSTEMTIME now, SYSTEMTIME last, string direc, int score) : username(name), MoveTime(now), LastMoveTime(last), direc(direc), score(score){};
//     ~Movement()
//     {
//         //cout << "~movement" << endl;
//         // delete
//     }
// };

// int getDiff(SYSTEMTIME now, SYSTEMTIME last);

// class Bouns : public GameObserver
// {
// public:
//     //Game *game;
//     SYSTEMTIME lastMovementActionTime;
//     void actionPerformed(PlayerAction &action){
//         // if (action.actionType == Move)
//         // {
//         //     timeDuration = getdiff(action.ActionTime, lastMovementActionTime);
//         //     //check movemeent time duration, if bouns criteria is satisfied:
//         //     actionExecuter.execute(new ObtainBounsAction(action.player, timeDuration));
//         // }
//     };
// };
