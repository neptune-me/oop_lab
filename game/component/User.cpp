#include <iostream>

using namespace std;

class User
{
public:
    string username;
    int score;
    //还剩余的悔棋次数
    int remain_undos;
    User();
    User(string name);
};

User::User()
{
    username = "";
    score = 0;
}

User::User(string name)
{
    username = name;
    score = 0;
}
