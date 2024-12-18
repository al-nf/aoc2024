#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <regex>

#define ULL unsigned long long

using namespace std;

vector<ULL> program(vector<ULL>& registers, const vector<ULL>& instructions)
{
    ULL opcode;
    ULL operand;
    vector<ULL> out;
    for (ULL i = 0; i < instructions.size(); i += 2)
    {
        opcode = instructions[i];
        const ULL operandLit = instructions[i + 1];
        operand = instructions[i + 1];

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
                registers[0] /= (1ULL << operand);
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
                out.push_back(operand % 8);
                break;
            }
            case 6:
            {
                registers[1] = registers[0] / (1ULL << operand);
                break;
            }
            case 7:
            {
                registers[2] = registers[0] / (1ULL << operand);
                break;
            }
        }
    }

    return out;
}

int main(int argc, char *argv[]) 
{
    ifstream inputFile(argv[1]);
    vector<ULL> registers(3, 0); 
    vector<ULL> instructions;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    regex registerRegex("(Register [A-C]): (\\d+)");
    regex instructionsRegex("Program: (.+)"); 

    while (getline(inputFile, line))
    {
        smatch match;

        if (regex_match(line, match, registerRegex))
        {
            char reg = match[1].str()[9]; 
            ULL value = stoi(match[2].str()); 
            
            if (reg == 'A')
                registers[0] = value;
            else if (reg == 'B')
                registers[1] = value;
            else if (reg == 'C')
                registers[2] = value;
        }
        else if (regex_match(line, match, instructionsRegex))
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

    vector<ULL> factors(instructions.size(), 0);

    while (true) 
    {
        ULL A = 0;
        for (size_t i = 0; i < factors.size(); ++i) 
        {
            A += pow(8.0, static_cast<double>(i)) * factors[i];
            registers[0] = A;
        }

        vector<ULL> output = program(registers, instructions);

        if (output == instructions) 
        {
            cout << A << endl;
            break;
        }

        for (int i = factors.size() - 1; i >= 0; --i) 
        {
            if (output.size() < static_cast<size_t>(i)) 
            {
                factors[i] += 1;
                break;
            }
            if (output[i] != instructions[i]) {
                factors[i] += 1;
                break;
            }
        }
    }
}

