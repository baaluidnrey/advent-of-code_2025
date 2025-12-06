#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    int res = 0;
    string str;

    // open puzzle input
    ifstream f("input_test.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str)){
        
        std::vector<int>::iterator result;
        int joltage = 0;
        int nb_batteries = 2;       // part 1

        // extract digits
        vector<int> v;
        for (char c : str) v.push_back(static_cast<int>(c-'0'));

        cout << "---\n" << str << endl;

        for (int i=1; i<=nb_batteries; i++){

            for (auto it : v) cout << it << ", ";
            cout << endl;
            
            result = std::max_element(
                v.begin(), 
                v.end()-(nb_batteries-i)
            );
            
            std::cout << "Max element found at index "
                    << std::distance(v.begin(), result)
                    << " has value " << *result << '\n';

            joltage += *result * pow(10, nb_batteries-i);

            cout << "joltage: " << joltage << endl; 

            v.erase(v.begin(), v.begin() + std::distance(v.begin(), result) + 1);
        }
        res += joltage;
    }
    f.close();
    cout << "res: " << res << endl;
    return 0;
}
