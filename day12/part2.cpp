#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

bool inBound(int x, int y, const vector<vector<char>>& data) 
{
    return x >= 0 && x < data.size() && y >= 0 && y < data[0].size();
}

int getVertices(const pair<int, int>& point, const vector<vector<char>>& data) 
{
    const int dirs[3][3] = 
    {
        {-1, 0}, 
        {0, 1}, 
        {1, 0}
    };
    int vertices = 0;
    bool matches[3][3] = {{false}}; 

    char value = data[point.first][point.second];

    for (int r_d = 0; r_d < 3; ++r_d) 
    {
        for (int c_d = 0; c_d < 3; ++c_d) 
        {
            pair<int, int> compare_point = {point.first + c_d - 1, point.second + r_d - 1};
            if (inBound(compare_point.first, compare_point.second, data) &&
                data[compare_point.first][compare_point.second] == value) 
            {
                matches[r_d][c_d] = true;
            }
        }
    }

    if (matches[0][1]) 
    {
        
        if (matches[1][0] && !matches[0][0]) 
        {
            vertices++;
        }
        if (matches[1][2] && !matches[0][2]) 
        {
            vertices++;
        }
    } 
    else 
    {
        if (!matches[1][0]) 
        {
            vertices++;
        }
        if (!matches[1][2]) 
        {
            vertices++;
        }
    }

    if (matches[2][1]) 
    {
        if (matches[1][2] && !matches[2][2]) 
        {
            vertices++;
        }
        if (matches[1][0] && !matches[2][0]) 
        {
            vertices++;
        }
    } 
    else 
    {
        if (!matches[1][0]) 
        {
            vertices++;
        }
        if (!matches[1][2]) 
        {
            vertices++;
        }
    }

    return vertices;
}

pair<int, int> dfs(int x, int y, char plant_type, const vector<vector<char>>& data, vector<vector<bool>>& visited) 
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
    int vertices = 0; 

    while (!s.empty()) 
    {
        auto [cx, cy] = s.top();
        s.pop();
        area++; 

        vertices += getVertices({cx, cy}, data); 

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
            }
        }
    }
    return {area, vertices}; 
}

int price(const vector<vector<char>>& data) 
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
                auto [area, vertices] = dfs(i, j, plant_type, data, visited);
                int term = area * vertices;
                //cout << area << " " << vertices << endl; 
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

