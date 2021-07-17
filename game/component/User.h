#ifndef USER_H
#define USER_H

using namespace std;

class User
{
public:
    string username;
    int score;
    int remain_undos;
    User();
    User(string name);
    // User(string name, int remain);
    User(string name, int remain) : username(name), remain_undos(remain), score(0){};
};

#endif