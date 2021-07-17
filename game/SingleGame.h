#include <iostream>
#include "game.h"
#include "component/User.h"
#include "action/MoveAction.h"

using namespace std;

class SingleGame : public Game
{
public:
    SingleGame(int dest, int size, string name);

    void print() override;

    void printWinner() override;

    //void printCurrentPlayer() override;

    void handleInput() override;

    void handleInput(string input, string output) override;

    void undo() override;

    ~SingleGame()
    {
        this->deleteAllNodes();
    }

private:
    User user;

    //打印玩家名字和分数
    void printInfo();

    void addScore(int thisRound) override;
};
