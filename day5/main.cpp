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

int ConcatenateRanges(vector<range> input, vector<range> &output, bool debug){

    output.push_back(input[0]);
    range range_tmp;
    int nb_concatenation = 0;

    for (auto range : input){

        if (debug){
            cout << "---\nrange: (" << range.min << "," << range.max << ")\n";
            cout << "corrected ranges:\n";
            for (auto it : output) cout << "(" << it.min << ", " << it.max << "), ";
            cout << endl;
        }

        bool range_to_add = true;

        for (int j=0; j<output.size(); j++){
            auto corrected_range = output.at(j);

            bool superposition = false;
            auto min = corrected_range.min;
            auto max = corrected_range.max;

            if (debug) cout << "corr_range: (" << corrected_range.min << "," << corrected_range.max << ")\t";

            if (range.min == min && range.max == max){       // same range, do nothing
                if (debug) cout << "same range\n";
                range_to_add = false;
            }
            
            else{

                if (range.min < min && range.max >= min){   // superposition from bottom
                    min = range.min;
                    superposition = true;
                }

                if (range.min <= max && range.max > max){   // superposition from top
                    max = range.max;
                    superposition = true;
                }

                range_tmp.min = min;
                range_tmp.max = max;
                if (superposition){
                    output.at(j) = range_tmp;
                    range_to_add = false;
                    nb_concatenation++;
                }              
                if (debug) cout << "--> (" << min << "," << max << ")\n";
            }
        }
        if (range_to_add)     output.push_back(range);
    }
    return nb_concatenation;
}

int main()
{
    // puzzle variables
    vector<range> v_ranges;
    vector<range> v_corrected_ranges;
    vector<long int> v_ingredient;
    set<long int>fresh_ingredients;
    int res;

    // open puzzle input
    ifstream f("input.txt");
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

        // ingredient ?
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
                v_ranges.push_back(r);
            }
        }
    }
    f.close();

    // display input
    cout << "ingredients:\n";
    for (auto it : v_ingredient) cout << it << ", ";
    cout << endl;

    cout << "ranges:\n";
    for (auto it : v_ranges) cout << "(" << it.min << ", " << it.max << "), ";
    cout << endl;

    // part 2 ----------
    // res = 0;
    // for (auto it : v_ranges){
    //     cout << "(" << it.min << ", " << it.max << ")\n";
    //     for (long int n = it.min; n<= it.max; n++){
    //         if (!fresh_ingredients.contains(n))
    //             fresh_ingredients.insert(n);
    //     }
    // }
    // res = fresh_ingredients.size();

    // concatenation of ranges ----------
    int nb_concatenations;
    vector<range> v_ranges_tmp = v_ranges;
    do{
        v_corrected_ranges.clear();
        nb_concatenations = ConcatenateRanges(v_ranges_tmp, v_corrected_ranges, false);
        v_ranges_tmp = v_corrected_ranges;
        cout << "nb_concatenations: " << nb_concatenations << endl;
    }
    while (nb_concatenations!=0);

    cout << "corrected ranges:\n";
    for (auto it : v_corrected_ranges) cout << "(" << it.min << ", " << it.max << "), ";
    cout << endl;

    // part 1 ----------
    res = 0;
    for (auto ingredient : v_ingredient){
        bool is_fresh = false;
        for (auto range : v_corrected_ranges){
            if (ingredient >= range.min && ingredient <= range.max){
                is_fresh = true;
                res++;
                break;
            }
        }
    }


    cout << "res: " << res << endl;
    return 0;
}
