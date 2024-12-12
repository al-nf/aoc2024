#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
#include <stack>

using namespace std;


pair<int, int> dfs(int x, int y, char plant_type, const vector<vector<char>>& data, vector<vector<bool>> &visited) 
{
    const vector<pair<int, int>> dirs =
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };
    stack<pair<int, int>> s;
    s.push({x, y});
    visited[x][y] = true;
    
    int area = 0;
    int perimeter = 0;

    while (!s.empty()) 
    {
        auto [cx, cy] = s.top();
        s.pop();
        area++;

        for (const auto& dir : dirs) 
        {
            int nx = cx + dir.first;
            int ny = cy + dir.second;
            
            if (nx >= 0 && nx < data.size() && ny >= 0 && ny < data[0].size()) 
            {
                if (data[nx][ny] == plant_type && !visited[nx][ny]) 
                {
                    visited[nx][ny] = true;
                    s.push({nx, ny});
                } 
                else if (data[nx][ny] != plant_type) 
                {
                    perimeter++;
                }
            } 
            else 
            {
                perimeter++;
            }
        }
    }
    return {area, perimeter};
}

int price(vector<vector<char>> data) 
{
    const int rows = data.size();
    const int cols = data[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int sum = 0;


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!visited[i][j])
            {
                char plant_type = data[i][j];
                auto [area, perimiter] = dfs(i, j, plant_type, data, visited);
                int term = area * perimiter;
                sum += term;
            }
        }
    }
    return sum;
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

    printf("sum: %d\n", price(data));
}
