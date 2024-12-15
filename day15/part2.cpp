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

void convertMap(vector<vector<char>>& warehouse)
{
    vector<vector<char>> newMap;

    for (int i = 0; i < warehouse.size(); i++)
    {
        vector<char> row;
        for (int j = 0; j < warehouse[0].size(); j++)
        {
            switch (warehouse[i][j])
            {
                case '#':
                {
                    row.push_back('#');
                    row.push_back('#');
                    break;
                }
                case 'O':
                {
                    row.push_back('[');
                    row.push_back(']');
                    break;
                }
                case '.':
                {
                    row.push_back('.');
                    row.push_back('.');
                    break;
                }
                case '@':
                {
                    row.push_back('@.');
                    row.push_back('.');
                    break;
                }
            }
        }
        newMap.push_back(row);
    }
    warehouse.assign(newMap.begin(), newMap.end());
}

bool isValid(int x, int y, const vector<vector<char>>& warehouse)
{
    if (x >= 0 && x < warehouse.size() && y >= 0 && y < warehouse[0].size())
    {
        if (warehouse[x][y] != '#')
        {
            return true;
        }
    }
    return false;

}

bool isThereSpaceToPushBoxes(int& x, int& y, const vector<vector<char>>& warehouse, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x+dx;
    int ny = y+dy;

    if (dy == 0)
    {
        while (isValid(nx, ny, warehouse))
        {
            if (warehouse[nx][ny] == '.')
                return true;
            nx += dx;
            ny += dy;
        }
        return false;
    }
    else
    {
        char ya = warehouse[nx][ny];
        if (ya == '[')
        {
            nx += dx;
            ny += dy;
            if (isValid(nx, ny, warehouse) && isValid(nx + 1, ny, warehouse))
            {
                if (warehouse[nx + dx][ny + dy] == ya)
                {
                    while (isValid(nx,   
                }
            }
        }
        else
        {
            if (isValid(nx + dx, ny + dy, warehouse) && isValid(nx + dx - 1, ny + dy, warehouse))
            {
                if (warehouse[nx + dx][ny + dy] == ya)
                {
                }
            }
        }
    }
}

void pushBoxes(int& x, int& y, vector<vector<char>>& warehouse, char dir) 
{
    auto [dx, dy] = getDir(dir);

    if (!isThereSpaceToPushBoxes(x, y, warehouse, dir)) 
    {
        return; 
    }

    int nx = x + dx;
    int ny = y + dy;
    
    warehouse[x][y] = '.';
    x = nx;
    y = ny;

    int boxes = 0;

    while (warehouse[nx][ny] != '.')
    {
        boxes++;
        nx += dx;
        ny += dy;
    }

    nx = x;
    ny = y;
    warehouse[x][y] = '@';
    for (int i = 0; i < boxes; i++)
    {
        nx += dx;
        ny += dy;
        warehouse[nx][ny] = 'O';
    }
}

void robot(vector<vector<char>>& warehouse, const vector<char>& moves) 
{
    int x, y; 

    for (int i = 0; i < warehouse.size(); i++) 
    {
        for (int j = 0; j < warehouse[0].size(); j++) 
        {
            if (warehouse[i][j] == '@') {
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

        if (isValid(nx, ny, warehouse)) 
        {
            if (warehouse[nx][ny] == '.') 
            { 
                warehouse[nx][ny] = '@'; 
                warehouse[x][y] = '.';  

                x = nx;
                y = ny;
            } 
            else if (warehouse[nx][ny] == '[' || warehouse[nx][ny] == ']') 
            { 
                if(isThereSpaceToPushBoxes(x, y, warehouse, move))
                {
                    pushBoxes(x, y, warehouse, move);
                }
            }
        }
    }
}

int distance(int x, int y)
{
    return(100 * x + y);
}

ULL gps(vector<vector<char>>& warehouse)
{
    ULL sum = 0;
    vector<pair<int, int>> boxes;
    
    for (int i = 0; i < warehouse.size(); i++)
    {
        for (int j = 0; j < warehouse[0].size(); j++)
        {
            if (warehouse[i][j] == 'O')
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
    ifstream input_file(argv[1]);
    vector<vector<char>> warehouse;
    vector<char> moves;

    if (!input_file) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;

    while (getline(input_file, line)) 
    {
        if (line.empty())
        {
            break;
        }
        vector<char> row(line.begin(), line.end());
        warehouse.push_back(row);
    }

    while (getline(input_file, line)) 
    {
        for (char c : line)
        {
            moves.push_back(c);
        }
    }
    input_file.close();

    convertMap(warehouse);
    robot(warehouse, moves);

    printf("sum: %llu\n", gps(warehouse)); 
}

