#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ULL unsigned long long 

using namespace std;

void convertMap(vector<vector<char>>& a)
{
    vector<vector<char>> newMap;

    for (int i = 0; i < a.size(); i++)
    {
        vector<char> row;
        for (int j = 0; j < a[0].size(); j++)
        {
            switch (a[i][j])
            {
                case '#':
                    row.push_back('#');
                    row.push_back('#');
                    break;
                case 'O':
                    row.push_back('[');
                    row.push_back(']');
                    break;
                case '.':
                    row.push_back('.');
                    row.push_back('.');
                    break;
                case '@':
                    row.push_back('@');
                    row.push_back('.');
                    break;
            }
        }
        newMap.push_back(row);
    }
    a.assign(newMap.begin(), newMap.end());
}

int move(int x, int y, int dir, vector<vector<char>>& a, bool dry)
{
    int x2 = x + ((dir % 2) ? 0 : ((dir) ? 1 : -1));
    int y2 = y + (!(dir % 2) ? 0 : ((dir == 1) ? 1 : -1));

    if (a[x][y] == '.')
        return 1;
    if (a[x2][y2] == '#' || a[x][y] == '#')
        return 0;

    if (!(dir % 2) && ((a[x][y] == '[' && a[x][y + 1] == ']') || 
        (a[x][y] == ']' && a[x][y - 1] == '[') || 
        (a[x][y] == ']' && a[x][y - 1] == 'O')))
    {
        if (a[x][y] == '[')
        {
            if (move(x2, y2, dir, a, true) && move(x2, y2 + 1, dir, a, true))
            {
                if (!dry)
                {
                    move(x2, y2, dir, a, false);
                    move(x2, y2 + 1, dir, a, false);
                    a[x2][y2] = a[x][y];
                    a[x2][y2 + 1] = a[x][y + 1];
                    a[x][y] = a[x][y + 1] = '.';
                }
                return 1;
            }
            return 0;
        }
        else if (a[x][y] == ']')
        {
            if (move(x2, y2, dir, a, true) && move(x2, y2 - 1, dir, a, true))
            {
                if (!dry)
                {
                    move(x2, y2, dir, a, false);
                    move(x2, y2 - 1, dir, a, false);
                    a[x2][y2] = a[x][y];
                    a[x2][y2 - 1] = a[x][y - 1];
                    a[x][y] = a[x][y - 1] = '.';
                }
                return 1;
            }
            return 0;
        }
    }

    if (a[x2][y2] == '.')
    {
        if (!dry)
        {
            a[x2][y2] = a[x][y];
            a[x][y] = '.';
            if (!(dir % 2))
            {
                if (a[x2][y2] == '[' && a[x][y + 1] == ']')
                    move(x, y + 1, dir, a, false);
                else if (a[x2][y2] == ']' && a[x][y - 1] == '[')
                    move(x, y - 1, dir, a, false);
            }
        }
        else
        {
            if (a[x][y] == '[' && a[x][y + 1] == ']')
            {
                a[x][y] = 'O';
                int ret = move(x, y + 1, dir, a, true);
                a[x][y] = '[';
                return ret;
            }
            else if (a[x][y] == ']' && a[x][y - 1] == '[')
                return move(x, y - 1, dir, a, true);
        }
        return 1;
    }
    else
    {
        if (!move(x2, y2, dir, a, dry))
            return 0;
        a[x2][y2] = a[x][y];
        a[x][y] = '.';
        return 1;
    }
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<vector<char>> a;
    vector<char> moves;

    if (!input_file) 
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(input_file, line)) 
    {
        if (line.empty())
            break;
        vector<char> row(line.begin(), line.end());
        a.push_back(row);
    }

    while (getline(input_file, line)) 
    {
        for (char c : line)
        {
            moves.push_back(c);
        }
    }
    input_file.close();

    convertMap(a);

    int x = 0, y = 0, dir = 0;
    ULL sum = 0;

    for (int i = 0; i < a.size(); i++) 
    {
        for (int j = 0; j < a[i].size(); j++) 
        {
            if (a[i][j] == '@') 
            {
                x = i;
                y = j;
                break;
            }
        }
    }

    for (char mv : moves) 
    {
        switch (mv) 
        {
            case '^': dir = 0; break;
            case '>': dir = 1; break;
            case 'v': dir = 2; break;
            case '<': dir = 3; break;
            default:
                cerr << "Invalid direction: " << mv << endl;
                return 1;
        }

        if (move(x, y, dir, a, false))
        {
            if (dir == 0) x--;
            else if (dir == 1) y++;
            else if (dir == 2) x++;
            else if (dir == 3) y--;
        }
    }

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i][j] == '[')
                sum += 100 * i + j;
        }
    }

    /*
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
    */

    printf("sum: %llu\n", sum);
}
