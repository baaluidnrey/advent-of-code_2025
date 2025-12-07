#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <regex>
#include <cmath>

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
    string str;

    bool part_1 = false;
    bool part_2 = true;

    // open puzzle input
    ifstream f("input_test.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // extract data from puzzle input ----------
    
    // for part. 1
    if (part_1){

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
    } // part. 1

    // for part. 2
    // Cephalopod math is written right-to-left in columns ----------
    // we need to parse the file another way
    // 2. then parse the file column by column
    if (part_2){

        // 1. get number of rows and cols
        int nb_cols = 0;
        int nb_rows = 0;
        while (getline(f, str)){
            cout << str << endl;
            nb_cols = str.length();
            nb_rows++;
        }
        f.close();

        cout << "nb_rows: " << nb_rows << ", nb_cols: " << nb_cols << endl;

        // 2. then parse the file column by column to get numbers
        int col = 0;
        char c;
        vector<int> numbers;

        FILE* fp = std::fopen("input_test.txt", "rb");  // we need to open the file in binary mode

        while (col < nb_cols) {

            vector<int> digits;

            for (int row = 0; row <nb_rows-1; row++){

                // get char of col line by line
                int offset = row*(nb_cols+1)+col;
                fseek(fp, offset, SEEK_SET);        // go at the position of the interesting char in file
                c = fgetc(fp);

                int digit = static_cast<int>(c-'0');
                if ( digit>=0 && digit>=9 ) digits.push_back(digit);

                cout << "offset: " << offset << ", c: " << c << ", digit: " << digit << endl;
            }
            col++;
        }
        fclose(fp);
    }

    // display operations ----------
    cout << "---\noperations:\n";
    for (auto it : operations){
        cout << it.type << ": ";
        for (auto n : it.numbers) cout << n << ", ";
        cout << endl;
    }

    // compute result ----------
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

    cout << "res : " << res_1 << endl;
    return 0;
}
