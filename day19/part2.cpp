#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#define ULL unsigned long long

using namespace std;

bool startsWith(const string& str, const string& prefix) 
{
    return str.compare(0, prefix.size(), prefix) == 0;
}

ULL count(const string& design, const vector<string>& patterns) 
{
    int n = design.size();
    vector<ULL> dp(n + 1, 0);  
    dp[0] = 1;  

    for (int i = 1; i <= n; ++i) 
    {
        for (const string& pattern : patterns) 
        {
            int len = pattern.size();
            if (i >= len && design.substr(i - len, len) == pattern) 
            {
                dp[i] += dp[i - len];  
            }
        }
    }

    return dp[n];  
}

void towels(const vector<string>& patterns, const vector<string>& designs) 
{
    ULL sum = 0;

    for (const string& design : designs) 
    {
        sum += count(design, patterns);
    }

    printf("sum: %llu\n", sum);  
}

int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);

    if (!inputFile) 
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    vector<string> patterns;
    vector<string> designs;

    string line;

    while (getline(inputFile, line)) 
    {
        if (line.empty()) 
        {
            break;
        }

        stringstream ss(line);
        string group;

        while (getline(ss, group, ','))
        {
            group.erase(remove(group.begin(), group.end(), ' '), group.end());
            patterns.push_back(group);
        }
    }

    while (getline(inputFile, line)) 
    {
        designs.push_back(line);
    }

    inputFile.close();

    towels(patterns, designs);
}

