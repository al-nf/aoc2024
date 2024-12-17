#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <thread>
#include <chrono>

#define ROWS 101
#define COLS 103

#define ULL unsigned long long

using namespace std;

pair<int, int> pos(pair<pair<int, int>, pair<int, int>> &robot, int t)
{
    int px = robot.first.first;
    int py = robot.first.second;
    int vx = robot.second.first;
    int vy = robot.second.second;

    //int testx = (((px + vx * 2) % ROWS) + ROWS) % ROWS;
    //int testy = (((py + vy * 2) % COLS) + COLS) % COLS;

    int nx = (((px + vx * t) % ROWS) + ROWS) % ROWS;
    int ny = (((py + vy * t) % COLS) + COLS) % COLS;

    //printf("Before: %d, %d\n After: %d, %d\n Velocities: %d, %d\n After 2 seconds: %d, %d\n\n", px, py, nx, ny, vx, vy, testx,testy);

    return make_pair(nx, ny);
}

void printBoard(vector<pair<pair<int,int>, pair<int,int>>> &robots, int t)
{
    vector<vector<int>> board(ROWS, vector<int>(COLS, 0));
    for (int i = 0; i < robots.size(); i++)
    {
        pair<int, int> position = pos(robots[i], t);
        if (board[position.first][position.second] == 1)
        {
            return;
        }
        board[position.first][position.second] = 1;
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

ULL safety(vector<pair<pair<int,int>, pair<int,int>>> &robots, int t)
{
    int rowMid = ROWS / 2;
    int colMid = COLS / 2;
    int data[] = {0, 0, 0, 0};

    vector<pair<int, int>> newPos;

    for (int i = 0; i < robots.size(); i++)
    {
        newPos.push_back(pos(robots[i], t));
    }

    // First quadrant: nx > rowMid, ny > colMid
    // Second quadrant: nx < rowMid, ny > colMid
    // Third quadrant: nx < rowMid, ny < colMid
    // Fourth quadrant: nx > rowMid, ny < colMid
    pair<int, int> pos;
    for (int i = 0; i < newPos.size(); i++)
    {
        pos = newPos[i];

        if (pos.first > rowMid && pos.second > colMid)
        {
            data[0]++;
        }
        else if (pos.first < rowMid && pos.second > colMid)
        {
            data[1]++;
        }
        else if (pos.first < rowMid && pos.second < colMid)
        {
            data[2]++;
        }
        else if (pos.first > rowMid && pos.second < colMid)
        {
            data[3]++;
        }
    }

    //cout << data[0] << ' ' << data[1] << ' ' << data[2] << ' ' << data[3] << endl;
    ULL result = 1;
    for (int i = 0; i < 4; i++)
    {
        result *= data[i];
    }
    return result;
}
int main(int argc, char *argv[]) 
{
    ifstream inputFile(argv[1]);
    vector<pair<pair<int,int>, pair<int,int>>> robots;
    ULL sum = 0;

    if (!inputFile) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    regex regex(R"(p=(-?\d+),(-?\d+)\s*v=(-?\d+),(-?\d+))");

    while (getline(inputFile, line)) 
    {
        smatch matches;
        if (regex_search(line, matches, regex))
        {
            int px = stoi(matches[1].str());
            int py = stoi(matches[2].str());
            int vx = stoi(matches[3].str());
            int vy = stoi(matches[4].str());
        
            robots.push_back
            (
                make_pair
                (
                    make_pair(px, py),
                    make_pair(vx, vy)
                )
            );
        }
    }
    inputFile.close();

    printf("sum: %llu\n", safety(robots, 100));
    int i = 0;
    while (true)
    {
        printBoard(robots, i);
        printf("\n, TIME: %d", i);
        i++;
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

