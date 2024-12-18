#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>
#include <queue>

#define ROWS 71

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

typedef pair<int, pair<int,int>> Node;

bool isValid(int x, int y, int rows, int cols, vector<vector<char>>& grid)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '.');
}

bool dijkstra(int startX, int startY, int endX, int endY, vector<vector<char>>& grid) 
{
    vector<vector<int>> d(ROWS, vector<int>(ROWS, INT_MAX));
    d[startX][startY] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, {startX, startY}});

    while (!pq.empty()) 
    {
        int cd = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (x == endX && y == endY) 
        {
            return true;
        }

        
        for (int i = 0; i < 4; i++) 
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, ROWS, ROWS, grid)) 
            {
                int nd = cd + 1; 
                if (nd < d[nx][ny]) 
                {
                    d[nx][ny] = nd;
                    pq.push({nd, {nx, ny}});
                }
            }
        }
    }
    return false;
}

void solve(vector<vector<char>>& grid, const vector<vector<int>>& memory)
{
    int startX = 0; 
    int startY = 0;
    int endX = ROWS-1; 
    int endY = ROWS-1;
    for (int i = 0; i < memory.size(); i++)
    {
        grid[memory[i][0]][memory[i][1]] = '#';
        if (!dijkstra(startX, startY, endX, endY, grid))
        {
            printf("coordinates: %d, %d\n", memory[i][0], memory[i][1]);
            return;
        }
    }

}

int main(int argc, char *argv[])
{
    ifstream inputFile(argv[1]);
    vector<vector<char>> grid(ROWS, vector<char> (ROWS, '.'));
    vector<vector<int>> memory;

    if (!inputFile)
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        string pair;
        vector<int> numbers;
        
        while (getline(ss, pair, ',')) 
        {
            numbers.push_back(stoi(pair)); 
        }
        
        memory.push_back(numbers);
    }
    inputFile.close();

    solve(grid, memory);
}

