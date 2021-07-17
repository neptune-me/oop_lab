
#include <iostream>
#include "game/component/parameter.h"
#include "game/component/Board.h"
#include "game/component/User.h"
#include "game/component/log.h"
#include <string.h>
#include <getopt.h>
#include "unistd.h"
#include "math.h"
#include "factory/Factory.h"
#include "game/game.h"

#include <stdlib.h>

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

using namespace std;

int BOARD_SIZE = 0;

int main(int argc, char *argv[])
{

    system("chcp 65001");
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpFlag);
    int row = 3;

    //解析命令行
    opterr = 0;
    string input = "";
    string output = "";
    int c;
    int dest = 2048;
    int option_index = 0;
    static struct option long_options[] = {
        {"log", no_argument, NULL, 0}};
    bool log = false;
    bool reward = false;
    while ((c = getopt_long(argc, argv, "s:tc:i:o:p", long_options, &option_index)) != EOF)
    {
        switch (c)
        {
        case 63:
            cout << "日志功能开启" << endl;
            log = true;
            break;
        case 's':
            row = atoi(optarg);
            if (row < 2 || row > 5)
            {
                cout << "Dimension should be one of 3, 4, 5." << endl;
                exit(1);
            }
            //注意把BOARD_SIZE更新
            BOARD_SIZE = row;
            break;
        case 't':
            dest = 64;
            cout << "Testing Mode!" << endl;
            break;
        case 'i': //输入文件名
            input = optarg;
            break;
        case 'o': //输出文件名
            output = optarg;
            break;
        case 'p': //打开奖励功能
            reward = true;
            cout << "奖励功能开启" << endl;
            break;
        default:
            cout << "invalid" << endl;
            exit(1);
        }
    }

    if (input != "")
    {
        Game *game = Factory::createIO2048(input, output);
        game->handleInput(input, output);
        cout << "输出完成" << endl;
        exit(0);
    }

    Game *game = Factory::create2048(dest, row);

    //选择开启日志 奖励功能
    if (reward == true)
    {
        game->reward = true; //开启奖励
    }
    if (log == true)
    {
        Log *logObserver = new Log();
        game->log = true; //开启日志
        game->addMoveObserver(logObserver);
        if (reward == true)
        {
            game->addBonusObserver(logObserver);
        }
    }

    int i = 0;
    string commandline;
    bool over = false;

    game->print();

    while (!over)
    {
        game->handleInput();
        //判断是否结束
        over = game->isOver();
        //计算分数
        game->print();
        game->undo();
        i++;
    }

    game->printWinner();
    delete game;
    return 0;
}
