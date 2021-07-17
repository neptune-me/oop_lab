#pragma once
#include <iostream>
#include "PlayerAction.h"

using namespace std;

class MoveAction : public PlayerAction
{
    void addScore(int thisRound);
    void deductScore(int thisRound);
    //静态变量，与具体实例无关
    static vector<Board> history_boards;

public:
    string direc;
    MoveAction(string direc, User &player) : PlayerAction(Move, player), direc(direc){};
    void execute(Board *board) override;
    void undo(Board *board) override;
};