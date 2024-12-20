#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> Point;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

bool isValid(int x, int y, const vector<vector<char>>& grid, const vector<vector<bool>>& visited)
{
    return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] != '#' && !visited[x][y]);
}

void solve(const vector<vector<char>>& grid)
{
    int startX = -1, startY = -1, endX = -1, endY = -1;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == 'S')
            {
                startX = i;
                startY = j;
            }
            if (grid[i][j] == 'E')
            {
                endX = i;
                endY = j;
            }
        }
    }

    if (startX == -1 || startY == -1 || endX == -1 || endY == -1)
    {
        cerr << "Start or End not found in the grid." << endl;
        return;
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    vector<vector<int>> distance(grid.size(), vector<int>(grid[0].size(), 0));
    queue<Point> q;

    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty())
    {
        Point p = q.front();
        q.pop();
        int x = p.first, y = p.second;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];

            if (isValid(nx, ny, grid, visited))
            {
                visited[nx][ny] = true;
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    int sum = 0;
    vector<Point> reachablePoints;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (visited[i][j] && grid[i][j] != 'S' && grid[i][j] != 'E')
            {
                reachablePoints.push_back({i, j});
            }
        }
    }

    for (size_t i = 0; i < reachablePoints.size(); i++)
    {
        for (size_t j = i + 1; j < reachablePoints.size(); j++)
        {
            Point p1 = reachablePoints[i];
            Point p2 = reachablePoints[j];
            int dist = abs(p1.first - p2.first) + abs(p1.second - p2.second);

            if (dist <= 20 && distance[p2.first][p2.second] - distance[p1.first][p1.second] > dist)
            {
                int saved = distance[p2.first][p2.second] - distance[p1.first][p1.second] - dist;
                if (saved >= 50)
                {
                    sum++;
                }
            }
        }
    }

    printf("sum: %d\n", sum);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Please provide the input file as a command-line argument." << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    vector<vector<char>> grid;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    inputFile.close();

    solve(grid);
    return 0;
}

