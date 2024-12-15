#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#define ROWS 103
#define COLS 101

#define ULL unsigned long long

using namespace std;

pair<int, int> pos(pair<pair<int, int>, pair<int, int>> &robot, int t)
{
    int px = robot.first.first;
    int py = robot.first.second;
    int vx = robot.second.first;
    int vy = robot.second.second;

    int nx = ((px + vx * t) % ROWS + ROWS) % ROWS;
    int ny = ((py + vy * t) % COLS + COLS) % COLS;

    printf("Robot after time %d: %d, %d\n", t, nx, ny);

    return make_pair(nx, ny);
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

    cout << data[0] << ' ' << data[1] << ' ' << data[2] << ' ' << data[3] << endl;
    ULL result =  data[0] * data[1] * data[2] * data[3];
    return result;
}
int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<pair<pair<int,int>, pair<int,int>>> robots;
    ULL sum = 0;

    if (!input_file) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    regex regex(R"(p=(-?\d+),(-?\d+)\s*v=(-?\d+),(-?\d+))");

    while (getline(input_file, line)) 
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
    input_file.close();



    printf("sum: %llu\n", safety(robots, 100));
}

