#include <iostream>
#include "SingleGame.h"
#include <fstream>
#include "component/Board.h"
#include "action/MoveAction.h"
#include "action/ObtainBonusAction.h"
#include <windows.h>
using namespace std;
SingleGame::SingleGame(int dest, int size, string name) : Game(dest, size)
{
    this->user = User(name, this->total_undos);
}

void SingleGame::printInfo()
{
    cout << "User:" << this->user.username << endl;
    cout << "Your score:" << this->user.score << endl;
}

void SingleGame::printWinner()
{
    cout << "Game Over" << endl;
}

void SingleGame::print()
{
    this->printInfo();
    this->printBoard();
}

void SingleGame::handleInput()
{
    string ch;
    getline(cin, ch);

    if (ch == "w" || ch == "a" || ch == "s" || ch == "d")
    {
        //创建Move命令
        MoveAction *ma = new MoveAction(ch, this->user);
        //执行
        executeAction(*ma);
        if (this->reward == true)
        {
            int duration = this->getDiff((*ma).ActionTime, this->LastActionTime);
            if (duration != -1)
            {
                ObtainBonusAction *oba = new ObtainBonusAction(this->user, (*ma).ActionTime, duration);
                executeAction(*oba);
            }
        }
        this->LastActionTime = (*ma).ActionTime;
    }
    else
    {
        cout << "INVALID INPUT:" << ch << "" << endl;
        return;
    }
}

void SingleGame::addScore(int thisRound)
{
    this->user.score += thisRound;
}

void SingleGame::undo()
{
    int remain_undos = this->user.remain_undos;
    if (remain_undos == 0)
    {
        return;
    }
    //是否要悔棋 y or n
    cout << this->user.username << "，你是否要悔棋，你还有[" << remain_undos << "]次机会" << endl;
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

        this->print();
        this->undo();
    }
    else if (ans == "n")
    {
        cout << "不用悔棋，请进行操作" << endl;
    }
    else
    {
        cout << "请输入y或n" << endl;
    }
}

void SingleGame::handleInput(string input, string output)
{
    ifstream myfile;
    //读取输入文件，读到迷宫大小，迷宫各格子的数字，移动方向
    try
    {
        myfile.open(input);
    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file";
    }

    string temp;
    int line_num = 0;
    int size;
    int number;  //每个格子的数字
    int inx;     //填入数组的第inx个
    char *direc; //移动迷宫的方向
    vector<int> board_vec;

    while (getline(myfile, temp))
    {
        char *line = (char *)temp.data();

        //调试
        //cout << temp << endl;
        if (line_num == 0)
        {
            size = atoi(line);
            BOARD_SIZE = size;
        }
        else if (line_num <= size)
        {
            char *number_ch = strtok(line, " ");
            while (number_ch != NULL)
            {
                number = atoi(number_ch);
                //调试
                //cout << number << endl;
                board_vec.push_back(number);
                number_ch = strtok(NULL, " ");
            }
        }
        else
        {
            direc = line;
        }
        line_num++;
    }

    //为输入文件中的迷宫创建Board对象：1.提取size 2.提取每个格子的值
    Game *IO2048 = new SingleGame(2048, size, "IO");
    for (int i = 0; i < board_vec.size(); i++)
    {
        int row = i / size;
        int col = i % size;
        IO2048->board->data[row][col] = board_vec[i];
        //调试
        //cout << row << " " << col << " ";
        //cout << "IO2048->board->data[row][col]:" << IO2048->board->data[row][col] << endl;
    }

    //判断迷宫可移动方向
    vector<string> dirs = IO2048->board->GetAvaiDirs();

    //移动迷宫后得到新迷宫，记下新增分数
    Board::MRes mre = IO2048->board->move(direc);

    int score;
    score = mre.thisRound;

    //根据以上信息生成输出文件
    ofstream outputfile;

    try
    {
        outputfile.open(output);
    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file";
    }

    //第一行 4 w a s z
    outputfile << dirs.size() << " ";
    for (auto iter = dirs.cbegin(); iter != dirs.cend(); iter++)
    {
        outputfile << (*iter) << " ";
    }
    outputfile << "\n";
    //第2行到第k+1行，每行k个整数，表示新迷宫。
    int(*Board)[MAX_SIZE];
    Board = IO2048->board->data;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            outputfile << Board[i][j] << " ";
        }
        outputfile << "\n";
    }
    //第k+2行 新生成的整数
    //生成一个随机数，并记录它的位置
    int row_col[2] = {0, 0};
    IO2048->board->fill_with_2_report(row_col);
    outputfile << 2;
    outputfile << "\n";
    //第k+3行包含两个整数x,y，表示该随机数在迷宫中的位置
    outputfile << row_col[0] << " ";
    outputfile << row_col[1];
    outputfile << "\n";
    //第k+4行包含一个整数，表示本次移动后的得分。
    outputfile << score;

    outputfile.close();
    myfile.close();
}