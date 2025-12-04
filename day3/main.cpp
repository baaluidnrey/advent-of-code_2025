#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <map>
#include <string>

using namespace std;

int main()
{
    int res;
    string str;

    // open puzzle input
    ifstream f("input_test.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str)){  
        map<int, int> m;
        for (char c : str){
            auto val = static_cast<int>(c-'0');
            
        }

    }
    f.close();



    // compute and display the result
    res = 0;
    cout << "res: " << res << endl;

    return 0;
}
