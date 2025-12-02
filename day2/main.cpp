#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <regex>

using namespace std;

struct range {
    int min;
    int max;
};

int main()
{
    // puzzle variables
    vector<range> v;
    int res;

    // open puzzle input
    ifstream f("input_test.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // read input
    string str;
    regex range_regex("\\d+-\\d+");
    smatch range_match;

    while (getline(f, str)){  

        auto str_begin = sregex_iterator(str.begin(), str.end(), range_regex);
        auto str_end = sregex_iterator();

        for (sregex_iterator i = str_begin; i != str_end; i++)
        {
            smatch match = *i;
            string match_str = match.str();

            int pos = match_str.find("-");
            range r = { 
                stoi(match_str.substr(0,pos)), 
                stoi(match_str.substr(pos+1)) 
            };
            v.push_back(r);
        }
    }
    f.close();

    for (auto it : v){
        cout << it.min << ", " << it.max << endl;
    }


    return 0;
}
