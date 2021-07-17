#include "../game/SingleGame.h"
#include "../game/game.h"
#include <iostream>

using namespace std;

class Factory
{
public:
    static Game *create2048(int dest, int size);
    static Game *createIO2048(string input, string output);
};