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
    int pos, res;

    // open puzzle input
    ifstream f("input.csv");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    // read input and put data into the arrays
    while (getline(f, str))
    {  
        char c = (char) str[0];
        int n = stoi(str.substr(1));
    
	if (c=='L') v.push_back(n*(-1));
	else if (c=='R') v.push_back(n); 

    	cout << str << ": " << c << ", " << n << endl;
    }
    f.close();

    res = 0;
    pos = 50;
    for (auto it : v)
    {
        pos = pos + it;
	pos = pos % 100;
	if (pos==0) res++;
	cout << it << "\t|pos:" << pos << ",\tres:" << res << endl;  
    }
    

    return 0;
}
