#ifndef GAME_H
#define GAME_H

#include "component/Board.h"
#include "component/User.h"
#include "component/GameObserver.h"
#include "component/Bonus.h"
#include <windows.h>

class Game
{
public:
    Board *board;

    vector<User> users;

    Game(int dest, int size);
    //virtual void PrintScore(int mode, User(&user), int thisRound);

    //打印当前的棋盘和分数信息
    virtual void print(){};

    //输出游戏结束后胜利的信息
    virtual void printWinner(){};

    //打印当前的棋盘
    void printBoard();

    virtual void handleInput(){};

    virtual void handleInput(string input, string output){};

    virtual void addScore(int thisRound){};

    //virtual void AddBonus(Movement *thismove){};

    virtual void Move(string ch){};

    bool isOver();

    //开启或不开启日志
    bool turnOnLog(bool log);

    time_t setMoveTime();

    bool reward = false;
    bool log = false;

    //增加观察者
    void addMoveObserver(GameObserver *observer);
    void addBonusObserver(GameObserver *observer);

    //更新上次移动时间
    void updateLastTime(SYSTEMTIME time);
    //悔棋
    virtual void undo(){};

private:
    //int size; //棋盘的长宽
    int dest;
    void fill_with_2();

protected:
    int size;
    //上一次输入（单人模式是当前玩家，双人模式是上一位玩家）的时间
    SYSTEMTIME LastActionTime = {0};

    //Movement *movement;

    //观察者
    vector<GameObserver *> MoveObservers;
    vector<GameObserver *> BonusObservers;

    //触发奖励行为
    //void AddBonus(Movement *thismove);
    //历史棋盘，每次移动把棋盘存进去
    vector<Board> history_boards;
    //总共悔棋次数
    const int total_undos = 3;
    //还剩余的悔棋次数
    // int remain_undos = total_undos;
    void updateBoard(Board board);

    void deleteAllNodes();
    //执行某action
    void executeAction(PlayerAction &pa);
    void undoAction(PlayerAction *action);

    // //存每一次的MoveAction
    vector<PlayerAction *> LastActions;
    //计算时间差（单位为毫秒）
    int getDiff(SYSTEMTIME now, SYSTEMTIME last);
    //取出上一个玩家的所有action
    vector<PlayerAction *> getLastActions();
};

#endif