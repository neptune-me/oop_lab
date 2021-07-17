#include <iostream>
#include "GameObserver.h"
#include "../action/MoveAction.h"
#include "../action/ObtainBonusAction.h"
using namespace std;

class Log : public GameObserver
{
    // Game *game;
    //日志文件
    const char *logFile = "log.txt";

public:
    // //将*得分*移动操作记录到日志文件里面
    // void onMove(Movement *move) override;

    // //将*奖励*记录到日志文件里面 {用户名} {时间} {用时} {分数} 用时为小于1的
    // void onBonus(Movement *move, double diff) override;

    // void onUndo(int thisRound, string username) override;

    void actionPerformed(PlayerAction &ma) override;
    void actionUndo(PlayerAction &ma) override;
};