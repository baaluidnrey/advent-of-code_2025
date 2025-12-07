#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <set>

using namespace std;

struct operation {
    vector<int> numbers;
    char type;
};


int main()
{
    // puzzle variables
    vector<operation> operations;
    int operation_index;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // extract data from puzzle input ----------
    string str;
    regex number_regex("\\d+");
    regex operation_regex("\[+*]");
    smatch range_match;
    sregex_iterator str_begin, str_end;

    bool first_line = true;

    while (getline(f, str)){

        // number ?
        operation_index = 0;
        str_begin = sregex_iterator(str.begin(), str.end(), number_regex);
        str_end = sregex_iterator();

        for (sregex_iterator i = str_begin; i != str_end; i++) {
            
            smatch match = *i;
            string match_str = match.str();

            if (first_line) {
                vector<int> numbers;
                numbers.push_back(stoi(match_str));
                operation operation_tmp{numbers, '.'};
                operations.push_back(operation_tmp);
            }
            else {
                operations[operation_index].numbers.push_back(stoi(match_str));
            }
            operation_index++;
        }
        first_line = false;

        // if not number, look for operation sign
        operation_index = 0;
        str_begin = sregex_iterator(str.begin(), str.end(), operation_regex);
        str_end = sregex_iterator();

        for (sregex_iterator i = str_begin; i != str_end; i++) {
            
            smatch match = *i;
            string match_str = match.str();
            operations[operation_index].type = match_str[0];
            operation_index++;
        }
    }
    f.close();

    // display operations ----------
    // cout << "operations:\n";
    // for (auto it : operations){
    //     cout << it.type << ": ";
    //     for (auto n : it.numbers) cout << n << ", ";
    //     cout << endl;
    // }


    // part 1 ----------
    long int res_1 = 0;
    for (auto it : operations){

        long int res;
        if      (it.type == '+')    res = 0;    // initialization of operation result
        else if (it.type == '*')    res = 1;

        for (auto n : it.numbers) {
            if      (it.type == '+')    res += n;
            else if (it.type == '*')    res *= n;
        }
        res_1 += res;
    }

    // part 2 ----------
    int res_2 = 0;

    cout << "part. 1: " << res_1 << endl;
    cout << "part. 2: " << res_2 << endl;
    return 0;
}
