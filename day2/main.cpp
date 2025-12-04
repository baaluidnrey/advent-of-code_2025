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

            bool id_valid = true;
            int nb_digits = floor(log10(n))+1;

            // int q = 2;           // part 1
            int q = nb_digits;      // part 2
            int q_min = 2;

            while (id_valid && q>=q_min){
                if ( (nb_digits % q) == 0 ){    // n can be splitted in q parts
                    long int values[q];
                    long int current = n;

                    // extract q parts from highest order
                    for (int i=0; i<q-1; i++){
                        int p = pow(10, nb_digits-(i+1)*(nb_digits/q));
                        long int tmp = round(current/p);
                        current -= p*tmp;
                        values[i] = tmp;
                    }
                    values[q-1] = current;

                    // check if id is valid
                    id_valid = false;
                    for (int i=0; i<q; i++){
                        if (values[i]!=values[0]) id_valid = true;
                    }
                }
                q--;
            }
            if (!id_valid) ids.push_back(n);
        }
    }

    // compute and display the result
    res = 0;
    cout << "invalid ids: ";
    for (auto id : ids) {
        cout << id << ", ";
        res+=id;
    }
    cout << endl;
    cout << "res: " << res << endl;

    return 0;
}
