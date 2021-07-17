#include <iostream>
#include "game.h"
#include "component/User.h"
#include "component/Bonus.h"

using namespace std;

class DoubleGame : public Game
{
public:
    DoubleGame(int dest, int size, User users[]);

    DoubleGame(int dest, int size, std::string name1, std::string name2);

    void print() override;

    void printWinner() override;

    void printCurrentPlayer();

    void handleInput() override;

    void handleInput(string ch);

    void undo() override;

    ~DoubleGame()
    {
        this->deleteAllNodes();
        //delete[] users;
    }

private:
    User users[2];
    int CurrentUser;
    int cheatUser;
    bool cheatValid;
    bool cheatDoing;
    string requirement;
    //打印玩家名字和分数
    void printInfo();
    void changePlayer();
    void addScore(int thisRound) override;
    void deleteScore(int thisRound);
    void TriggerCheating(string direc);
    void CheckCheat();
    bool printUndo();
};
