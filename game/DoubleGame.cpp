#ifndef _MOVEMENT_H_

#include <iostream>
#include "DoubleGame.h"
#include "component/Board.h"
#include "action/MoveAction.h"
#include "action/ObtainBonusAction.h"

using namespace std;
bool undo_or_not = false;
DoubleGame::DoubleGame(int dest, int size, User users[]) : Game(dest, size)
{
    //this->users = users;
    this->CurrentUser = 0;
    this->cheatValid = true;
    this->cheatDoing = false;
}

DoubleGame::DoubleGame(int dest, int size, std::string name1, std::string name2) : Game(dest, size)
{
    this->users[0] = User(name1, this->total_undos);
    this->users[1] = User(name2, this->total_undos);
    this->CurrentUser = 0;
    this->cheatValid = true;
    this->cheatDoing = false;
}

bool DoubleGame::printUndo()
{
    int remain_undos = this->users[this->CurrentUser].remain_undos;
    string username = this->users[this->CurrentUser].username;
    if (remain_undos == 0)
    {
        //cout << this->user.username << "不能再悔棋了!" << endl;
        return false;
    }
    //是否要悔棋 y or n
    cout << username << "，你是否要悔棋，你还有[" << remain_undos << "]次机会" << endl;
    string ans;
    getline(cin, ans);
    if (ans == "y")
    {

        return true;
    }
    else
    {
        return false;
    }
}

void DoubleGame::print()
{
    this->printInfo();
    this->printBoard();

    this->printCurrentPlayer();
}

//打印玩家名字和分数
void DoubleGame::printInfo()
{
    cout << "The score of " << (*(this->users)).username << " : " << (*(this->users)).score << endl;
    cout << "The score of " << (*(this->users + 1)).username << " : " << (*(this->users + 1)).score << endl;
}

void DoubleGame::printCurrentPlayer()
{
    cout << "It's " << (this->users[CurrentUser]).username << "'s turn!" << endl;
}

void DoubleGame::changePlayer()
{
    this->CurrentUser = (this->CurrentUser + 1) % 2;
}

void DoubleGame::addScore(int thisRound)
{
    (this->users[CurrentUser]).score += thisRound;
}

void DoubleGame::TriggerCheating(string direc)
{
    //打印一下轮到谁 以及她现在面临的棋盘
    this->printCurrentPlayer();
    this->printBoard();
    cout << this->requirement << " 答应请按" << direc << endl;
    string input;
    while ((!(cin >> input)) || (input != direc))
    {
        cout << this->requirement << " 答应请按" << direc << endl;
        cin.clear();
        cin.ignore(100, '\n');
    }
    cin.ignore(100, '\n');

    //不能再使用作弊功能
    cheatValid = false;
    cheatDoing = false;

    //执行相应的移动
    // this->board->move(direc);
    // this->board->fill_with_2();
    this->handleInput(direc);

    return;
}

void DoubleGame::CheckCheat()
{
    if (this->cheatDoing == false || this->CurrentUser == this->cheatUser)
    {
        return;
    }
    vector<string> AvaiDirs = this->board->GetAvaiDirs();
    string direc = AvaiDirs.at(0);
    //可移动方向只有一个
    if (AvaiDirs.size() == 1)
    {
        this->TriggerCheating(direc);
        return;
    }
}

//显示谁输谁赢
void DoubleGame::printWinner()
{

    if (users[0].score > users[1].score)
    {
        cout << users[0].username << " wins!" << endl;
    }
    else if (users[0].score < users[1].score)
    {
        cout << users[1].username << " wins!" << endl;
    }
    else
    {
        cout << "The game has drawn." << endl;
    }
}

void DoubleGame::handleInput(string ch)
{
    if (ch == "w" || ch == "a" || ch == "s" || ch == "d")
    {
        Board::MRes mres = this->board->move(ch);
        if (mres.hasChanged == true)
        {
            this->board->fill_with_2();
        }
        this->addScore(mres.thisRound);
        //更换玩家
        this->changePlayer();
    }
}

void DoubleGame::deleteScore(int thisRound)
{
    int prevUser = (this->CurrentUser + 1) % 2;
    this->users[prevUser].score -= thisRound;
}

void DoubleGame::undo()
{
    //上一回合a悔棋了 这一回合仍然是a操作且不询问是否悔棋
    int prevUser = (this->CurrentUser + 1) % 2;
    int remain_undos = this->users[prevUser].remain_undos;
    string username = this->users[prevUser].username;
    if (remain_undos == 0)
    {
        return;
    }
    //是否要悔棋 y or n
    cout << username << "，你是否要悔棋，你还有[" << remain_undos << "]次机会" << endl;
    string ans;
    getline(cin, ans);

    if (ans == "y")
    {
        //取出上一次玩家的所有action
        for (auto action : this->getLastActions())
        {
            this->undoAction(action);
            for (auto observer : this->MoveObservers)
            {
                observer->actionUndo(*action);
            }
        }
        this->changePlayer();

        this->print();
        // this->undo();
    }
    else if (ans == "n")
    {
        cout << username << "不用悔棋，请" << this->users[CurrentUser].username << "进行操作" << endl;
        undo_or_not = false;
    }
    else
    {
        cout << "请输入y或n" << endl;
    }
}

void DoubleGame::handleInput()
{
    string ch;
    getline(cin, ch);

    Board::MRes mres;
    // User user = this->users[this->CurrentUser];
    if (ch == "w" || ch == "a" || ch == "s" || ch == "d")
    {
        MoveAction *ma = new MoveAction(ch, this->users[this->CurrentUser]);
        executeAction(*ma);
        if (this->reward == true)
        { //如果打开了奖励功能，则判断是否为快速移动
            int duration = getDiff((*ma).ActionTime, this->LastActionTime);
            if (duration != -1)
            {
                // ObtainBonusAction oba(this->user, ma.ActionTime, duration);
                ObtainBonusAction *oba = new ObtainBonusAction(this->users[this->CurrentUser], (*ma).ActionTime, duration);
                executeAction(*oba);
            }
        }
        this->LastActionTime = (*ma).ActionTime;
        this->changePlayer();
    }
    else if (ch.substr(0, 1) == "c" && this->cheatValid == true)
    {
        int pos = ch.find(' ');
        this->requirement = ch.substr(pos + 1, string::npos);
        //作弊后的操作

        cout << "作弊开启" << endl;
        this->cheatDoing = true;
        this->handleInput();
        return;
    }
    else
    {
        cout << "INVALID INPUT:" << ch << "" << endl;
    }
    //作弊检查
    this->CheckCheat();

    return;
}

#endif