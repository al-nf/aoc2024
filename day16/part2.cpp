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
    return {0, 0};
}

struct State
{
    int g, x, y, direction;

    bool operator>(const State& other) const
    {
        return g > other.g;
    }
};


void dijkstra(const vector<vector<char>>& map, int startX, int startY, int endX, int endY, vector<vector<vector<int>>>& dist)
{
    int rows = map.size();
    int cols = map[0].size();

    priority_queue<State, vector<State>, greater<State>> openList;
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
            return;
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
}

void bfsFromEnd(vector<vector<char>>& map, int startX, int startY, int endX, int endY, const vector<vector<vector<int>>>& dist)
{
    int rows = map.size();
    int cols = map[0].size();

    queue<tuple<int, int, int>> q;
    vector<vector<bool>> path(rows, vector<bool>(cols, false));

    for (int direction = 0; direction < 4; direction++)
    {
        if (dist[endX][endY][direction] != INT_MAX)
        {
            q.push({endX, endY, direction});
        }
    }

    while (!q.empty())
    {
        auto [x, y, direction] = q.front();
        q.pop();

        path[x][y] = true;

        pair<int, int> moveDir = dir(direction);
        int nx = x - moveDir.first, ny = y - moveDir.second;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && map[nx][ny] != '#')
        {
            if (dist[nx][ny][direction] == dist[x][y][direction] - 1)
            {
                q.push({nx, ny, direction});
            }
        }

        for (int turn = -1; turn <= 1; turn += 2)
        {
            int newDirection = (direction + turn + 4) % 4;
            if (dist[x][y][newDirection] == dist[x][y][direction] - 1000)
            {
                q.push({x, y, newDirection});
            }
        }
    }

    int pathCount = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (path[i][j])
                pathCount++;
        }
    }
    printf("sum: %d\n", pathCount);
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

    vector<vector<vector<int>>> dist(map.size(), vector<vector<int>>(map[0].size(), vector<int>(4, INT_MAX)));

    dijkstra(map, startX, startY, endX, endY, dist);
    bfsFromEnd(map, startX, startY, endX, endY, dist);
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

