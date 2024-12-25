#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>
#include <cmath>
#include <random>

using namespace std;

pair<int, int> translateGridPosition(char c)
{
    int x, y;
    switch (c)
    {
        case '0': x = 3; y = 1; break;
        case '1': x = 2; y = 0; break;
        case '2': x = 2; y = 1; break;
        case '3': x = 2; y = 2; break;
        case '4': x = 1; y = 0; break;
        case '5': x = 1; y = 1; break;
        case '6': x = 1; y = 2; break;
        case '7': x = 0; y = 0; break;
        case '8': x = 0; y = 1; break;
        case '9': x = 0; y = 2; break;
        case 'A': x = 3; y = 2; break;
        default: printf("invalid input\n"); return make_pair(-1, -1);
    }
    return make_pair(x, y);
}

pair<int, int> translateKeypadPosition(char c)
{
    int x, y;
    switch (c)
    {
        case '^': x = 0; y = 1; break;
        case 'A': x = 0; y = 2; break;
        case '<': x = 1; y = 0; break;
        case 'v': x = 1; y = 1; break;
        case '>': x = 1; y = 2; break;
        default: printf("invalid input\n"); return make_pair(-1, -1);
    }
    return make_pair(x, y);
}

string findPath(const vector<vector<char>>& grid, int x1, int y1, int x2, int y2)
{
    vector<pair<pair<int, int>, char>> directions = {
        {{0, -1}, '<'},
        {{-1, 0}, '^'},
        {{1, 0}, 'v'},
        {{0, 1}, '>'}
    };

    struct Path
    {
        string moves;
        vector<vector<bool>> visited;
        int turns;
        int x, y;
        int lastDir;

        Path(int rows, int cols, int startX, int startY)
            : visited(rows, vector<bool>(cols, false)),
              turns(0), x(startX), y(startY), lastDir(-1)
        {
            visited[startX][startY] = true;
        }
    };

    int rows = grid.size();
    int cols = grid[0].size();

    queue<Path> q;
    q.push(Path(rows, cols, x1, y1));

    string bestPath = "";
    int minTurns = INT_MAX;
    int maxAllowedLength = (rows + cols) * 2;

    while (!q.empty())
    {
        Path current = q.front();
        q.pop();

        if (current.x == x2 && current.y == y2)
        {
            if (current.turns < minTurns ||
                (current.turns == minTurns && current.moves.length() < bestPath.length()))
            {
                minTurns = current.turns;
                bestPath = current.moves;
            }
            continue;
        }

        if (current.moves.length() >= maxAllowedLength) continue;

        vector<pair<pair<int, int>, char>> shuffledDirections = directions;
        random_device rd;
        mt19937 g(rd());
        shuffle(shuffledDirections.begin(), shuffledDirections.end(), g);

        for (int i = 0; i < shuffledDirections.size(); i++)
        {
            int nx = current.x + shuffledDirections[i].first.first;
            int ny = current.y + shuffledDirections[i].first.second;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                !current.visited[nx][ny] && grid[nx][ny] != '#')
            {
                Path newPath = current;
                newPath.x = nx;
                newPath.y = ny;
                newPath.visited[nx][ny] = true;
                newPath.moves += shuffledDirections[i].second;

                if (current.lastDir != -1 && current.lastDir != i)
                {
                    newPath.turns++;
                }
                newPath.lastDir = i;

                if (newPath.turns < minTurns)
                {
                    q.push(newPath);
                }
            }
        }
    }

    return bestPath;
}

int solve(const vector<vector<char>>& grid, const vector<vector<char>>& keypad, const vector<vector<char>>& passwords)
{
    int x0, y0, x1, y1, x2, y2;
    int tx0, ty0, tx1, ty1, tx2, ty2;
    int sum = 0;
    string result = "";

    x0 = 3; y0 = 2;
    x1 = 0; y1 = 2;
    x2 = 0; y2 = 2;

    for (vector<char> row : passwords)
    {
        string res0 = "";
        string res1 = "";
        string res2 = "";
        string moves = "";
        string moves1 = "";
        string moves2 = "";
        string result = "";

        for (char c : row)
        {
            pair<int, int> tmp = translateGridPosition(c);
            tx0 = tmp.first; ty0 = tmp.second;
            string moves = findPath(grid, x0, y0, tx0, ty0);
            x0 = tx0; y0 = ty0;
            moves += 'A';
            res0 += moves;

            for (char ch : moves)
            {
                moves1 = "";
                tmp = translateKeypadPosition(ch);
                tx1 = tmp.first; ty1 = tmp.second;
                moves1 += findPath(keypad, x1, y1, tx1, ty1);
                moves1 += 'A';
                x1 = tx1; y1 = ty1;
                res1 += moves1;

                for (char cha : moves1)
                {
                    moves2 = "";
                    tmp = translateKeypadPosition(cha);
                    tx2 = tmp.first; ty2 = tmp.second;
                    moves2 += findPath(keypad, x2, y2, tx2, ty2);
                    moves2 += 'A';
                    x2 = tx2; y2 = ty2;
                    res2 += moves2;

                    result += moves2;
                }
            }
        }

        string temporary = "";
        for (char c : row)
        {
            if (isdigit(c))
            {
                temporary += c;
            }
        }
        int a = stoi(temporary);
        sum += (result.length() * a);
    }

    return sum;
}

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);
    vector<vector<char>> grid = {
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'},
        {'#', '0', 'A'}
    };

    vector<vector<char>> keypad = {
        {'#', '^', 'A'},
        {'<', 'v', '>'}
    };
    vector<vector<char>> passwords;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        vector<char> row(line.begin(), line.end());
        passwords.push_back(row);
    }

    inputFile.close();

    int smallestSum = INT_MAX;

    for (int i = 0; i < 1000000; ++i)
    {
        int currentSum = solve(grid, keypad, passwords);
        if (currentSum < smallestSum)
        {
            smallestSum = currentSum;
        }
        cout << "run " << i << '\n';
    }

    cout << "sum: " << smallestSum << '\n';
}
