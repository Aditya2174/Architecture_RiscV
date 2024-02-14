#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    map<string, string> mp;  // creating a map to store the register names and their corresponding names and using mp values for comparison
    mp["x0"] = "zero";
    mp["x1"] = "ra";
    mp["x2"] = "sp";
    mp["x3"] = "gp";
    mp["x4"] = "tp";
    mp["x5"] = "t0";
    mp["x6"] = "t1";
    mp["x7"] = "t2";
    mp["x8"] = "fp";
    mp["x9"] = "s1";
    mp["x10"] = "a0";
    mp["x11"] = "a1";
    mp["x12"] = "a2";
    mp["x13"] = "a3";
    mp["x14"] = "a4";
    mp["x15"] = "a5";
    mp["x16"] = "a6";
    mp["x17"] = "a7";
    mp["x18"] = "s2";
    mp["x19"] = "s3";
    mp["x20"] = "s4";
    mp["x21"] = "s5";
    mp["x22"] = "s6";
    mp["x23"] = "s7";
    mp["x24"] = "s8";
    mp["x25"] = "s9";
    mp["x26"] = "s10";
    mp["x27"] = "s11";
    mp["x28"] = "t3";
    mp["x29"] = "t4";
    mp["x30"] = "t5";
    mp["x31"] = "t6";
    mp["zero"] = "zero";
    mp["ra"] = "ra";
    mp["sp"] = "sp";
    mp["gp"] = "gp";
    mp["tp"] = "tp";
    mp["t0"] = "t0";
    mp["t1"] = "t1";
    mp["t2"] = "t2";
    mp["fp"] = "fp";
    mp["s0"] = "fp";
    mp["s1"] = "s1";
    mp["a0"] = "a0";
    mp["a1"] = "a1";
    mp["a2"] = "a2";
    mp["a3"] = "a3";
    mp["a4"] = "a4";
    mp["a5"] = "a5";
    mp["a6"] = "a6";
    mp["a7"] = "a7";
    mp["s2"] = "s2";
    mp["s3"] = "s3";
    mp["s4"] = "s4";
    mp["s5"] = "s5";
    mp["s6"] = "s6";
    mp["s7"] = "s7";
    mp["s8"] = "s8";
    mp["s9"] = "s9";
    mp["s10"] = "s10";
    mp["s11"] = "s11";
    mp["t3"] = "t3";
    mp["t4"] = "t4";
    mp["t5"] = "t5";
    mp["t6"] = "t6";
    freopen("input.txt", "r", stdin);  // inputting and outputting in a file 
    freopen("output.txt", "w", stdout);

    vector<string> input;  // creating a vector to store the input
    string line;
    ll n = 0;
    while (getline(cin, line))
    {
        input.push_back(line); // storing the input in the vector
        n++; // counting the number of lines
    }

    ll cycles_fwd = n;
    ll cycles = n;

    vector<vector<string>> vv(n + 1); // creating a vector of vector to store the input in a 2d vector

    vector<pair<int, bool>> pos(n + 1);  // creating a vector of pair to store the count of the nop and whether it is present or not

    vector<pair<int, bool>> pos_fwd(n + 1, {0, 0});  // creating a vector of pair to store the count of the nop in the forward case and whether it is present or not
    
    // parsing the input and storing it in the 2d vector
    for (int i = 0; i < n; i++)
    {
        string temp;
        int count = 0;
        ll x = input[i].size();
        // vv].erase(vv].begin(), vv].end());
        for (int j = 0; j < x; j++)
        {

            if (input[i][j] == ' ')
            {

                vv[i].push_back(temp);
                temp.clear();
            }
            else if (input[i][j] == ',')
            {
                count++;
                continue;
            }
            else
                temp.push_back(input[i][j]);
        }
        vv[i].push_back(temp);
        if (count == 1)
        {
            string s;
            bool y = 0;
            for (int x = 0; x < vv[i][2].size(); x++)
            {
                if (vv[i][2][x] == '(')
                {
                    y = 1;
                }
                else if (y && vv[i][2][x] != ')')
                {
                    s.push_back(vv[i][2][x]);
                }
            }
            vv[i][2] = s;
            vv[i].push_back("null");
            vv[i].push_back("1");
        }
        else
            vv[i].push_back("2");

        if (vv[i][4] == "2" && mp[vv[i][1]] != "zero") // checking for R and I type instructions
        {
            int count = 0;
            for (int k = i - 1; k >= i - 2 && k >= 0; k--)
            {

                if (vv[k][4] == "2" && mp[vv[k][1]] != "zero") // for R type or I type instructions
                {

                    if (mp[vv[k][1]] == mp[vv[i][2]] || mp[vv[k][1]] == mp[vv[i][3]])
                    {
                        int diff = i - k;
                        if (diff == 1)
                        {

                            diff += pos[k].first;
                        }
                        else if (diff == 2)
                        {

                            diff += pos[k].first + pos[k + 1].first;
                        }
                        if (diff == 1)
                        {

                            if (2 > pos[k].first)
                            {
                                cycles += 2 - pos[k].first;
                                pos[k] = {2, 1};
                            }
                        }
                        else if (diff == 2)
                        {

                            if (1 > pos[k + 1].first)
                            {
                                cycles += 1 - pos[k + 1].first;
                                pos[k + 1] = {1, 1};
                            }
                        }
                    }
                }
                else if (vv[k][0] == "lw" || vv[k][0] == "ld" || vv[k][0] == "lh" || vv[k][0] == "lb" || vv[k][0] == "lbu" || vv[k][0] == "lhu" || vv[k][0] == "lwu" || vv[k][0] == "lui" && mp[vv[k][1]] != "zero")
                {
                    if (mp[vv[k][1]] == mp[vv[i][2]] || (vv[i][3][0] == 'x' && mp[vv[k][1]] == mp[vv[i][3]]))
                    {
                        int diff = i - k;
                        if (diff == 1)
                        {
                            diff += pos[k].first;
                        }
                        else if (diff == 2)
                        {
                            diff += pos[k].first + pos[k + 1].first;
                        }
                        // else if (diff == 3)
                        // {
                        //     diff += pos[k].first + pos[k + 1].first + pos[k + 2].first;
                        // }
                        if (diff == 1)
                        {
                            if (2 > pos[k].first)
                            {
                                cycles += 2 - pos[k].first;
                                pos[k] = {2, 1};
                            }
                            pos_fwd[k] = {1, 1};
                            cycles_fwd += 1;
                        }
                        else if (diff == 2)
                        {
                            if (1 > pos[k + 1].first)
                            {
                                cycles += 1 - pos[k + 1].first;
                                pos[k + 1] = {1, 1};
                            }
                        }
                        // else if (diff == 3)
                        // {
                        //     pos[k] = {1, 1};
                        //     cycles++;
                        // }
                    }
                }
            }
        }
        else if (vv[i][0] == "lw" || vv[i][0] == "ld" || vv[i][0] == "lh" || vv[i][0] == "lb" || vv[i][0] == "lbu" || vv[i][0] == "lhu" || vv[i][0] == "lwu" || vv[i][0] == "lui" && mp[vv[i][1]] != "zero")
        {

            for (int k = i - 1; k >= i - 2 && k >= 0; k--)
            {

                if (vv[k][4] == "2" && mp[vv[k][1]] != "zero") // for R type or I type instructions
                {

                    if (mp[vv[k][1]] == mp[vv[i][2]])
                    {
                        int diff = i - k;
                        if (diff == 1)
                        {
                            diff += pos[k].first;
                        }
                        else if (diff == 2)
                        {
                            diff += pos[k].first + pos[k + 1].first;
                        }
                        if (diff == 1)
                        {
                            if (2 > pos[k].first)
                            {
                                cycles += 2 - pos[k].first;
                                pos[k] = {2, 1};
                            }
                        }
                        else if (diff == 2)
                        {
                            if (1 > pos[k + 1].first)
                            {
                                cycles += 1 - pos[k + 1].first;
                                pos[k + 1] = {1, 1};
                            }
                        }
                    }
                }
                else if (vv[k][0] == "lw" || vv[k][0] == "ld" || vv[k][0] == "lh" || vv[k][0] == "lb" || vv[k][0] == "lbu" || vv[k][0] == "lhu" || vv[k][0] == "lwu" || vv[k][0] == "lui" && mp[vv[k][1]] != "zero")
                {
                    // cout << mp[vv[k][2]] << " " << mp[vv[i][1]] << " ";
                    // cout << vv[k][2] << " " << vv[i][1] << " ";
                    if (mp[vv[k][1]] == mp[vv[i][2]])
                    {
                        int diff = i - k;
                        if (diff == 1)
                        {
                            diff += pos[k].first;
                        }
                        else if (diff == 2)
                        {
                            diff += pos[k].first + pos[k + 1].first;
                        }
                        // else if (diff == 3)
                        // {
                        //     diff += pos[k].first + pos[k + 1].first + pos[k + 2].first;
                        // }
                        if (diff == 1)
                        {
                            if (2 > pos[k].first)
                            {
                                cycles += 2 - pos[k].first;
                                pos[k] = {2, 1};
                            }
                            pos_fwd[k] = {1, 1};
                            cycles_fwd += 1;
                        }
                        else if (diff == 2)
                        {
                            if (1 > pos[k + 1].first)
                            {
                                cycles += 1 - pos[k + 1].first;
                                pos[k + 1] = {1, 1};
                            }
                        }
                        // else if (diff == 3)
                        // {
                        //     pos[k] = {1, 1};
                        //     cycles++;
                        // }
                    }
                }
                else if (vv[k][0] == "sw" || vv[k][0] == "sd" || vv[k][0] == "sh" || vv[k][0] == "sb" && mp[vv[k][1]] != "zero")
                {
                   
                    // no need to do anything
                }
            }
        }
        else if (vv[i][0] == "sw" || vv[i][0] == "sd" || vv[i][0] == "sh" || vv[i][0] == "sb" && mp[vv[i][1]] != "zero")
        {
            for (int k = i - 1; k >= i - 2 && k >= 0; k--)
            {
                if (vv[k][4] == "2" && mp[vv[k][1]] != "zero")
                {
                    if (mp[vv[k][1]] == mp[vv[i][2]] || mp[vv[k][1]] == mp[vv[i][1]])
                    {
                        int diff = i - k;
                        if (diff == 1)
                        {
                            diff += pos[k].first;
                        }
                        else if (diff == 2)
                        {
                            diff += pos[k].first + pos[k + 1].first;
                        }
                        if (diff == 1)
                        {
                            if (2 > pos[k].first)
                            {
                                cycles += 2 - pos[k].first;
                                pos[k] = {2, 1};
                            }
                        }
                        else if (diff == 2)
                        {
                            if (1 > pos[k + 1].first)
                            {
                                cycles += 1 - pos[k + 1].first;
                                pos[k + 1] = {1, 1};
                            }
                        }
                    }
                }
                else if (vv[k][0] == "lw" || vv[k][0] == "ld" || vv[k][0] == "lh" || vv[k][0] == "lb" || vv[k][0] == "lbu" || vv[k][0] == "lhu" || vv[k][0] == "lwu"  || vv[k][0] == "lui" && mp[vv[k][1]] != "zero")
                {
                    if (mp[vv[k][1]] == mp[vv[i][2]])
                    {
                        int diff = i - k;
                        if (diff == 1)
                        {
                            diff += pos[k].first;
                        }
                        else if (diff == 2)
                        {
                            diff += pos[k].first + pos[k + 1].first;
                        }
                        // else if (diff == 3)
                        // {
                        //     diff += pos[k].first + pos[k + 1].first + pos[k + 2].first;
                        // }
                        if (diff == 1)
                        {
                            if (2 > pos[k].first)
                            {
                                cycles += 2 - pos[k].first;
                                pos[k] = {2, 1};
                            }
                            pos_fwd[k] = {1, 1};
                            cycles_fwd += 1;
                        }
                        else if (diff == 2)
                        {
                            if (1 > pos[k + 1].first)
                            {
                                cycles += 1 - pos[k + 1].first;
                                pos[k + 1] = {1, 1};
                            }
                        }
                        // else if (diff == 1)
                        // {
                        //     pos[k] = {1, 1};
                        //     cycles++;
                        // }
                    }
                }
                else if (vv[k][0] == "sw" || vv[k][0] == "sd" || vv[k][0] == "sh" || vv[k][0] == "sb")
                {
                    // do nothing 
                }
            }
        }
    }

    // printing the output

    cout << "Without Forwarding And Hazard Detection " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << input[i] << endl;
        if (pos[i].second == 1)
        {
            for (int j = 0; j < pos[i].first; j++)
            {
                cout << "nop" << endl;
            }
        }
    }
    cout << "Total cycles: ";
    cout << cycles + 4 << endl;
    puts(" ");
    cout << "With Forwarding But Without Hazard Detection " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << input[i] << endl;
        if (pos_fwd[i].second == 1)
        {
            for (int j = 0; j < pos_fwd[i].first; j++)
            {
                cout << "nop" << endl;
            }
        }
    }
    cout << "Total cycles: ";
    cout << cycles_fwd + 4 << endl;
}