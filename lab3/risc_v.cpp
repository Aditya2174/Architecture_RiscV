#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<string> output;
#define MAXSIZE 1000
ll label[MAXSIZE];
int number = 1;
string LongToString(long long long_num) // converts a long long integer to string for output purposes
{
    stack<char> stringStack;
    string signValue = "";

    if (long_num < 0)
    {
        signValue = "-";
        long_num = -long_num;
    }
    if (long_num == 0)
    {
        stringStack.push('0');
    }

    while (long_num > 0)
    {
        char convertedDigit = long_num % 10 + '0';
        stringStack.push(convertedDigit);
        long_num /= 10;
    }

    string long_to_string = "";

    while (!stringStack.empty())
    {
        long_to_string += stringStack.top();
        stringStack.pop();
    }

    return signValue + long_to_string;
}
void r_type(ll binary[])
{
    string instruction;
    ll funct_7 = 0;
    ll shift = 6;
    for (ll i = 0; i < 7; i++)
    {
        funct_7 += (binary[i]) << (shift);
        shift--;
    }
    ll rs_2 = 0;
    shift = 4;
    for (ll i = 7; i < 12; i++)
    {
        rs_2 += (binary[i]) << (shift);
        shift--;
    }
    ll rs_1 = 0;
    shift = 4;
    for (ll i = 12; i < 17; i++)
    {
        rs_1 += (binary[i]) << (shift);
        shift--;
    }
    ll funct_3 = 0;
    shift = 2;
    for (ll i = 17; i < 20; i++)
    {
        funct_3 += (binary[i]) << (shift);
        shift--;
    }
    // cout << funct_7 << " " << funct_3 << endl ;
    ll rd = 0;
    shift = 4;
    for (ll i = 20; i < 25; i++)
    {
        rd += (binary[i]) << (shift);
        shift--;
    }
    if (funct_7 == 0)
    {
        if (funct_3 == 0)
        {
            instruction = "add";
        }
        else if (funct_3 == 1)
        {
            instruction = "sll";
        }
        else if (funct_3 == 2)
        {
            instruction = "slt";
        }
        else if (funct_3 == 3)
        {
            instruction = "sltu";
        }
        else if (funct_3 == 4)
        {
            instruction = "xor";
        }
        else if (funct_3 == 5)
        {
            instruction = "srl";
        }
        else if (funct_3 == 6)
        {
            instruction = "or";
        }
        else if (funct_3 == 7)
        {
            instruction = "and";
        }
    }
    else if (funct_7 == 32)
    {
        if (funct_3 == 0)
        {
            instruction = "sub";
        }
        else if (funct_3 == 5)
        {
            instruction = "sra";
        }
    }

    // cout << instruction << " x" << rd << " x" << rs_1 << " x" << rs_2 << endl;
    string inst = instruction + " x" + LongToString(rd) + ", x" + LongToString(rs_1) + ", x" + LongToString(rs_2);
    output.push_back(inst);
}
void i_type(ll binary[], ll type)
{
    string instruction;
    ll immediate = 0;
    ll shift = 11;
    ll val_imm = 0;
    for (ll i = 0; i < 12; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }
    if (immediate > 2047)
    {
        immediate -= 4096;
    }
    ll check = 0;
    shift = 5;
    for (ll i = 0; i < 6; i++)
    {
        check += (binary[i]) << (shift);
        shift--;
    }
    shift = 5;
    for (ll i = 6 ; i < 12 ; i++)
    {
        val_imm += (binary[i]) << (shift);
        shift--;
    }
    ll rs_1 = 0;
    shift = 4;
    for (ll i = 12; i < 17; i++)
    {
        rs_1 += (binary[i]) << (shift);
        shift--;
    }
    ll funct_3 = 0;
    shift = 2;
    for (ll i = 17; i < 20; i++)
    {
        funct_3 += (binary[i]) << (shift);
        shift--;
    }
    ll rd = 0;
    shift = 4;
    for (ll i = 20; i < 25; i++)
    {
        rd += (binary[i]) << (shift);
        shift--;
    }
    if (type == 1)
    {
        if (funct_3 == 0)
        {
            instruction = "addi";
        }
        else if (funct_3 == 1)
        {
            instruction = "slli";
        }
        else if (funct_3 == 2)
        {
            instruction = "slti";
        }
        else if (funct_3 == 3)
        {
            instruction = "sltiu";
        }
        else if (funct_3 == 4)
        {
            instruction = "xori";
        }
        else if (funct_3 == 5)
        {    
            if (check == 0)
                instruction = "srli";
            else if (check >= 16)
                instruction = "srai";
        }
        else if (funct_3 == 6)
        {
            instruction = "ori";
        }
        else if (funct_3 == 7)
        {
            instruction = "andi";
        }

        //  cout << instruction << " x" << rd << " x" << rs_1 << " " << immediate  << endl;
        string inst;
        if (funct_3 != 1 && funct_3 != 5)
         inst = instruction + " x" + LongToString(rd) + ", x" + LongToString(rs_1) + ", " + LongToString(immediate);
        else
         inst = instruction + " x" + LongToString(rd) + ", x" + LongToString(rs_1) + ", " + LongToString(val_imm);
        output.push_back(inst);
    }
    else if (type == 2)
    {
        if (funct_3 == 0)
        {
            instruction = "lb";
        }
        else if (funct_3 == 1)
        {
            instruction = "lh";
        }
        else if (funct_3 == 2)
        {
            instruction = "lw";
        }
        else if (funct_3 == 3)
        {
            instruction = "ld";
        }
        else if (funct_3 == 4)
        {
            instruction = "lbu";
        }
        else if (funct_3 == 5)
        {
            instruction = "lhu";
        }
        else if (funct_3 == 6)
        {
            instruction = "lwu";
        }
        //  cout << instruction << " x" << rd << " x" << rs_1 << " " << immediate  << endl;

        string inst = instruction + " x" + LongToString(rd) + ", " + LongToString(immediate) + "(x" + LongToString(rs_1) +")";
        output.push_back(inst);
    }
    else if (type == 3)
    {
        if (funct_3 == 0)
        {
            instruction = "jalr";
        }

        //  cout << instruction << " x" << rd << " x" << rs_1 << " " << immediate  << endl;
        string inst = instruction + " x" + LongToString(rd) + ", x" + LongToString(rs_1) + ", " + LongToString(immediate);
        output.push_back(inst);
    }
    else if (type == 4)
    {
        if (funct_3 == 0)
        {
            if (immediate == 0)
                instruction = "ecall";
            else
                instruction = "ebreak";
        }

        //  cout << instruction << " x" << rd << " x" << rs_1 << " " << immediate  << endl;
        string inst = instruction + " x" + LongToString(rd) + ", x" + LongToString(rs_1) + ", " + LongToString(immediate);
        output.push_back(inst);
    }
}
void s_type(ll binary[])
{
    string instruction;
    ll immediate = 0;
    ll shift = 11;
    for (ll i = 0; i < 7; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }
    if (immediate > 2047)
    {
        immediate -= 4096;
    }
    ll rs_2 = 0;
    shift = 4;
    for (ll i = 7; i < 12; i++)
    {
        rs_2 += (binary[i]) << (shift);
        shift--;
    }
    ll rs_1 = 0;
    shift = 4;
    for (ll i = 12; i < 17; i++)
    {
        rs_1 += (binary[i]) << (shift);
        shift--;
    }
    ll funct_3 = 0;
    shift = 2;
    for (ll i = 17; i < 20; i++)
    {
        funct_3 += (binary[i]) << (shift);
        shift--;
    }
    shift = 4;
    for (ll i = 20; i < 25; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }

    if (funct_3 == 0)
    {
        instruction = "sb";
    }
    else if (funct_3 == 1)
    {
        instruction = "sh";
    }
    else if (funct_3 == 2)
    {
        instruction = "sw";
    }
    else if (funct_3 == 3)
    {
        instruction = "sd";
    }
    // cout << instruction << " x" << rs_2 << " (" << immediate << ")"  << rs_1 << " " << endl;
    string inst = instruction + " x" + LongToString(rs_2) + ", " + LongToString(immediate) + "(x" + LongToString(rs_1) + ") ";
    output.push_back(inst);
}
void b_type(ll binary[], ll i)
{
    string instruction;
    ll immediate = 0;
    immediate += (binary[0]) << (12);
    ll shift = 10;
    for (ll i = 1; i < 7; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }
    ll rs_2 = 0;
    shift = 4;
    for (ll i = 7; i < 12; i++)
    {
        rs_2 += (binary[i]) << (shift);
        shift--;
    }
    ll rs_1 = 0;
    shift = 4;
    for (ll i = 12; i < 17; i++)
    {
        rs_1 += (binary[i]) << (shift);
        shift--;
    }
    ll funct_3 = 0;
    shift = 2;
    for (ll i = 17; i < 20; i++)
    {
        funct_3 += (binary[i]) << (shift);
        shift--;
    }
    shift = 4;
    for (ll i = 20; i < 24; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }
    immediate += binary[24] << (11);
    if (immediate > 2047)
    {
        immediate -= 4096 * 2;
    }
    if (funct_3 == 0)
    {
        instruction = "beq";
    }
    else if (funct_3 == 1)
    {
        instruction = "bne";
    }
    else if (funct_3 == 4)
    {
        instruction = "blt";
    }
    else if (funct_3 == 5)
    {
        instruction = "bge";
    }
    else if (funct_3 == 6)
    {
        instruction = "bltu";
    }
    else if (funct_3 == 7)
    {
        instruction = "bgeu";
    }
    if (label[i + immediate / 4] == 0)
    {
        label[i + immediate / 4] = number;
        number++;
    }
    // cout << immediate << " hello \n";
    // cout << instruction << " x" << rs_1 << " x" << rs_2 << " L" << label[i+immediate/4] << endl;
    string inst = instruction + " x" + LongToString(rs_1) + ", x" + LongToString(rs_2) + ", L" + LongToString(label[i + immediate / 4]);
    output.push_back(inst);
}
void u_type(ll binary[], ll type)
{
    ll immediate = 0;
    ll shift = 31;
    string instruction;
    for (ll i = 0; i < 20; i++)
    {
        immediate += (binary[i]) << (shift);

        shift--;
    }
    ll rd = 0;
    shift = 4;
    for (ll i = 20; i < 25; i++)
    {
        rd += (binary[i]) << (shift);
        shift--;
    }
    if (type == 1)
    {
        instruction = "lui";
    }
    else if (type == 2)
    {
        instruction = "auipc";
    }
    char hex[10];
    sprintf(hex, "%llX", immediate); // convert number to hex

    string modified;
    for (int i = 0; i < hex[i] != '\0'; i++)
        modified.push_back(hex[i]);
    ll size = modified.length();
    modified = modified.substr(0, size - 3);

    string inst = instruction + " x" + LongToString(rd) + ", 0x" + modified;
    output.push_back(inst);
}
void j_type(ll binary[], ll i)
{
    ll immediate = 0;
    immediate += (binary[0]) << (20);
    ll shift = 10;
    for (ll i = 1; i < 11; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }
    immediate += (binary[11]) << (11);
    shift = 19;
    for (ll i = 12; i < 20; i++)
    {
        immediate += (binary[i]) << (shift);
        shift--;
    }
    ll rd = 0;
    shift = 4;
    if (immediate > 1048576)
    {
        immediate -= 2 * 1048576;
    }
    for (ll i = 20; i < 25; i++)
    {
        rd += (binary[i]) << (shift);
        shift--;
    }
    if (label[i + immediate / 4] == 0)
    {
        label[i + immediate / 4] = number;
        number++;
    }
    // cout << immediate;
    // cout << "jal" << " x" << rd << " L" << label[i+immediate/4] << endl;
    string inst = "jal x" + LongToString(rd) + ", L" + LongToString(label[i + immediate / 4]);
    output.push_back(inst);
}
int main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    for (ll i = 0; i < MAXSIZE; i++)
        label[i] = 0;

    vector<string> input;
    string line;
    ll n = 0;
    while (getline(cin, line))
    {
        input.push_back(line);
        n++;
    }
    // converting into an integer using stoi function
    for (ll i = 0; i < n; i++)
    {
        ll machine_code = stoll(input[i], 0, 16);
        ll binary[32]; // converting the number into binary form
        ll dummy = machine_code;
        for (ll i = 1; i <= 32; i++)
        {
            binary[32 - i] = (dummy % 2);
            dummy /= 2;
        }
        // find opcode
        ll opcode = (machine_code) & (127);
        if (opcode == stoll("0110011", 0, 2)) // RISCV-R format
        {
            // cout << "It is R type instruction" << endl;
            r_type(binary);
        }
        else if (opcode == stoll("0010011", 0, 2))
        {
            // cout << "It is I type instruction" << endl;
            i_type(binary, 1);
        }
        else if (opcode == stoll("0000011", 0, 2))
        {
            // cout << "It is I type instruction" << endl;
            i_type(binary, 2);
        }
        else if (opcode == stoll("1100111", 0, 2))
        {
            // cout << "It is I type instruction" << endl;
            i_type(binary, 3);
        }
        else if (opcode == stoll("1110011", 0, 2))
        {
            // cout << "It is I type instruction" << endl;
            i_type(binary, 4);
        }
        else if (opcode == stoll("0100011", 0, 2))
        {
            //  cout << "It is S type instruction" << endl;
            s_type(binary);
        }
        else if (opcode == stoll("1100011", 0, 2))
        {
            //  cout << "It is B type instruction" << endl;
            b_type(binary, i);
        }
        else if (opcode == stoll("0110111", 0, 2))
        {
            // cout << "It is U type instruction" << endl;
            u_type(binary, 1);
        }
        else if (opcode == stoll("0010111", 0, 2))
        {
            // cout << "It is U type instruction" << endl;
            u_type(binary, 2);
        }
        else if (opcode == stoll("1101111", 0, 2))
        {
            // cout << "It is J type instruction" << endl;
            j_type(binary, i);
        }
    }
    for (int i = 0; i < output.size(); i++)
    {
        if (label[i])
        {
            cout << "L" << label[i] << ": ";
        }
        cout << output[i] << "\n";
    }
}