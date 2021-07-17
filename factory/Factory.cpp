#include "Factory.h"
#include "../game/DoubleGame.h"
#include "../game/component/Board.h"
#include <iostream>

using namespace std;

Game *Factory::createIO2048(string input, string output)
{
    cout << "输入文件：" << input << endl;
    cout << "输出文件：" << output << endl;
    return new SingleGame(2048, 0, "IO");
}
/**
 * 产生2048游戏类的工厂函数，根据输入产生单人版游戏和双人版游戏
 * @param dest 合成标号多大的方块就停止游戏
 * @param size 棋盘有多大
 * 
 * @return 游戏实例
 */
Game *Factory::create2048(int dest, int size)
{
    cout << "---------游戏开始----------" << endl;
    cout << "请进行模式选择：" << endl;
    cout << "1.单人模式" << endl;
    cout << "2.双人模式" << endl;
    cout << "请键入对应模式的序号：";

    //检验输入是否合法
    enum validMode
    {
        Single = 1,
        Double = 2,
    };
    int mode;

    while ((!(cin >> mode)) || (mode != Single && mode != Double))
    {
        cout << "Invalid input! Try again!" << endl;
        cin.clear();
        cin.ignore(100, '\n');
    }
    cin.ignore(100, '\n');

    //双人模式下输入用户名
    string username;
    User users[2];
    if (mode == 1)
    {
        return new SingleGame(dest, size, "Default User");
    }
    if (mode == 2)
    {
        string username1, username2;
        cout << "请输入玩家1的名字" << endl;
        cin >> username1;
        cin.sync();
        cout << "请输入玩家2的名字" << endl;
        cin >> username2;
        cin.sync();
        return new DoubleGame(dest, size, username1, username2);
    }
}
