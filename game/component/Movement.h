#pragma once
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_
#include <iostream>
#include <windows.h>

using namespace std;
//记录用户名，获得加分的时刻，用时(一位小数)，移动棋盘所得分，加分的分数
class Movement
{
public:
    string username;
    SYSTEMTIME MoveTime;
    SYSTEMTIME LastMoveTime;
    string str_MoveTime = "";
    string direc;
    int score;
    Movement(const string &name, SYSTEMTIME now, SYSTEMTIME last, string direc, int score) : username(name), MoveTime(now), LastMoveTime(last), direc(direc), score(score){};
};

#endif