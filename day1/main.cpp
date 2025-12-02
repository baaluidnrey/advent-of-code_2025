#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    // puzzle variables
    vector<int> v;
    string str;
    char c;
    int pos, n;
    int q, r;
    int res;

    // open puzzle input
    ifstream f("input.csv");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // read input
    while (getline(f, str)){  
        c = (char) str[0];
        n = stoi(str.substr(1));
	    if      (c=='L')    v.push_back(n*(-1));
	    else if (c=='R')    v.push_back(n); 
    }
    f.close();

    res = 0;
    pos = 50;
    for (auto n : v){

        q = n / 100;
        r = n % 100;
        cout << "n: " << n << ", q: " << q << ", r: " << r << endl;

        // part 1 ----------
        if ( ((pos+r+100) % 100) == 0) res++;           // point at 0 at the end of a rotation

        // part 2 ----------
        if ( (pos!=0 && pos+r<0) || pos+r>100) res++;   // point at 0 during a rotation
        res +=abs(q);                                   // number of full rotations

        // update current position
        pos = (pos+r+100) % 100;    

        // print iteration
        cout << "pos:" << pos << endl;
        cout << "--> res: " << res << endl;
    }
    

    return 0;
}
