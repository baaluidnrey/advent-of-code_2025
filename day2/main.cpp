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
                stol(match_str.substr(0,pos)), 
                stol(match_str.substr(pos+1)) 
            };
            v.push_back(r);
        }
    }
    f.close();

    for (auto it : v){
        for (long int n = it.min; n <= it.max; n++){

            /* part 1 ----------
            int order = floor(log10(n));
            if ((order % 2)==1){

                int p = pow(10,(order+1)/2);
                long int n_begin = round(n/p);
                long int n_end = n - p*n_begin;

                if (n_end==n_begin) ids.push_back(n);
            }
            */

            int nb_digits = floor(log10(n))+1;
            cout << "n: " << n << ", nb_digits: " << nb_digits << endl;
            int q = 2;
            bool id_valid = true;
            while (id_valid && q<=nb_digits){
                if ( (nb_digits % q) == 0 ){
                    long int values[q];
                    long int current = n;

                    for (int i=0; i<q; i++){
                        int p = pow(10, nb_digits/q);   // TODO : begin with the higher order
                        long int tmp = round(current/p);
                        // current -= p*tmp;
                        current = p*(current-p*tmp);
                        values[i] = tmp;
                        cout << "p: " << p << endl;
                        cout << "tmp: " << tmp << endl;
                        cout << "current: " << current << endl;
                    }
                    for (int i=0; i<q; i++) cout << values[i] << ", ";
                    cout << endl;       
                }
                q++;
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
