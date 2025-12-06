#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <limits>

using namespace std;

int main()
{
    int res = 0;
    string str;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str)){
        
        std::vector<int>::iterator result;
        int joltage;

        // extract digits
        vector<int> v;
        for (char c : str) v.push_back(static_cast<int>(c-'0'));

        // find first digit of joltage rating, i.e. max in line
        result = std::max_element(
            v.begin(), 
            v.end()-1
        );
        joltage = *result * 10;

        // find second digit of voltage rating, i.e. max in rest of line
        result = std::max_element(
            v.begin() + std::distance(v.begin(), result) + 1,
            v.end()
        );
        joltage += *result;

        // std:: cout << "joltage :"
        //         << joltage << endl;

        res+=joltage;
    }
    f.close();

    // compute and display the result
    cout << "res: " << res << endl;

    return 0;
}
