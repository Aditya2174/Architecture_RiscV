#include <bits/stdc++.h>
#include <time.h>
using namespace std;
typedef long long ll;
#define MAX 100000000
vector<string> full_address;
string decToHex(ll n, ll count)   // converts a decimal to hexadecimal 
{

    string ans;
    int x = 0;
    if (count == 0)
    {
        ans.push_back('0');
        return ans;
    }
    while (x != count)
    {
        ll temp = 0;
        temp = n % 16;
        if (temp < 10)
        {
            ans.push_back(temp + 48);
        }
        else
        {
            ans.push_back(temp + 55);
        }
        n = n / 16;
        x++;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
// direct mapped cache 
void dmc(vector<vector<ll>> &meta_data, ll number_of_blocks, ll block_size, string replacement_policy, string write_policy, ll used_bytes_for_index, ll used_bytes_for_tag)
{
    ofstream cache_output("output.txt");
    int x = 0;
    ll my_cache[number_of_blocks][2];
    for (int i = 0; i < number_of_blocks; i++)
    {
        my_cache[i][0] = 0;
    }
    ll reads = 0;
    ll writes = 0;
    for (auto instruction : meta_data)
    {
        bool hits = 0;
        bool misses = 1;
        if (instruction[0] == 0)
        {
            reads++;
            ll index = instruction[1];
            ll tag = instruction[2];
            if (my_cache[index][0] == 0)
            {
                misses = true;
                my_cache[index][0] = 1;
                my_cache[index][1] = tag;
            }
            else
            {
                if (my_cache[index][1] == tag)
                {
                    hits = true;
                }
                else
                {
                    misses = true;
                    my_cache[index][1] = tag;
                }
            }
        }
        else
        {
            writes++;
            ll index = instruction[1];
            ll tag = instruction[2];

            if (my_cache[index][0] == 0)
            {
                misses = true;

                if (write_policy == "WB")
                {
                    my_cache[index][1] = tag;
                    my_cache[index][0] = 1;
                }
            }
            else
            {
                if (my_cache[index][1] == tag)
                {
                    hits = true;
                }
                else
                {
                    misses = true;
                    if (write_policy == "WB")
                        my_cache[index][1] = tag;
                }
            }
        }

        string index = decToHex(instruction[1], used_bytes_for_index);
        string tag = decToHex(instruction[2], used_bytes_for_tag);

        if (!hits)
        {

            cache_output << "Address: " << full_address[x] << ", Set: 0x" << index << ", Miss, "
                         << "Tag: "
                         << "0x" << tag << endl;
            x++;
        }
        else
        {

            cache_output << "Address: " << full_address[x] << ", Set: 0x" << index << ", Hit, "
                         << "Tag: "
                         << "0x" << tag << endl;
            x++;
        }
    }
}
// fully associative cache 
void fac(vector<vector<ll>> &meta_data, ll number_of_blocks, ll block_size, ll associativity, string replacement_policy, string write_policy, ll used_bytes_for_index, ll used_bytes_for_tag)
{
    ofstream cache_output("output.txt");
    int x = 0;
    ll my_cache[number_of_blocks][2];
    ll LRU[number_of_blocks];
    ll fifo[number_of_blocks];
    for (int i = 0; i < number_of_blocks; i++)
    {
        my_cache[i][0] = 0;
        LRU[i] = 0;
        fifo[i] = 0;
    }

    for (auto instruction : meta_data)
    {
        ll max_fifo = 0;
        bool misses = 1;
        bool hits = 0;
        ll tag = instruction[2];
        ll location = -1;
        ll maxi = 0;
        ll pos = 0;
        ll mini = 1e9;
        if (instruction[0] == 0)
        {
            for (int i = 0; i < number_of_blocks; i++)
            {
                if (my_cache[i][0] == 1 && my_cache[i][1] == tag)
                {
                    hits = true;
                    LRU[i] = -1;
                    // fifo[i] = max_fifo + 1;
                    // max_fifo++;
                }
                else if (my_cache[i][0] == 0)
                {
                    location = i;
                }

                if (maxi < LRU[i] && replacement_policy == "LRU")
                {
                    maxi = LRU[i];
                    pos = i;
                }
                else if (mini > fifo[i] && replacement_policy == "FIFO")
                {
                    mini = fifo[i];
                    pos = i;
                }
                max_fifo = max(max_fifo, fifo[i]);
            }

            if (!hits)
            {
                if (location != -1)
                {
                    my_cache[location][0] = 1;
                    my_cache[location][1] = tag;
                    if (replacement_policy == "LRU")
                    {
                        LRU[location] = -1;
                    }
                    if (replacement_policy == "FIFO")
                    {
                        fifo[location] = max_fifo + 1;
                        max_fifo++;
                    }
                }
                else
                {
                    if (replacement_policy == "RANDOM")
                    {
                        pos = rand() % number_of_blocks;
                    }
                    my_cache[pos][0] = 1;
                    my_cache[pos][1] = tag;
                    if (replacement_policy == "LRU")
                    {
                        LRU[pos] = -1;
                    }
                    if (replacement_policy == "FIFO")
                    {
                        fifo[pos] = max_fifo + 1;
                        max_fifo++;
                    }
                }
                misses = true;
            }
        }
        else
        {
            for (int i = 0; i < number_of_blocks; i++)
            {
                if (my_cache[i][0] == 1 && my_cache[i][1] == tag)
                {
                    hits = true;
                    LRU[i] = -1;
                }
                else if (my_cache[i][0] == 0)
                {
                    location = i;
                }

                if (maxi < LRU[i] && replacement_policy == "LRU")
                {
                    maxi = LRU[i];
                    pos = i;
                }
                if (mini > fifo[i] && replacement_policy == "FIFO")
                {
                    mini = fifo[i];
                    pos = i;
                }
                max_fifo = max(max_fifo, fifo[i]);
            }

            if (!hits)
            {
                if (write_policy == "WB")
                {
                    if (location != -1)
                    {
                        my_cache[location][0] = 1;
                        my_cache[location][1] = tag;
                        if (replacement_policy == "LRU")
                        {
                            LRU[location] = -1;
                        }
                        if (replacement_policy == "FIFO")
                        {
                            fifo[location] = max_fifo + 1;
                            max_fifo++;
                        }
                    }
                    else
                    {
                        if (replacement_policy == "RANDOM")
                        {
                            pos = rand() % number_of_blocks;
                        }

                        my_cache[pos][0] = 1;
                        my_cache[pos][1] = tag;
                        if (replacement_policy == "LRU")
                        {
                            LRU[pos] = -1;
                        }
                        if (replacement_policy == "FIFO")
                        {
                            fifo[pos] = max_fifo + 1;
                            max_fifo++;
                        }
                    }
                }
                misses = true;
            }
        }
        if (replacement_policy == "LRU")
        {
            for (int i = 0; i < associativity; i++)
            {
                LRU[i]++;
            }
        }

        string indexes = decToHex(instruction[1], used_bytes_for_index);
        string tags = decToHex(instruction[2], used_bytes_for_tag);
        if (!hits)
        {

            cache_output << "Address: " << full_address[x] << ", Set: 0x" << indexes << ", Miss, "
                         << "Tag: "
                         << "0x" << tags << endl;
            x++;
        }
        else
        {

           cache_output << "Address: " << full_address[x] << ", Set: 0x" << indexes << ", Hit, "
                         << "Tag: "
                         << "0x" << tags << endl;
            x++;
        }
    }
}
// set associative cache 
void sac(vector<vector<ll>> &meta_data, ll number_of_blocks, ll block_size, ll associativity, string replacement_policy, string write_policy, ll used_bytes_for_index, ll used_bytes_for_tag)
{
    ofstream cache_output("output.txt");
    int x = 0;
    ll my_cache[number_of_blocks][associativity][2];
    for (int i = 0; i < number_of_blocks; i++)
    {
        for (int j = 0; j < associativity; j++)
        {
            my_cache[i][j][0] = 0;
            my_cache[i][j][1] = -1;
        }
    }
    ll LRU[number_of_blocks][associativity];
    ll fifo[number_of_blocks][associativity];

    for (int i = 0; i < number_of_blocks; i++)
    {
        for (int j = 0; j < associativity; j++)
        {
            LRU[i][j] = 0;
            fifo[i][j] = 0;
        }
    }
    ll reads = 0;
    ll writes = 0;
    ll hit = 0;
    for (auto instruction : meta_data)
    {
        bool hits = 0;
        bool misses = 1;
        ll max_fifo = 0;
        if (instruction[0] == 0)
        {
            reads++;
            ll index = instruction[1];
            ll tag = instruction[2];
            ll maxi = 0;
            ll pos = 0;
            ll mini = 1e9;
            ll location = -1;
            for (int i = 0; i < associativity; i++)
            {
                if (my_cache[index][i][0] == 0)
                {
                    location = i;
                }
                else
                {
                    if (my_cache[index][i][1] == tag)
                    {
                        hits = true;
                        if (replacement_policy == "LRU")
                        {
                            LRU[index][i] = -1;
                        }
                        // else if (replacement_policy == "FIFO")
                        // {
                        //     fifo[index][i] = 0;
                        // }
                    }
                    else if (maxi < LRU[index][i] && replacement_policy == "LRU")
                    {
                        maxi = LRU[index][i];
                        pos = i;
                    }
                    else if (mini > fifo[index][i] && replacement_policy == "FIFO")
                    {
                        mini = fifo[index][i];
                        pos = i;
                    }
                }
                max_fifo = max(max_fifo, fifo[index][i]);
            }
            if (!hits)
            {
                if (location != -1)
                {
                    misses = true;
                    my_cache[index][location][0] = 1;
                    my_cache[index][location][1] = tag;
                    if (replacement_policy == "LRU")
                    {
                        LRU[index][location] = -1;
                    }
                    else if (replacement_policy == "FIFO")
                    {
                        fifo[index][location] = max_fifo + 1;
                        max_fifo++;
                    }
                }
                else
                {
                    if (replacement_policy == "LRU")
                        LRU[index][pos] = -1;
                    else if (replacement_policy == "RANDOM")
                        pos = rand() % associativity;
                    else if (replacement_policy == "FIFO")
                    {
                        fifo[index][pos] = max_fifo + 1;
                        max_fifo++;
                    }
                    misses = true;
                    my_cache[index][pos][1] = tag;
                }
            }
            if (replacement_policy == "LRU")
            {
                for (int i = 0; i < associativity; i++)
                {
                    LRU[index][i]++;
                }
            }
        }
        else
        {
            writes++;
            ll index = instruction[1];
            ll tag = instruction[2];
            ll mini = 1e9;
            ll maxi = 0;
            ll pos = 0;
            ll location = -1;
            for (int i = 0; i < associativity; i++)
            {
                if (my_cache[index][i][0] == 0)
                {
                    location = i;
                }
                else
                {
                    if (my_cache[index][i][1] == tag)
                    {
                        hits = true;
                        if (replacement_policy == "LRU")
                        {
                            LRU[index][i] = -1;
                        }
                        // else if (replacement_policy == "FIFO")
                        // {
                        //     fifo[index][i] = 0;
                        // }
                    }
                    else if (maxi < LRU[index][i] && replacement_policy == "LRU")
                    {
                        maxi = LRU[index][i];
                        pos = i;
                    }
                    else if (mini > fifo[index][i] && replacement_policy == "FIFO")
                    {
                        mini = fifo[index][i];
                        pos = i;
                    }
                }
                max_fifo = max(max_fifo, fifo[index][i]);
            }
            if (!hits)
            {
                if (location != -1)
                {
                    misses = true;
                    my_cache[index][location][0] = 1;
                    if (write_policy == "WB")
                    {
                        my_cache[index][location][1] = tag;
                        if (replacement_policy == "LRU")
                            LRU[index][location] = -1;
                        else if (replacement_policy == "FIFO")
                        {
                            fifo[index][location] = max_fifo + 1;
                            max_fifo++;
                        }
                    }
                }
                else
                {
                    misses = true;
                    if (write_policy == "WB")
                    {
                        if (replacement_policy == "LRU")
                            LRU[index][pos] = -1;
                        else if (replacement_policy == "RANDOM")
                            pos = rand() % associativity;
                        else if (replacement_policy == "FIFO")
                        {
                            fifo[index][pos] = max_fifo + 1;
                            max_fifo++;
                        }
                        my_cache[index][pos][1] = tag;
                    }
                }
            }
            if (replacement_policy == "LRU")
            {
                for (int i = 0; i < associativity; i++)
                {
                    LRU[index][i]++;
                }
            }
        }

        string index = decToHex(instruction[1], used_bytes_for_index);
        string tag = decToHex(instruction[2], used_bytes_for_tag);
        if (!hits)
        {

            cache_output << "Address: " << full_address[x] << ", Set: 0x" << index << ", Miss, "
                         << "Tag: "
                         << "0x" << tag << endl;
            x++;
        }
        else
        {
            hit++;

            cache_output << "Address: " << full_address[x] << ", Set: 0x" << index << ", Hit, "
                         << "Tag: "
                         << "0x" << tag << endl;
            x++;
        }
    }
    // cout << hit << endl;
}
int main()
{
    srand(time(0));
    ifstream config_file("cache.config");
    long long cache_size, block_size, associativity;
    string replacement_policy;
    string write_policy;
    config_file >> cache_size >> block_size >> associativity >> replacement_policy >> write_policy;
    long long number_of_blocks = cache_size / (block_size);
    long long number_of_sets;
    if (associativity != 0)
        number_of_sets = number_of_blocks / associativity;
    else
        number_of_sets = number_of_blocks;
    long long wasted_bytes = log2(block_size);
    long long used_bytes_for_index;
    if (associativity != 0)
        used_bytes_for_index = log2(number_of_sets);
    else
        used_bytes_for_index = 0;
    long long used_bytes_for_tag = 32 - used_bytes_for_index - wasted_bytes;
    config_file.close();
    ifstream cache_file("cache.access");

    vector<string> access;
    vector<pair<string, long long>> input;
    string s;
    string line;
    ll n = 0;
    while (getline(cache_file, line))
    {
        access.push_back(line); // storing the input in the vector
        n++;                    // counting the number of lines
    }

    for (int i = 0; i < n; i++)
    {
        string type;
        string address;
        string faddress;
        type.push_back(access[i][0]);
        for (int j = 3; j < access[i].length(); j++)
        {
            faddress.push_back(access[i][j]);
        }
        for (int j = 5; j < access[i].length(); j++)
        {
            address.push_back(access[i][j]);
        }
        long long x;
        x = stoll(address, 0, 16);
        input.push_back({type, x});
        full_address.push_back(faddress);
    }

    cache_file.close();

    // for (int i = 0; i < n; i++)
    // {
    //     cout << input[i].first << " " << input[i].second << endl;
    // }

    vector<vector<ll>> meta_data(n);
    for (int i = 0; i < n; i++)
    {
        if (input[i].first == "R")
        {
            meta_data[i].push_back(0);
        }
        else
        {
            meta_data[i].push_back(1);
        }
        long long binary_instruction[32] = {0};
        int j = 0;
        while (input[i].second != 0)
        {
            binary_instruction[j] = input[i].second % 2;
            input[i].second /= 2;
            j++;
        }
        long long index = 0;
        long long shift = 0;
        for (int j = wasted_bytes; j < wasted_bytes + used_bytes_for_index; j++)
        {
            index += binary_instruction[j] << shift;
            shift++;
        }
        meta_data[i].push_back(index);
        long long tag = 0;
        shift = 0;
        for (int j = wasted_bytes + used_bytes_for_index; j < 32; j++)
        {
            tag += binary_instruction[j] << shift;
            shift++;
        }
        meta_data[i].push_back(tag);
    }
    used_bytes_for_index = (used_bytes_for_index + 3) / 4;
    used_bytes_for_tag = (used_bytes_for_tag + 3) / 4;
    if (associativity == 1)
    {
        dmc(meta_data, number_of_sets, block_size, replacement_policy, write_policy, used_bytes_for_index, used_bytes_for_tag);
    }
    else if (associativity)
    {
        sac(meta_data, number_of_sets, block_size, associativity, replacement_policy, write_policy, used_bytes_for_index, used_bytes_for_tag);
    }
    else
    {
        fac(meta_data, number_of_sets, block_size, associativity, replacement_policy, write_policy, used_bytes_for_index, used_bytes_for_tag);
    }
}