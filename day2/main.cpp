#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct range {
    long int min;
    long int max;
};

int main()
{
    // puzzle variables
    vector<range> v;
    vector<long int>ids;
    long int res;

    // open puzzle input
    ifstream f("input.txt");
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
                stol(match_str.substr(0,pos)), 
                stol(match_str.substr(pos+1)) 
            };
            v.push_back(r);
        }
    }
    f.close();

    for (auto it : v){
        for (long int n = it.min; n <= it.max; n++){

            int order = floor(log10(n));
            if ((order % 2)==1){

                int p = pow(10,(order+1)/2);
                long int n_begin = round(n/p);
                long int n_end = n - p*n_begin;

                if (n_end==n_begin) ids.push_back(n);
            }
        }
    }
    res = 0;
    for (auto id : ids) {
        res+=id;
        cout << "res: " << res << endl;
    }
    return 0;
}
