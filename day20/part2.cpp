#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <queue>
#include <map>
#include <set>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

typedef pair<int, int> Point;

bool isValid(int x, int y, int rows, int cols, const vector<vector<char>>& grid)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] != '#');
}

int dijkstra(Point start, Point end, const vector<vector<char>>& grid)
{
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[start.first][start.second] = 0;

    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [curDist, curPoint] = pq.top();
        pq.pop();
        int x = curPoint.first;
        int y = curPoint.second;

        if (x == end.first && y == end.second)
        {
            return curDist;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, n, m, grid))
            {
                int newDist = curDist + 1;

                if (newDist < dist[nx][ny])
                {
                    dist[nx][ny] = newDist;
                    pq.push({newDist, {nx, ny}});
                }
            }
        }
    }

    return INT_MAX;
}

void solve(vector<vector<char>>& grid)
{
    int sum = 0;
    int startX, startY, endX, endY;

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

    set<Point> uniqueCheats;

    int timeBefore = dijkstra({startX, startY}, {endX, endY}, grid);

    for (int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid[0].size(); y++)
        {
            if (grid[x][y] == '#')
            {
                Point wall = {x, y};
                if (uniqueCheats.find(wall) == uniqueCheats.end())
                {
                    uniqueCheats.insert(wall);

                    grid[x][y] = '.';
                    int timeAfter = dijkstra({startX, startY}, {endX, endY}, grid);

                    int timeSaved = timeBefore - timeAfter;

                    if (timeSaved >= 100)
                    {
                        sum++;
                    }

                    grid[x][y] = '#';
                }
            }
        }
    }

    printf("sum: %d\n", sum);
}

int main(int argc, char* argv[])
{
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
}

