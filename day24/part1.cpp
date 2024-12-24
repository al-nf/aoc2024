#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <cmath>

using namespace std;

struct Gate 
{
    string input1;
    string input2;
    string output;
    int op; 
    bool processed = false;
};

bool canProcess(const Gate& gate, const map<string, bool>& states) 
{
    return states.find(gate.input1) != states.end() && states.find(gate.input2) != states.end();
}

bool processGate(const Gate& gate, const map<string, bool>& states) 
{
    bool in1 = states.at(gate.input1);
    bool in2 = states.at(gate.input2);
    
    switch (gate.op) 
    {
        case 0: return in1 && in2;
        case 1: return in1 || in2;
        case 2: return in1 != in2;
        default: return false;
    }
}

string traverse(const map<string, bool>& data) 
{
    vector<pair<int, bool>> zWires;
    for (const auto& pair : data) 
    {
        if (pair.first[0] == 'z') 
        {
            string numStr = pair.first.substr(1);
            zWires.push_back({stoi(numStr), pair.second});
        }
    }
    
    sort(zWires.begin(), zWires.end());
    
    string result;
    for (const auto& wire : zWires) 
    {
        result += (wire.second ? "1" : "0");
    }
    return result;
}

void solve(map<string, bool>& states, vector<Gate>& gates) 
{
    bool progress;
    do 
    {
        progress = false;
        for (Gate& gate : gates) 
        {
            if (!gate.processed && canProcess(gate, states)) 
            {
                states[gate.output] = processGate(gate, states);
                gate.processed = true;
                progress = true;
            }
        }
    } while (progress);

    string binStr = traverse(states);
    long int sum = 0;
    for (int i = 0; i < binStr.length(); i++) 
    {
        if (binStr[i] == '1') {
            sum += pow(2, i);
        }
    }
    cout << '\n' << binStr << '\n';
    printf("sum: %ld\n", sum);
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
            if (op == "AND") gate.op = 0;
            else if (op == "OR") gate.op = 1;
            else if (op == "XOR") gate.op = 2;
            
            gates.push_back(gate);
        }
    }

    inputFile.close();
    solve(states, gates);
}
