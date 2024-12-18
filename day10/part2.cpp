#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int findTrailPaths(vector<vector<int>> map) 
{
    int sum = 0;
    int rows = map.size();
    int cols = map[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    const vector<pair<int, int>> dirs = 
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    auto dfs = [&](int x, int y, auto&& self) -> int 
    {
        if (map[x][y] == 9)
        {
            return 1;
        }

        visited[x][y] = true;
        int rating = 0;

        for (auto [dx, dy] : dirs) 
        {
            int nx = x + dx, ny = y + dy;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) 
            {
                if (!visited[nx][ny] && map[nx][ny] != -1 && map[nx][ny] == map[x][y] + 1)
                {
                    rating += self(nx, ny, self); 
                }
            }
        }
        visited[x][y] = false;
        return rating; 
    };

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (map[i][j] == 0 && !visited[i][j]) 
            {
                sum += dfs(i, j, dfs); 
            }
        }
    }
    return sum;
}


int main(int argc, char *argv[]) 
{
    ifstream inputFile(argv[1]);
    vector<vector<int>> data;

    if (!inputFile) 
    {
        cerr << "error opening file" << endl;
        return 1; 
    }

    string line;
    while (getline(inputFile, line)) 
    {
        vector<int> row;
        for (char c : line) 
        {
            if (c != '.')
                row.push_back(c - '0');
            else
                row.push_back(-1);
        }
        data.push_back(row);
    }

    printf("sum: %d\n", findTrailPaths(data));
}

