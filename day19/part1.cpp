#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool startsWith(const string& str, const string& prefix) 
{
    return str.compare(0, prefix.size(), prefix) == 0;
}

bool solveDesign(const string& design, const vector<string>& patterns, string current) 
{
    if (current == design) 
    {
        return true;
    }

    for (const string& pattern : patterns) 
    {
        if (startsWith(design, current + pattern)) 
        {
            if (solveDesign(design, patterns, current + pattern)) 
            {
                return true;
            }
        }
    }

    return false;
}

void towels(const vector<string>& patterns, const vector<string>& designs) 
{
    int sum = 0;

    for (const string& design : designs) 
    {
        if (solveDesign(design, patterns, "")) 
        {
            sum++;
        }
    }

    printf("sum: %d\n", sum);
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

