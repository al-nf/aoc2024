#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Gate 
{
    string input1;
    string input2;
    string output;
    int op; 
};

void solve(map<string, bool>& states, vector<Gate>& gates) 
{
    set<string> brokenNodes;

    for (const auto& gate : gates) 
    {
        if (gate.output[0] == 'z' && gate.output != "z45" && gate.op != 2) 
        {
            brokenNodes.insert(gate.output);
        }
        if (gate.input1[0] == 'z') 
        {
            brokenNodes.insert(gate.input1);
        }
        if (gate.input2[0] == 'z') 
        {
            brokenNodes.insert(gate.input2);
        }

        if (gate.op == 2 && gate.output[0] != 'z' && !((gate.input1[0] == 'x' && gate.input2[0] == 'y') || (gate.input1[0] == 'y' && gate.input2[0] == 'x'))) 
        {
            brokenNodes.insert(gate.output);
        }

        if (gate.op == 2 && gate.output[0] != 'z') 
        {
            int count = count_if(gates.begin(), gates.end(), [&](const Gate& g) 
            {
                return g.input1 == gate.output || g.input2 == gate.output;
            });
            if (count != 2) 
            {
                brokenNodes.insert(gate.output);
            }
        }

        if (gate.op == 0 && gate.output[0] != 'z') 
        {
            int count = count_if(gates.begin(), gates.end(), [&](const Gate& g) 
            {
                return g.input1 == gate.output || g.input2 == gate.output;
            });
            if (count != 1 && !(gate.input1 == "x00" && gate.input2 == "y00")) 
            {
                brokenNodes.insert(gate.output);
            }
        }
    }

    vector<string> sortedResults(brokenNodes.begin(), brokenNodes.end());
    sort(sortedResults.begin(), sortedResults.end());
    for (size_t i = 0; i < sortedResults.size(); ++i) 
    {
        cout << sortedResults[i];
        if (i < sortedResults.size() - 1) 
        {
            cout << ",";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) 
{
    ifstream inputFile(argv[1]);
    map<string, bool> states;
    vector<Gate> gates;

    if (!inputFile) 
    {
        cerr << "Error opening file\n";
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        if (line.empty()) break;

        string wire = line.substr(0, 3);
        bool state = (line.substr(5, 1) == "1");
        states[wire] = state;
    }

    regex pattern(R"((\w+)\s(AND|OR|XOR)\s(\w+)\s->\s(\w+))");
    while (getline(inputFile, line)) 
    {
        smatch match;
        if (regex_search(line, match, pattern)) 
        {
            Gate gate;
            gate.input1 = match[1];
            gate.input2 = match[3];
            gate.output = match[4];

            string op = match[2];
            if (op == "AND") 
            {
                gate.op = 0;
            }
            else if (op == "OR") 
            {
                gate.op = 1;
            }
            else if (op == "XOR") 
            {
                gate.op = 2;
            }

            gates.push_back(gate);
        }
    }

    inputFile.close();
    solve(states, gates);
}

