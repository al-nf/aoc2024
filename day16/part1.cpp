#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <queue>
#include <climits>

#define ULL unsigned long long

using namespace std;

pair<int, int> dir(int direction)
{
    switch (direction % 4)
    {
        case 0: return {0, 1};
        case 1: return {1, 0};
        case 2: return {0, -1};
        case 3: return {-1, 0};
    }
}

ULL distance(const int& x, const int& y, const int& a, const int& b)
{
    return abs(x - a) + abs(y - b);
}

struct State
{
    int f, g, x, y, direction;
    bool operator>(const State &other) const
    {
        return f > other.f;
    }
};

ULL astar(const vector<vector<char>>& map, const int& x, const int& y, const int& dr, const int& a, const int& b)
{
    int n = map.size();

    vector<vector<vector<ULL>>> dist(n, vector<vector<ULL>>(n, vector<ULL>(4, ULLONG_MAX)));

    auto valid = [&map](const int& x, const int& y)
    {
        return (x >= 0 && x < map.size() && y >= 0 && y < map.size() && map[x][y] != '#');
    };

    priority_queue<State, vector<State>, greater<State>> openList;

    dist[x][y][dr] = 0;
    openList.push({0, 0, x, y, dr});

    while (!openList.empty())
    {
        State cur = openList.top();
        openList.pop();

        int x = cur.x, y = cur.y, dr = cur.direction;
        int g = cur.g, f = cur.f;

        if (x == a && y == b)
        {
            return g;
        }

        pair<int, int> pairDir = dir(dr);
        int dx = pairDir.first, dy = pairDir.second;
        int nx = x + dx, ny = y + dy;

        if (valid(nx, ny) && dist[nx][ny][dr] > g + 1)
        {
            dist[nx][ny][dr] = g + 1;
            openList.push({g + 1, g + 1, nx, ny, dr});
        }

        int newDr = (dr + 1) % 4;
        if (dist[x][y][newDr] > g + 1000)
        {
            dist[x][y][newDr] = g + 1000;
            openList.push({g + 1000, g + 1000, x, y, newDr});
        }

        newDr = (dr - 1 + 4) % 4;
        if (dist[x][y][newDr] > g + 1000)
        {
            dist[x][y][newDr] = g + 1000;
            openList.push({g + 1000, g + 1000, x, y, newDr});
        }
    }
    return -1;
}

void reindeer(vector<vector<char>>& map)
{
    int x, y, a, b;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] == 'S')
            {
                x = i; 
                y = j;
            }
            if (map[i][j] == 'E')
            {
                a = i; 
                b = j;
            }
        }
    }

    int dr = 0;
    int score = astar(map, x, y, dr, a, b);
    printf("score: %llu\n", score);
}

int main(int argc, char *argv[])
{
    ifstream input_file(argv[1]);
    vector<vector<char>> data;

    if (!input_file)
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;

    while (getline(input_file, line))
    {
        vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }
    input_file.close();

    reindeer(data);
}
