#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ULL unsigned long long

using namespace std;

pair<int, int> getDir(char ch)
{
    switch (ch)
    {
        case '^':
            return make_pair(-1, 0);
        case '>':
            return make_pair(0, 1); 
        case 'v':
            return make_pair(1, 0); 
        case '<':
            return make_pair(0, -1);
    }
    return {0, 0};
}

bool isValid(int x, int y, const vector<vector<char>>& a)
{
    if (x >= 0 && x < a.size() && y >= 0 && y < a[0].size())
    {
        if (a[x][y] != '#')
        {
            return true;
        }
    }
    return false;

}

bool isThereSpaceToPushBoxes(const int& x, const int& y, const vector<vector<char>>& a, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x+dx;
    int ny = y+dy;
    while (isValid(nx, ny, a))
    {
        if (a[nx][ny] == '.')
            return true;
        nx += dx;
        ny += dy;
    }
    return false;
}

void pushBoxes(int& x, int& y, vector<vector<char>>& a, char dir) 
{
    auto [dx, dy] = getDir(dir);

    if (!isThereSpaceToPushBoxes(x, y, a, dir)) 
    {
        return; 
    }

    int nx = x + dx;
    int ny = y + dy;
    
    a[x][y] = '.';
    x = nx;
    y = ny;

    int boxes = 0;

    while (a[nx][ny] != '.')
    {
        boxes++;
        nx += dx;
        ny += dy;
    }

    nx = x;
    ny = y;
    a[x][y] = '@';
    for (int i = 0; i < boxes; i++)
    {
        nx += dx;
        ny += dy;
        a[nx][ny] = 'O';
    }
}

void robot(vector<vector<char>>& a, const vector<char>& moves) 
{
    int x, y; 

    for (int i = 0; i < a.size(); i++) 
    {
        for (int j = 0; j < a[0].size(); j++) 
        {
            if (a[i][j] == '@') {
                x = i;
                y = j;
                break;
            }
        }
    }

    for (char move : moves) {
        auto [dx, dy] = getDir(move);
        int nx = x + dx; 
        int ny = y + dy;

        if (isValid(nx, ny, a)) 
        {
            if (a[nx][ny] == '.') 
            { 
                a[nx][ny] = '@'; 
                a[x][y] = '.';  

                x = nx;
                y = ny;
            } 
            else if (a[nx][ny] == 'O') 
            { 
                if(isThereSpaceToPushBoxes(x, y, a, move))
                {
                    pushBoxes(x, y, a, move);
                }
            }
        }
    }
}

int distance(int x, int y)
{
    return(100 * x + y);
}

ULL gps(vector<vector<char>>& a)
{
    ULL sum = 0;
    vector<pair<int, int>> boxes;
    
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == 'O')
            {
                boxes.push_back(make_pair(i,j));
            }
        }
    }

    for (const auto& box : boxes)
    {
        sum += distance(box.first, box.second);
    }
    return sum;
}

int main(int argc, char *argv[]) 
{
    ifstream inputFile(argv[1]);
    vector<vector<char>> a;
    vector<char> moves;

    if (!inputFile) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) 
    {
        if (line.empty())
        {
            break;
        }
        vector<char> row(line.begin(), line.end());
        a.push_back(row);
    }

    while (getline(inputFile, line)) 
    {
        for (char c : line)
        {
            moves.push_back(c);
        }
    }
    inputFile.close();

    robot(a, moves);

    printf("sum: %llu\n", gps(a)); 
}

