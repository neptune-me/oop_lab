#include <iostream>
#include <vector>
#include "math.h"
#include "Board.h"
#include "parameter.h"

using namespace std;
Board::Board(const Board &board)
{
    this->row = board.row;
    this->col = board.col;
    this->mres = board.mres;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            data[i][j] = board.data[i][j];
        }
    }
}
Board::Board(int r, int c)
{
    row = r;
    col = c;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            data[i][j] = 0;
        }
    }
    data[0][0] = 2;
}

void Board::fill_with_2_report(int (&row_col)[2])
{
    int i;
    int j;
    while (true)
    {

        i = rand() % this->row;
        j = rand() % this->col;
        if (this->data[i][j] == 0)
        {
            break;
        }
    }
    this->data[i][j] = 2;

    row_col[0] = i;
    row_col[1] = j;
}

void Board::fill_with_2()
{

    int i;
    int j;
    while (true)
    {

        i = rand() % this->row;
        j = rand() % this->col;
        if (this->data[i][j] == 0)
        {
            break;
        }
    }
    this->data[i][j] = 2;
}

Board::MRes Board::move(string command)
{
    //调试：AvaiDirs
    //vector<string> dirs = GetAvaiDirs();

    int direction = 0;
    if (command == "w")
    {
        direction = UP;
    }
    else if (command == "a")
    {
        direction = LEFT;
    }
    else if (command == "s")
    {
        direction = DOWN;
    }
    else if (command == "d")
    {
        direction = RIGHT;
    }
    else
    {
        cout << "Invalid command!";
        exit(0);
    }
    // this->DeleteZero(Board, direction);
    // this->Merge(Board, direction);
    // this->DeleteZero(Board, direction);
    bool hasZero;
    bool Merged;
    hasZero = this->DeleteZero(direction);
    Merged = this->Merge(direction);
    this->mres.hasChanged = hasZero || Merged;
    hasZero = this->DeleteZero(direction);
    this->mres.hasChanged = hasZero || this->mres.hasChanged;
    return this->mres;
}

//获取某个方向的每一排数字 用vector装
vector<vector<int>> Board::getLinesAtdir(int dir)
{
    int(*Board)[MAX_SIZE];
    Board = this->data;
    vector<vector<int>> lines;
    vector<int> line;
    switch (dir)
    {
    case UP:
        //遍历每一列
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //遍历某一列的4行
            for (int i = BOARD_SIZE - 1; i >= 0; i--)
            {
                line.push_back(Board[i][j]);
            }
            lines.push_back(line);
            line.clear();
        }
        break;
    case DOWN:
        //遍历每一列
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                line.push_back(Board[i][j]);
            }
            lines.push_back(line);
            line.clear();
        }
        break;
    case RIGHT:
        //遍历每一行
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            //遍历某一行的4列 可以从第二列开始 因为第一列往左移没变化
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                line.push_back(Board[i][j]);
            }
            lines.push_back(line);
            line.clear();
        }
        break;

    case LEFT:
        //遍历每一行
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            //遍历某一行的4列
            for (int j = BOARD_SIZE - 1; j >= 0; j--)
            {
                line.push_back(Board[i][j]);
            }
            lines.push_back(line);
            line.clear();
        }
        break;
    default:
        break;
    }

    return lines;
}

bool Board::ParseLines(int dir)
{

    bool res = false;
    vector<vector<int>> lines = this->getLinesAtdir(dir);
    for (auto iter = lines.cbegin(); iter != lines.cend(); iter++)
    {
        res = this->ParseLine(*iter);
        if (res == true)
        {
            break;
        }
    }
    return res;
}
/*
 * 棋盘某行数字为 0 2 2 4 ，则row_p = 224 ， row_p_r = 422。
 * 通过row_p/col_p来判断是否可以朝对应方向移动； 1.是某连续两位数字相同的非零整数，则可以移动2个方向；2.某一位是数字0。
 */
