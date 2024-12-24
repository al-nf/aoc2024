#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void bronKerbosch(set<string>& R, set<string>& P, set<string>& X, map<string, set<string>>& adjList, set<string>& maxClique)
{
    if (P.empty() && X.empty())
    {
        if (R.size() > maxClique.size())
        {
            maxClique = R;
        }
        return;
    }
    set<string> P_copy = P;
    for (const auto& node : P_copy) {
        set<string> neighbors = adjList[node];
        set<string> newR = R;
        newR.insert(node);

        set<string> newP, newX;
        for (const auto& n : neighbors) {
            if (P.find(n) != P.end()) newP.insert(n);
            if (X.find(n) != X.end()) newX.insert(n);
        }

        bronKerbosch(newR, newP, newX, adjList, maxClique);

        P.erase(node);
        X.insert(node);
    }
}
void solve(const vector<pair<string, string>>& connections)
{
    int sum = 0;
    map<string, set<string>> adjList;
    set<vector<string>> uniqueTriangles;

    for (const auto& edge : connections)
    {
        adjList[edge.first].insert(edge.second);
        adjList[edge.second].insert(edge.first);
    }

    set<string> R, P, X, maxClique;
    for (const auto& node : adjList)
    {
        P. insert(node.first);
    }

    bronKerbosch(R, P, X, adjList, maxClique);

    vector<string> res (maxClique.begin(), maxClique.end());
    sort(res.begin(), res.end());

    for (size_t i = 0; i < res.size(); i++)
    {
        if (i > 0) cout << ",";
        cout << res[i];
    }
    cout << '\n';
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

