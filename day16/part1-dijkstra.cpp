#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <climits>

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

struct State
{
    int g, x, y, direction;

    bool operator>(const State& other) const
    {
        return g > other.g;
    }
};

int dijkstra(const vector<vector<char>>& map, int startX, int startY, int endX, int endY)
{
    int rows = map.size();
    int cols = map[0].size();

    priority_queue<State, vector<State>, greater<State>> openList;
    vector<vector<vector<int>>> dist(rows, vector<vector<int>>(cols, vector<int>(4, INT_MAX)));
    set<tuple<int, int, int>> visited;

    openList.push({0, startX, startY, 0});
    dist[startX][startY][0] = 0;

    while (!openList.empty())
    {
        State cur = openList.top();
        openList.pop();

        int x = cur.x, y = cur.y, direction = cur.direction;
        int g = cur.g;

        if (x == endX && y == endY)
        {
            return g;
        }

        pair<int, int> moveDir = dir(direction);
        int nx = x + moveDir.first, ny = y + moveDir.second;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && map[nx][ny] != '#')
        {
            if (g + 1 < dist[nx][ny][direction])
            {
                dist[nx][ny][direction] = g + 1;
                openList.push({g + 1, nx, ny, direction});
            }
        }

        int newDirection = (direction + 1) % 4;
        if (g + 1000 < dist[x][y][newDirection])
        {
            dist[x][y][newDirection] = g + 1000;
            openList.push({g + 1000, x, y, newDirection});
        }

        newDirection = (direction - 1 + 4) % 4;
        if (g + 1000 < dist[x][y][newDirection])
        {
            dist[x][y][newDirection] = g + 1000;
            openList.push({g + 1000, x, y, newDirection});
        }
    }

    return -1;
}

void reindeer(vector<vector<char>>& map)
{
    int startX, startY, endX, endY;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] == 'S')
            {
                startX = i;
                startY = j;
            }
            if (map[i][j] == 'E')
            {
                endX = i;
                endY = j;
            }
        }
    }

    int score = dijkstra(map, startX, startY, endX, endY);
    if (score != -1)
    {
        printf("Shortest path cost: %d\n", score);
    }
    else
    {
        printf("No path found.\n");
    }
}

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);
    vector<vector<char>> map;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }
    inputFile.close();

    reindeer(map);
}
