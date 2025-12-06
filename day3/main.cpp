#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    long int res = 0;
    string str;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str)){
        
        std::vector<int>::iterator result;
        long int joltage = 0;
        // int nb_batteries = 2;       // part 1
        int nb_batteries = 12;       // part 2

        // extract digits
        vector<int> v;
        for (char c : str) v.push_back(static_cast<int>(c-'0'));

        // compute joltage of bank
        for (int i=1; i<=nb_batteries; i++){
            
            result = max_element(
                v.begin(), 
                v.end()-(nb_batteries-i)
            );
            
            joltage += *result * pow(10, nb_batteries-i);

            v.erase(
                v.begin(), 
                v.begin() + distance(v.begin(), result) + 1
            );
        }
        res += joltage;
    }
    f.close();
    cout << "res: " << res << endl;
    return 0;
}
