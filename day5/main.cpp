#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <set>

using namespace std;

struct range {
    long int min;
    long int max;
};

int main()
{
    // puzzle variables
    vector<range> v_range;
    vector<long int> v_ingredient;
    set<long int>fresh_ingredients;
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
    regex ingredient_regex("\\d+");
    smatch range_match;

    while (getline(f, str)){  

        if ( regex_match(str, ingredient_regex) ){
            v_ingredient.push_back(stol(str));
        }

        // if not ingredient, search for range
        else {
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
                v_range.push_back(r);
            }
        }
    }
    f.close();

    // display input
    // cout << "ingredients:\n";
    // for (auto it : v_ingredient) cout << it << ", ";
    // cout << endl;

    // cout << "ranges:\n";
    // for (auto it : v_range) cout << "(" << it.min << ", " << it.max << "), ";
    // cout << endl;

    // part 1 ----------
    // res = 0;
    // for (auto ingredient : v_ingredient){
    //     bool is_fresh = false;
    //     for (auto range : v_range){
    //         if (ingredient >= range.min && ingredient <= range.max){
    //             is_fresh = true;
    //             res++;
    //             break;
    //         }
    //     }
    // }

    // part 2 ----------
    res = 0;
    for (auto it : v_range){
        cout << "(" << it.min << ", " << it.max << ")\n";
        for (long int n = it.min; n<= it.max; n++){
            if (!fresh_ingredients.contains(n))
                fresh_ingredients.insert(n);
        }
    }
    res = fresh_ingredients.size();

    cout << "res: " << res << endl;
    return 0;
}
