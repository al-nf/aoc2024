#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int findTrailScores(vector<vector<int>> map) 
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
        visited[x][y] = true;
        int score = (map[x][y] == 9) ? 1 : 0;

        for (auto [dx, dy] : dirs) 
        {
            int nx = x + dx, ny = y + dy;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) 
            {
                if (!visited[nx][ny] && map[nx][ny] != -1 && map[nx][ny] == map[x][y] + 1) 
                {
                    score += self(nx, ny, self); 
                }
            }
        }
        return score; 
    };

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (map[i][j] == 0 && !visited[i][j]) 
            {
                vector<vector<bool>> tempVisited = visited;
                sum += dfs(i, j, dfs); 
                visited = tempVisited;
            }
        }
    }
    return sum;
}


int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<vector<int>> data;

    if (!input_file) 
    {
        cerr << "Error opening file" << endl;
        return 1; 
    }

    string line;
    while (getline(input_file, line)) 
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

    printf("sum: %d\n", findTrailScores(data));
}

