#include <iostream>
#include <fstream>
#include "log.h"
#include "../action/PlayerAction.h"

using namespace std;

ofstream Open(string filename)
{
    ofstream output;
    try
    {
        output.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return output;
}
ofstream output = Open("../log.txt");
string Time(SYSTEMTIME lt)
{
    string mystring;
    FILE *outputfile;
    try
    {
        outputfile = fopen("1.txt", "w");
    }
    catch (const ifstream::failure &e)
    {
        cout << "Exception opening/reading file";
    }

    fwprintf(outputfile, L"%d-%d-%d %02d:%02d:%02d ",
             lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);

    fclose(outputfile);
    ifstream a;
    a.open(
        "1.txt");
    getline(a, mystring);

    return mystring;
}
// void Log::onMove(Movement *move)
// {

//     //用户名
//     ofstream output = Open("../log.txt");
//     output << move->username << " ";
//     //时间
//     string time = Time(move->MoveTime);
//     move->str_MoveTime = time;
//     output << time;
//     //方向
//     output << move->direc << " ";
//     //分数
//     output << move->score;
//     output << endl;
// }

// void Log::onBonus(Movement *move, double diff)
// {
//     //cout << "log bonus";
//     //用户名
//     ofstream output = Open("../log.txt");
//     output << move->username << " ";
//     //时间
//     string time;
//     if (move->str_MoveTime != "")
//     {
//         time = move->str_MoveTime;
//     }
//     else
//     {
//         time = Time(move->MoveTime);
//     }
//     output << time;
//     //用时
//     string str = to_string(diff);
//     str = str.substr(0, 3);
//     output << str << " ";
//     //加分为1
//     output << 1;
//     output << endl;
// }
void Log::actionUndo(PlayerAction &ma)
{
    if (ma.thisRound == 0)
    {
        return;
    }
    //用户名
    output << ma.player.username << " ";
    //记录移动的时间，精确到毫秒
    SYSTEMTIME lt;
    GetLocalTime(&lt);
    //时间
    string time = Time(lt);
    output << time;
    //分数
    output << ma.thisRound;
    output << endl;
}

void Log::actionPerformed(PlayerAction &ma)
{

    if (ma.actionType == PlayerAction::Move)
    {
        if (ma.thisRound != 0)
        {
            auto newma = dynamic_cast<MoveAction &>(ma);
            //用户名
            //ofstream output = Open("../log.txt");
            output << newma.player.username << " ";
            //时间
            string time = Time(newma.ActionTime);
            // move->str_MoveTime = time;
            output << time;
            //方向
            output << newma.direc << " ";
            //分数
            output << newma.thisRound;
            output << endl;
        }
    }
    else if (ma.actionType == PlayerAction::Bonus)
    {
        auto newma = dynamic_cast<ObtainBonusAction &>(ma);
        //用户名
        //ofstream output = Open("../log.txt");
        output << newma.player.username << " ";
        //时间
        string time;
        time = Time(newma.ActionTime);
        output << time;
        //用时
        string str = to_string(newma.duration / 1000.0);
        str = str.substr(0, 3);
        output << str << " ";
        //加分为1
        output << 1;
        output << endl;
    }
    // //用户名
    // ofstream output = Open("../log.txt");
    // output << move->username << " ";
    // //时间
    // string time = Time(move->MoveTime);
    // move->str_MoveTime = time;
    // output << time;
    // //方向
    // output << move->direc << " ";
    // //分数
    // output << move->score;
    // output << endl;
}