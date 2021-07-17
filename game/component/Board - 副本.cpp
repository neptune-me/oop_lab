#include <iostream>
#include <vector>
#include "math.h"
#include "Board.h"
#include "parameter.h"

using namespace std;

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
            for (auto iter = line.cbegin(); iter != line.cend(); iter++)
            {
                cout << *iter << " ";
            }
            cout << endl;
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

bool Board::ParsePos_Atom(int position, int digits)
{
    //  << "position:" << position << endl;
    if (position < 10)
    {
        return false;
    }
    bool res = false;
    // int digits = this->row;
    int curr_digit = -1;
    int prev_digit = -1;
    int tmp_pos = position;
    //从高位到低位遍历
    for (int i = 0; i < digits; i++)
    {
        prev_digit = curr_digit;
        curr_digit = tmp_pos / (int)pow(10, digits - i - 1);
        tmp_pos = tmp_pos % (int)pow(10, digits - i - 1);
        if (curr_digit == 0 && i == 0) //首位为0,递归判断 如果是002，024这种数字，返回false
        {
            res = ParsePos_Atom(position, digits - 1);
            break;
        }
        if (curr_digit == 0)
        {
            return true;
        }
        if (curr_digit != 0 && curr_digit == prev_digit)
        {
            return true;
        }
    }
    return res;
}
/*
 * 判断各整数 1.是否存在某连续两位数字相同的非零整数 2.某一位是数字0。
 * @param vector<int> & 需要判断的整数们
 * @return bool 存在以上两种情况返回true
 */
bool Board::ParsePos(vector<int> &positions)
{

    bool res = false;
    for (auto iter = positions.cbegin(); iter != positions.cend(); iter++)
    {

        //res = ParsePos_Atom(*iter, this->row) ? true : res;
        res = ParsePos_Atom(*iter, this->row);
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
    int num = 0;
    int row_position = 0; //从第0行往最后一行看每行的数字情况
    int col_position = 0; //从第0列往最后一列看每列的数字情况
    int rev_row_position = 0;
    int rev_col_position = 0;
    vector<int> row_positions;
    vector<int> col_positions;
    vector<int> rev_row_positions;
    vector<int> rev_col_positions;

    int(*Board)[MAX_SIZE];
    Board = this->data;

    for (int i = 0; i < this->row; i++)
    {
        row_position = 0;
        rev_row_position = 0;
        for (int j = 0; j < this->col; j++)
        {
            row_position = 10 * row_position + Board[i][j];
            rev_row_position += Board[i][j] * pow(10, j);
        }
        row_positions.push_back(row_position);
        rev_row_positions.push_back(rev_row_position);
        // cout << row_position << endl;
        // cout << rev_row_position << endl;
    }

    for (int j = 0; j < this->col; j++)
    {
        col_position = 0;
        rev_col_position = 0;
        for (int i = 0; i < this->row; i++)
        {
            col_position = 10 * col_position + Board[i][j];
            rev_col_position += Board[i][j] * pow(10, i);
        }
        col_positions.push_back(col_position);
        rev_col_positions.push_back(rev_col_position);
        //cout << col_position << endl;
        // cout << rev_col_position << endl;
    }

    vector<string> AvaiDirs;
    if (ParsePos(rev_col_positions))
    {
        AvaiDirs.push_back("w");
    }
    if (ParsePos(rev_row_positions))
    {
        AvaiDirs.push_back("a");
    }
    if (ParsePos(row_positions))
    {
        AvaiDirs.push_back("d");
    }
    if (ParsePos(col_positions))
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
