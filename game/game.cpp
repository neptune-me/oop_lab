#include <iostream>
#include "game.h"
#include "component/Bonus.h"
#include <fstream>
#include <windows.h>

using namespace std;

/**
 * 构造函数。创建一个size*size的游戏，当有方块的值超过dest时，游戏就胜利。
 * @param dest 方块的值超过dest时，游戏就胜利
 * @param size 棋盘的大小
 */
Game::Game(int dest, int size)
{
    this->board = new Board(size, size);
    this->dest = dest;
    this->size = size;
    // GetLocalTime(&this->movement->MoveTime);
}

/*
 * 在棋盘中随机生成一个2
 */
void Game::fill_with_2()
{
    int i;
    int j;
    while (true)
    {

        i = rand() % this->size;
        j = rand() % this->size;
        if (this->board->data[i][j] == 0)
        {
            break;
        }
    }
    this->board->data[i][j] = 2;
}

bool Game::isOver()
{
    bool isOver = true;
    bool isFull = true;
    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < this->size; j++)
        {
            //出现2048或32结束了
            if (this->board->data[i][j] == dest)
            {
                return true;
            }
            //有0肯定没结束
            if (this->board->data[i][j] == 0)
            {
                isOver = false;
                isFull = false;
            }
        }
    }
    if (isFull == true)
    {
        vector<string> dirs = this->board->GetAvaiDirs();
        if (dirs.size() == 0)
        {
            //cout << "enter1" << endl;
            isOver = true;
        }
        else
        {
            isOver = false;
        }
    }
    return isOver;
}

void Game::printBoard()
{
    for (int i = 0; i < 2 * this->size + 1; i++)
    {
        if (i % 2 == 0)
        {
            for (int k = 0; k < this->size; k++)
            {
                cout << "+-----";
            }
            cout << "+" << endl;
            // cout << "+-----+-----+-----+-----+" << endl;
        }
        else
        {
            cout << "|";
            for (int j = 0; j < this->size; j++)
            {
                if (this->board->data[i / 2][j] != 0)
                {
                    cout << "  " << this->board->data[i / 2][j] << "  |";
                }
                else
                {
                    cout << "  "
                         << " "
                         << "  |";
                }
            }
            cout << endl;
        }
    }
}

void Game::addMoveObserver(GameObserver *observer)
{
    this->MoveObservers.push_back(observer);
}

void Game::addBonusObserver(GameObserver *observer)
{
    this->BonusObservers.push_back(observer);
}

void Game::deleteAllNodes()
{
    delete this->board;
    for (auto action : this->LastActions)
    {
        delete action;
    }
    this->LastActions.clear();
}

int Game::getDiff(SYSTEMTIME now, SYSTEMTIME last)
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

void Game::executeAction(PlayerAction &pa)
{
    //将action都存起来
    for (auto observer : this->MoveObservers)
    {
        observer->actionAccepted(pa);
    }
    //执行某action
    pa.execute(this->board);
    //action记录
    LastActions.push_back(&pa);
    //通知观察者
    for (auto observer : this->MoveObservers)
    {
        observer->actionPerformed(pa);
    }
}

void Game::undoAction(PlayerAction *action)
{
    //撤销一次Moveaction：将前一步的board取出来
    //(dynamic_cast<MoveAction *>(action))->undo(this->board);
    (action)->undo(this->board);
}

vector<PlayerAction *> Game::getLastActions()
{

    if (this->LastActions.back()->actionType == PlayerAction::Bonus)
    { //有加分，两个一起撤销
        vector<PlayerAction *> res(this->LastActions.end() - 2, this->LastActions.end());
        this->LastActions.pop_back();
        this->LastActions.pop_back();
        return res;
    }
    else
    { //没有加分，只撤销移动操作
        vector<PlayerAction *> res(this->LastActions.end() - 1, this->LastActions.end());
        this->LastActions.pop_back();
        //cout << res.size();
        return res;
    }
}
