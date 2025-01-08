#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void solve(const vector<vector<vector<char>>>& schems)
{
    vector<vector<vector<char>>> lcks;
    vector<vector<vector<char>>> keys;

    for (vector<vector<char>> schem : schems)
    {
        if (schem[0][0] == '.')
        {
            keys.push_back(schem);
        }
        else if (schem[0][0] == '#')
        {
            lcks.push_back(schem);
        }
    }

    vector<vector<int>> lckHeights;
    vector<vector<int>> keyHeights;

    for (vector<vector<char>> lck : lcks)
    {
        vector<int> heights;
        for (int i = 0; i < 5; i++)
        {
            int height = -1;
            for (int j = 0; j < 7; j++)
            {
                if (lck[j][i] == '#')
                {
                    height++;
                }
            }
            heights.push_back(height);
        }
        lckHeights.push_back(heights);
    }
    for (vector<vector<char>> key : keys)
    {
        vector<int> heights;
        for (int i = 0; i < 5; i++)
        {
            int height = -1;
            for (int j = 0; j < 7; j++)
            {
                if (key[j][i] == '#')
                {
                    height++;
                }
            }
            heights.push_back(height);
        }
        keyHeights.push_back(heights);
    }

    int sum = lckHeights.size() * keyHeights.size();
    for (vector<int> lck : lckHeights)
    {
        for (vector<int> key : keyHeights)
        {
            bool bad = false;
            for (int i = 0; i < 5; i++)
            {
                if (key[i] + lck[i] >= 6)
                {
                    bad = true;
                    break;
                }
            }
            if (bad)
            {
                /*
                cout << "Bad lock and key: " << '\n';
                for (int num : lck)
                {
                    cout << num;
                }
                cout << '\n';
                for (int num : key)
                {
                    cout << num;
                }
                cout << '\n';
                */
                sum--;
            }
        }
    }
    printf("sum: %d\n", sum);
}
int main(int argc, char* argv[]) 
{
    ifstream inputFile(argv[1]);
    vector<vector<vector<char>>> schems;

    if (!inputFile) 
    {
        cerr << "Error opening file\n";
        return 1;
    }

    string line;
    vector<vector<char>> currentSchem;

    while (getline(inputFile, line)) 
    {
        if (line.empty()) 
        {
            if (!currentSchem.empty()) 
            {
                schems.push_back(currentSchem);
                currentSchem.clear();      
            }
        } 
        else 
        {
            vector<char> row(line.begin(), line.end());
            currentSchem.push_back(row);
        }
    }

    if (!currentSchem.empty()) 
    {
        schems.push_back(currentSchem);
    }

    inputFile.close();

    solve(schems);
}


