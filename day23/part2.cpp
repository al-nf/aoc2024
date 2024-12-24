#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void solve(const vector<pair<string, string>>& connections)
{
    int sum = 0;
    map<string, set<string>> adjList;

    for (const auto& edge : connections)
    {
        adjList[edge.first].insert(edge.second);
        adjList[edge.second].insert(edge.first);
    }

    for (const auto& nodeA : adjList)
    {
        const string& a = nodeA.first;
        const set<string>& neighborsA = nodeA.second;

        for (const string& b : neighborsA)
        {
            if (adjList.find(b) == adjList.end()) continue;

            for (const string& c : adjList[b])
            {
                if (c != a && neighborsA.find(c) != neighborsA.end())
                {
                    vector<string> triangle = {a, b, c};
                    sort(triangle.begin(), triangle.end()); 

                    if (triangle[0] == a) 
                    {
                        if (a[0] == 't' || b[0] == 't' || c[0] == 't')
                        {
                            sum++;
                        }
                    }
                }
            }
        }
    }

    printf("sum: %d\n", sum/2);
}

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);

    vector<pair<string, string>> connections;
    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        string a = line.substr(0, 2);
        string b = line.substr(3, 2);
        connections.push_back(make_pair(a, b));
    }

    inputFile.close();

    solve(connections);
}

