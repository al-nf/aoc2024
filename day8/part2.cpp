#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<char, vector<pair<int, int>>> get_pts(const vector<vector<char>>& data) 
{
    unordered_map<char, vector<pair<int, int>>> freq_pts;
    for (int i = 0; i < data.size(); i++) 
    {
        for (int j = 0; j < data[i].size(); j++) 
        {
            if (data[i][j] != '.') {
                freq_pts[data[i][j]].push_back({i, j});
            }
        }
    }
    return freq_pts;
}

void findAntinodes(vector<vector<char>>& data) 
{
    unordered_map<char, vector<pair<int, int>>> freq_pts = get_pts(data);
    int sum = 0;

    for (const auto& entry : freq_pts) 
    {
        const vector<pair<int, int>>& points = entry.second;

        for (int i = 0; i < points.size(); i++) 
        {
            pair<int, int> p1 = points[i];
            data[p1.first][p1.second] = '#';
            for (int j = i + 1; j < points.size(); ++j) 
            {
                pair<int, int> p2 = points[j];
                int dx = p1.first - p2.first;
                int dy = p1.second - p2.second;
                pair<int, int> n1 = {p1.first + dx, p1.second + dy};
                pair<int, int> n2 = {p2.first - dx, p2.second - dy};

                while (n1.first >= 0 && n1.first < data.size() && n1.second >= 0 && n1.second < data[0].size()) 
                {
                    data[n1.first][n1.second] = '#';
                    n1.first += dx;
                    n1.second += dy;

                } 

                while (n2.first >= 0 && n2.first < data.size() && n2.second >= 0 && n2.second < data[0].size()) 
                {
                    data[n2.first][n2.second] = '#';
                    n2.first -= dx;
                    n2.second -= dy;
                }
            }
        }
    }
    
    vector<vector<char>>::iterator row;
    vector<char>::iterator col;
    for (row = data.begin(); row != data.end(); row++)
    {
        for (col = row->begin(); col != row->end(); col++)
        {
            if (*col == '#')
                sum++;
        }
    }
    cout << "sum: " << sum << endl;
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<vector<char>> data;

    if (!input_file) {
        cerr << "error opening file" << endl;
        return 1; 
    }

    string line;
    while (getline(input_file, line)) 
    {
        vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }

    findAntinodes(data);
}

