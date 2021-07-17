#include <iostream>
#include <windows.h>
#include "MoveAction.h"
using namespace std;
//静态vector成员的定义 注意名字空间
vector<Board> MoveAction::history_boards;
void updateBoard(Board last_board, Board *board); //声明更新棋盘函数
void MoveAction::addScore(int thisRound)
{
    this->player.score += thisRound;
    this->thisRound = thisRound;
}
void MoveAction::deductScore(int thisRound)
{
    this->player.score -= thisRound;
    this->thisRound = (-1) * thisRound;
}
void MoveAction::execute(Board *board)
{
    //存入历史棋盘
    MoveAction::history_boards.push_back(*board);

    //移动
    Board::MRes mres = board->move(this->direc);
    //加分
    this->addScore(mres.thisRound);
    //生成随机的2
    if (mres.hasChanged == true)
    {
        board->fill_with_2();
    }
    //记录移动的时间，精确到毫秒
    SYSTEMTIME lt;
    GetLocalTime(&lt);
    this->ActionTime = lt;
}

void MoveAction::undo(Board *board)
{
    //将历史棋盘中最近添加的棋盘弹出来
    Board last_board = MoveAction::history_boards.back();
    MoveAction::history_boards.pop_back();

    //扣分
    this->deductScore(this->thisRound);
    //将Game所存board更新
    //Board *newboard = new Board(last_board);
    // cout << board->data[2][0];

    //board = new Board(last_board);
    updateBoard(last_board, board);

    //board = newboard;
    //悔棋次数-1
    this->player.remain_undos -= 1;
}
void updateBoard(Board last_board, Board *board)
{
    for (int i = 0; i < board->row; i++)
    {
        for (int j = 0; j < board->col; j++)
        {

            board->data[i][j] = last_board.data[i][j];
        }
    }
    board->mres = last_board.mres;
}