vector<string> Board::GetAvaiDirs()
{

    vector<vector<int>> lines;
    vector<string> AvaiDirs;

    if (ParseLines(UP))
    {
        AvaiDirs.push_back("w");
    }
    if (ParseLines(LEFT))
    {
        AvaiDirs.push_back("a");
    }
    if (ParseLines(RIGHT))
    {
        AvaiDirs.push_back("d");
    }
    if (ParseLines(DOWN))
    {
        AvaiDirs.push_back("s");
    }

    return AvaiDirs;
}
bool Board::Merge(int direction)
{
    //Board指向数组 data 的开头，也即第 0 行；Board+1前进一行，指向第 1 行。
    int(*Board)[MAX_SIZE];
    Board = this->data;

    bool hasChanged = false;
    int thisRound = 0;

    switch (direction)
    {
    case UP:
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //一列从最上面一行的格子开始往下合并，这是最上面那一行
            int curPos = 0;
            int cur = Board[curPos][j];
            int nextPos = curPos + 1;
            while (curPos < BOARD_SIZE)
            {
                cur = Board[curPos][j];
                nextPos = curPos + 1;
                if ((cur != 0) && (cur == Board[nextPos][j]))
                {
                    hasChanged = true;
                    Board[curPos][j] *= 2;
                    thisRound += Board[curPos][j];
                    Board[nextPos][j] = 0;
                    curPos = curPos + 2;
                }
                else
                {
                    curPos += 1;
                }
            }
        }
        break;
    case DOWN:
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //一列从最上面一行的格子开始往下合并，这是最上面那一行
            int curPos = BOARD_SIZE - 1;
            int cur = Board[curPos][j];
            //
            int nextPos = curPos + 1;
            while (curPos > 0)
            {
                cur = Board[curPos][j];
                nextPos = curPos - 1;
                if ((cur != 0) && (cur == Board[nextPos][j]))
                {
                    hasChanged = true;
                    Board[curPos][j] *= 2;
                    thisRound += Board[curPos][j];
                    Board[nextPos][j] = 0;
                    curPos = curPos - 2;
                }
                else
                {
                    curPos -= 1;
                }
            }
        }
        break;

    case LEFT:
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            //一行从最左边一列的格子开始往左合并，这是最左边一列
            int curPos = 0;
            int cur = Board[i][curPos];
            //
            int nextPos = curPos + 1;
            while (curPos < BOARD_SIZE)
            {
                cur = Board[i][curPos];
                nextPos = curPos + 1;
                if ((cur != 0) && (cur == Board[i][nextPos]))
                {
                    hasChanged = true;
                    Board[i][curPos] *= 2;
                    thisRound += Board[i][curPos];
                    Board[i][nextPos] = 0;
                    curPos = curPos + 2;
                }
                else
                {
                    curPos += 1;
                }
            }
        }
        break;

    case RIGHT:
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            //一行从最左边一列的格子开始往左合并，这是最左边一列
            int curPos = BOARD_SIZE - 1;
            int cur = Board[i][curPos];
            //
            int nextPos = curPos - 1;
            while (curPos > 0)
            {
                cur = Board[i][curPos];
                nextPos = curPos - 1;
                if ((cur != 0) && (cur == Board[i][nextPos]))
                {
                    hasChanged = true;
                    Board[i][curPos] *= 2;
                    thisRound += Board[i][curPos];
                    Board[i][nextPos] = 0;
                    curPos = curPos - 2;
                }
                else
                {
                    curPos -= 1;
                }
            }
        }
        break;
    default:
        break;
    }
    //cout << this->mres.hasChanged << endl;
    this->mres.thisRound = thisRound;

    return hasChanged;
}

bool Board::DeleteZero(int direction)
{
    int(*Board)[MAX_SIZE];
    Board = this->data;
    //移动所有的格子 让其靠在一起
    bool hasChanged = false;

    switch (direction)
    {
    case UP:
        //遍历每一列
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //遍历某一列的4行
            for (int i = 0; i < BOARD_SIZE; i++)
            {

                //找到最早出现的空格 之后最早出现的有数字格子移动过来 下面的格子以此类推
                if (Board[i][j] == 0)
                {
                    for (int k = i + 1; k < BOARD_SIZE; k++)
                    {
                        if (Board[k][j] != 0)
                        {
                            hasChanged = true;
                            Board[i][j] = Board[k][j];
                            Board[k][j] = 0;
                            i++;
                        }
                    }
                    break;
                }
            }
            //合并
            //Merge(Board, direction);
        }
        break;
    case DOWN:
        //遍历每一列
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            //遍历某一列的4行
            for (int i = BOARD_SIZE - 1; i >= 0; i--)
            {

                //最靠下的有数字的格子 移到最后一行
                if (Board[i][j] == 0)
                {
                    for (int k = i - 1; k >= 0; k--)
                    {

                        //如果格子里是0 说明这个格子是空的 移动之后不能有空格子存在 那么不填
                        if (Board[k][j] != 0)
                        {
                            hasChanged = true;
                            Board[i][j] = Board[k][j];
                            Board[k][j] = 0;
                            i--;
                        }
                    }
                    break;
                }
            }
            //合并
            //Merge(Board, direction);
        }
        break;
    case LEFT:
        //遍历每一行
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            //遍历某一行的4列 可以从第二列开始 因为第一列往左移没变化
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                int col = 0;
                //最靠左的有数字的格子 移到第一列
                if (Board[i][j] == 0)
                {
                    for (int k = j + 1; k < BOARD_SIZE; k++)
                    {
                        if (Board[i][k] != 0)
                        {
                            hasChanged = true;
                            Board[i][j] = Board[i][k];
                            Board[i][k] = 0;
                            j++;
                        }
                    }
                    break;
                }
            }
            //合并
            //Merge(Board, direction);
        }
        break;

    case RIGHT:
        //遍历每一行
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            //遍历某一行的4列
            for (int j = BOARD_SIZE - 1; j >= 0; j--)
            {
                //最靠右的有数字的格子 移到最后一列
                if (Board[i][j] == 0)
                {
                    for (int k = j - 1; k >= 0; k--)
                    {
                        if (Board[i][k] != 0)
                        {
                            hasChanged = true;
                            Board[i][j] = Board[i][k];
                            Board[i][k] = 0;
                            j--;
                        }
                    }
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
    // cout << this->mres.hasChanged << endl;
    // this->mres.hasChanged = hasChanged ? true : this->mres.hasChanged;
    //cout << "hasZero:" << hasChanged << endl;
    return hasChanged;
}

/*
 * 判断这一排数字 1.是否存在某连续两个相同的非零数字 2.某个数字是0。
 * @param vector<int>  需要判断的整数们
 * @return bool 存在以上两种情况返回true
 */
bool Board::ParseLine(const vector<int> positionorigin)
{
    int curr_p = -1;
    int prev_p = -1;
    int i = 0;
    vector<int> position = positionorigin;
    for (auto iter = position.cbegin(); iter != position.cend(); iter++)
    {
        prev_p = curr_p;
        curr_p = *iter;

        //cout << "position:" << *iter << endl;
        //首位为0，忽略
        if (i == 0 && curr_p == 0)
        {
            position.erase(position.begin());
            return ParseLine(position);
        }
        if (curr_p == 0)
        {
            return true;
        }
        //cout << "p:" << prev_p;
        if (curr_p == prev_p)
        {
            return true;
        }
        i++;
    }
    return false;
}
