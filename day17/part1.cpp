#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;

void program(vector<int>& registers, const vector<int>& instructions)
{
    int opcode;
    int operand;
    vector<int> out;
    for (int i = 0; i < instructions.size(); i += 2)
    {
        opcode = instructions[i];
        const int operandLit = instructions[i+1];
        operand = instructions[i+1];

        switch (operand)
        {
            case 4:
            {
                operand = registers[0];
                break;
            }
            case 5:
            {
                operand = registers[1];
                break;
            }
            case 6:
            {
                operand = registers[2];
                break;
            }
            default:
                break;
        }

        switch (opcode)
        {
            case 0:
            {
                registers[0] /= (int)pow(2, operand);
                break;
            }
            case 1:
            {
                registers[1] = registers[1] ^ operandLit;
                break;
            }
            case 2:
            {
                registers[1] = operand % 8;
                break;
            }
            case 3:
            {
                if (registers[0] != 0)
                {
                    i = operandLit;
                    i -= 2;
                }
                break;
            }
            case 4:
            {
                registers[1] = registers[1] ^ registers[2];
                break;
            }
            case 5:
            {
                out.push_back(operand%8);
                break;
            }
            case 6:
            {
                registers[1] = registers[0] / (int)pow(2, operand);
                break;
            }
            case 7:
            {
                registers[2] = registers[0] / (int)pow(2, operand);
                break;
            }
        }
    }

    for (int num : out)
    {
        cout << num << ", ";
    }
    cout << "\n";
}
int main(int argc, char *argv[])
{
    ifstream inputFile(argv[1]);
    vector<int> registers(3, 0); 
    vector<int> instructions;

    if (!inputFile)
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    regex registerRegex("(Register [A-C]): (\\d+)");
    regex programRegex("Program: (.+)"); 

    while (getline(inputFile, line))
    {
        smatch match;

        if (regex_match(line, match, registerRegex))
        {
            char reg = match[1].str()[9]; 
            int value = stoi(match[2].str()); 
            
            if (reg == 'A')
                registers[0] = value;
            else if (reg == 'B')
                registers[1] = value;
            else if (reg == 'C')
                registers[2] = value;
        }
        else if (regex_match(line, match, programRegex))
        {
            string instructionsLine = match[1].str();
            stringstream ss(instructionsLine);
            string instruction;
            
            while (getline(ss, instruction, ','))
            {
                instructions.push_back(stoi(instruction));
            }
        }
    }
    inputFile.close();

    program(registers, instructions);
}

