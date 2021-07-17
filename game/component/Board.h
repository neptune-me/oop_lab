#ifndef BOARD_H
#define BOARD_H

#include "parameter.h"
#include <string.h>
#include <vector>

using namespace std;

class Board
{
public:
    struct MRes
    {
        /* data */
        int thisRound = 0;
        bool hasChanged = false;
    };
    int row;
    int col;
    int data[MAX_SIZE][MAX_SIZE];
    Board(int r, int c);
    Board(const Board &board);
    MRes move(string command);
    MRes mres;
    void fill_with_2();
    void fill_with_2_report(int (&row_col)[2]);
    vector<string> GetAvaiDirs();

private:
    bool Merge(int direction);
    bool DeleteZero(int direction);
    vector<vector<int>> getLinesAtdir(int dir);
    bool ParseLine(const vector<int> positionorigin);
    bool ParseLines(int dir);
};

#endif