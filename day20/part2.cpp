#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> Point;

vector<Point> parseTrack(const vector<vector<char>>& grid, Point& start)
{
    vector<Point> track;
    int x, y;

    for (y = 0; y < grid.size(); y++)
    {
        for (x = 0; x < grid[y].size(); x++)
        {
            if (grid[y][x] == 'S')
            {
                start = {x, y};
                track.push_back(start);
                break;
            }
        }
        if (!track.empty()) break;
    }

    while (grid[y][x] != 'E')
    {
        Point nextPoint = {-1, -1};
        for (auto nb : vector<Point>{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}})
        {
            int nx = nb.first;
            int ny = nb.second;
            if (nx >= 0 && ny >= 0 && ny < grid.size() && nx < grid[ny].size() && grid[ny][nx] != '#' && !(track.size() > 1 && nb == track[track.size() - 2]))
            {
                nextPoint = nb;
                break;
            }
        }
        if (nextPoint.first == -1) break;
        track.push_back(nextPoint);
        x = nextPoint.first;
        y = nextPoint.second;
    }
    return track;
}

vector<int> calculateCheats(const vector<Point>& track, int max_dist)
{
    vector<int> saved;
    for (size_t t1 = 0; t1 < track.size(); t1++)
    {
        for (size_t t2 = t1 + 3; t2 < track.size(); t2++)
        {
            int x1 = track[t1].first, y1 = track[t1].second;
            int x2 = track[t2].first, y2 = track[t2].second;
            int dist = abs(x2 - x1) + abs(y2 - y1);

            if (dist <= max_dist && (t2 - t1) > dist)
            {
                saved.push_back(t2 - t1 - dist);
            }
        }
    }
    return saved;
}

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);
    vector<vector<char>> grid;
    string line;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    while (getline(inputFile, line))
    {
        vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }
    inputFile.close();

    Point start;
    vector<Point> track = parseTrack(grid, start);

    vector<int> cheats = calculateCheats(track, 20);

    int totalCheats = count_if(cheats.begin(), cheats.end(), [](int saved) { return saved >= 100; });
    cout << "sum: " << totalCheats << '\n';
}

